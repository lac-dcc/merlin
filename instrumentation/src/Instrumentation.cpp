#include "Instrumentation.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>

using namespace clang;
using namespace llvm;

bool InsertPrintVisitor::VisitReturnStmt(ReturnStmt* retStmt) {
  this->rewriter->InsertText(retStmt->getBeginLoc(), this->printString, false, true);
  return true;
}

bool NodeCounterVisitor::VisitStmt(Stmt* stmt) {
  this->nodeCount++;
  return true;
}

bool NodeCounterVisitor::VisitDecl(Decl* decl) {
  this->nodeCount++;
  return true;
}

bool DependenceVisitor::containsRefToParam(clang::Stmt* node, clang::NamedDecl* decl) {
  bool result = false;

  for (auto* child : node->children()) {
    if (!child)
      continue;

    if (auto* refExpr = dyn_cast<DeclRefExpr>(child)) {
      NamedDecl* foundDecl = refExpr->getFoundDecl();

      if (auto* param = dyn_cast<ParmVarDecl>(foundDecl)) {
        (*this->paramRefs)[decl].push_back(param);
        result = true;
      } else if (this->paramRefs->find(foundDecl) != this->paramRefs->end()) {
        for (ParmVarDecl* param : (*this->paramRefs)[foundDecl]) {
          (*this->paramRefs)[decl].push_back(param);
        }
        result = true;
      }
    }

    result |= this->containsRefToParam(child, decl);
  }

  return result;
}

bool DependenceVisitor::VisitBinaryOperator(clang::BinaryOperator* binOp) {
  if (!binOp->isAssignmentOp())
    return true;

  if (auto* ref = dyn_cast<DeclRefExpr>(binOp->getLHS())) {
    NamedDecl* decl = ref->getFoundDecl();
    if (!binOp->isCompoundAssignmentOp())
      (*this->paramRefs)[decl].clear();

    bool contains = this->containsRefToParam(binOp->getRHS(), decl);

    if (!contains && !binOp->isCompoundAssignmentOp())
      this->paramRefs->erase(decl);
  }

  return true;
}

bool DependenceVisitor::VisitVarDecl(clang::VarDecl* decl) {
  if (auto* param = dyn_cast<ParmVarDecl>(decl)) {
    (*this->paramRefs)[param].push_back(param);
  } else if (auto* init = decl->getInit()) {
    (*this->paramRefs)[decl].clear();
    bool contains = this->containsRefToParam(init, decl);

    if (!contains)
      this->paramRefs->erase(decl);
  }

  return true;
}

std::string InstrumentationVisitor::getPrintString() {
  SourceManager& srcMgr = this->rewriter->getSourceMgr();
  std::string header = "";
  std::string counters = "";

  header += "\nprintf(\"Number of counters: " + std::to_string(this->instrumentedLoops) + "\\n\");\n";
  for (auto const& loop : this->loopVec) {
    header += "printf(\"At line " + std::to_string(loop->line) + " :\");\n";

    std::string format = "";
    std::string variables = "";
    std::string originalNames = "";
    for (ParmVarDecl* controlParam : loop->controlVariables) {
      std::string paramName = controlParam->getNameAsString();
      originalNames += " " + paramName;

      QualType type = controlParam->getType();
      if (type.getTypePtr()->isPointerType()) {
        format +=
            this->formatSpecifier[type.getTypePtr()->getPointeeType().getDesugaredType(*this->context).getAsString()] +
            " ";
        variables += "*temp" + paramName + ",";
      } else {
        format += this->formatSpecifier[type.getDesugaredType(*this->context).getAsString()] + " ";
        variables += "temp" + paramName + ",";
      }
    }

    format += "%d";
    variables += loop->counterName;

    counters += "printf(\"" + format + "\\n\", " + variables + ");\n";
    header += "printf(\"" + originalNames + "\\n\");\n";
    header += "printf(\"Nesting depth: " + std::to_string(loop->nestingDepth) + "\\n\");\n";
  }

  return header + counters + "printf(\"\\nend\\n\");\n";
}

void InstrumentationVisitor::addTempVariables() {
  std::string tempVariables = "\n";
  DenseMap<ParmVarDecl*, bool> added;

  for (auto const& loop : this->loopVec) {
    for (ParmVarDecl* controlVar : loop->controlVariables) {
      if (added.find(controlVar) == added.end()) {
        added[controlVar] = true;
        std::string name = controlVar->getNameAsString();
        tempVariables += controlVar->getType().getAsString() + " temp" + name + " = " + name + ";\n";
      }
    }
  }

  auto* body = this->currFunc->getBody();
  if (body)
    this->rewriter->InsertTextAfterToken(body->getBeginLoc(), tempVariables);
}

void InstrumentationVisitor::addPrints() {
  InsertPrintVisitor printVisitor(this->rewriter);
  printVisitor.printString = this->getPrintString();
  printVisitor.TraverseDecl(this->currFunc);

  if (this->currFunc->getReturnType().getTypePtr()->isVoidType())
    this->rewriter->InsertText(this->currFunc->getEndLoc(), printVisitor.printString, false, true);
}

bool InstrumentationVisitor::VisitFunctionDecl(FunctionDecl* funcDecl) {
  if (funcDecl->getNameAsString() == this->functionName) {
    // Once we visit our target function, we count the number of nodes in its
    // AST and output it
    NodeCounterVisitor countVisitor;
    countVisitor.TraverseDecl(funcDecl);
    outs() << countVisitor.nodeCount << '\n';

    // We also use an auxiliary class to get all variables that reference
    // function params
    DependenceVisitor dependenceVisitor;
    dependenceVisitor.paramRefs = &(this->paramRefs);
    dependenceVisitor.TraverseDecl(funcDecl);
  } else if (this->currFunc != nullptr && this->currFunc->getNameAsString() == this->functionName) {
    // If this condition is true, then we have finished traversing our target
    // function

    std::string countersDecls = "";
    for (auto const& loop : this->loopVec) {
      countersDecls += "unsigned " + loop->counterName + " = 0;\n";
    }

    if (auto* body = this->currFunc->getBody())
      this->rewriter->InsertTextAfterToken(body->getBeginLoc(), countersDecls);

    this->addTempVariables();
    this->addPrints();
  }

  this->currFunc = funcDecl;

  return true;
}

bool InstrumentationVisitor::VisitWhileStmt(WhileStmt* whileStmt) {
  if (this->currFunc == nullptr || this->currFunc->getNameAsString() != this->functionName)
    return true;

  SourceLocation bodyLoc = whileStmt->getBody()->getBeginLoc();
  bool isValidLoop = this->createAndInstrumentLoop(whileStmt, bodyLoc);
  if (this->ignoreNonNewton && !isValidLoop)
    return false;

  auto loopPtr = this->loopMap[whileStmt];
  this->getControlVars(whileStmt->getCond(), loopPtr);

  loopPtr->verifyAndSetIsConstantLoop();
  loopPtr->computeNestingDepth();
  loopPtr->takeParentControlVars();

  return true;
}

bool InstrumentationVisitor::VisitDoStmt(DoStmt* doStmt) {
  if (this->currFunc == nullptr || this->currFunc->getNameAsString() != this->functionName)
    return true;

  SourceLocation bodyLoc = doStmt->getBody()->getBeginLoc();
  bool isValidLoop = this->createAndInstrumentLoop(doStmt, bodyLoc);
  if (this->ignoreNonNewton && !isValidLoop)
    return false;

  auto loopPtr = this->loopMap[doStmt];
  this->getControlVars(doStmt->getCond(), loopPtr);

  loopPtr->verifyAndSetIsConstantLoop();
  loopPtr->computeNestingDepth();
  loopPtr->takeParentControlVars();

  return true;
}

bool InstrumentationVisitor::VisitForStmt(ForStmt* forStmt) {
  if (this->currFunc == nullptr || this->currFunc->getNameAsString() != this->functionName)
    return true;

  SourceLocation bodyLoc = forStmt->getBody()->getBeginLoc();
  bool isValidLoop = this->createAndInstrumentLoop(forStmt, bodyLoc);
  if (this->ignoreNonNewton && !isValidLoop)
    return false;

  auto loopPtr = this->loopMap[forStmt];
  if (Stmt* init = forStmt->getInit())
    this->getControlVars(init, loopPtr);

  if (Expr* cond = forStmt->getCond())
    this->getControlVars(cond, loopPtr);

  loopPtr->verifyAndSetIsConstantLoop();
  loopPtr->computeNestingDepth();
  loopPtr->takeParentControlVars();

  return true;
}

void InstrumentationVisitor::getControlVars(Stmt* node, std::shared_ptr<Loop> loop) {
  for (auto* child : node->children()) {
    if (!child)
      continue;

    if (auto* refExpr = dyn_cast<DeclRefExpr>(child)) {
      NamedDecl* decl = refExpr->getFoundDecl();
      if (this->paramRefs.find(decl) != this->paramRefs.end()) {
        for (ParmVarDecl* param : this->paramRefs[decl]) {
          loop->controlVariables.insert(param);
        }
      }
    }

    this->getControlVars(child, loop);
  }
}

bool InstrumentationVisitor::createAndInstrumentLoop(Stmt* loop, SourceLocation& bodyLoc) {
  if (this->loopMap.find(loop) == this->loopMap.end()) {
    this->insertNewLoop(loop, nullptr);

    bool isValidLoop = this->validateLoop(loop, loop);
    if (this->ignoreNonNewton && !isValidLoop)
      return false;
  }

  // Add counter increment to the loop
  std::string counter = "counter" + this->functionName + std::to_string(this->instrumentedLoops);
  this->instrumentedLoops++;
  this->loopMap[loop]->counterName = counter;

  std::string increment = "\n" + counter + "++;";
  this->rewriter->InsertTextAfterToken(bodyLoc, increment);

  return true;
}

bool InstrumentationVisitor::validateLoop(clang::Stmt* stmt, Stmt* loop) {
  Stmt* lastLoop = loop;
  for (auto* child : stmt->children()) {
    if (!child)
      continue;

    if (this->isLoop(child)) {
      this->insertNewLoop(child, this->loopMap[loop]);

      lastLoop = child;
    }

    if (this->ignoreNonNewton && isa<ReturnStmt>(child))
      return false;

    bool childIsValid = this->validateLoop(child, lastLoop);
    if (this->ignoreNonNewton && !childIsValid)
      return false;

    lastLoop = loop;
  }

  return true;
}

bool InstrumentationVisitor::isLoop(clang::Stmt* stmt) {
  return isa<ForStmt>(stmt) || isa<WhileStmt>(stmt) || isa<DoStmt>(stmt);
}

bool InstrumentationVisitor::VisitIfStmt(IfStmt* ifStmt) {
  if (this->currFunc == nullptr || this->currFunc->getNameAsString() != this->functionName)
    return true;

  if (!this->ignoreNonNewton || this->visitedIfs.contains(ifStmt))
    return true;

  this->visitedIfs.insert(ifStmt);

  return this->validateIf(ifStmt);
}

bool InstrumentationVisitor::validateIf(Stmt* stmt) {
  for (auto* child : stmt->children()) {
    if (!child)
      continue;

    if (auto* childIf = dyn_cast<IfStmt>(child))
      this->visitedIfs.insert(childIf);

    if (this->isLoop(child) || !this->validateIf(child))
      return false;
  }

  return true;
}

void InstrumentationVisitor::insertNewLoop(Stmt* loop, std::shared_ptr<Loop> parent) {
  unsigned int line = this->rewriter->getSourceMgr().getSpellingLineNumber(loop->getBeginLoc());
  auto loopPtr = std::make_shared<Loop>(parent, line);

  this->loopMap[loop] = loopPtr;
  this->loopVec.push_back(loopPtr);
}

void InstrumentationConsumer::HandleTranslationUnit(ASTContext& Context) {
  clang::SourceManager& srcMgr = this->rewriter->getSourceMgr();
  std::string inputFile = srcMgr.getFileEntryForID(srcMgr.getMainFileID())->getName().str();
  this->visitor.functionName = this->targetFunction;

  auto start = std::chrono::system_clock::now();
  bool success = this->visitor.TraverseDecl(Context.getTranslationUnitDecl());

  if (success) {
    std::error_code error_code;
    raw_fd_ostream outFile("output/" + this->outputFile, error_code, sys::fs::FileAccess::FA_Write);
    this->rewriter->getEditBuffer(srcMgr.getMainFileID()).write(outFile);
    outFile.close();
  } else {
    outs() << "Unable to instrument the input\n";
  }

  auto end = std::chrono::system_clock::now();
  if (this->measureTime) {
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    outs() << duration.count() << '\n';
  }
}

std::unique_ptr<ASTConsumer> InstrumentationAction::CreateASTConsumer(CompilerInstance& Compiler, StringRef InFile) {
  this->rewriter.setSourceMgr(Compiler.getSourceManager(), Compiler.getLangOpts());
  return std::make_unique<InstrumentationConsumer>(&Compiler.getASTContext(), &(this->rewriter), this->outputFile,
                                                   this->targetFunction, this->ignoreNonNewton, this->measureTime);
}

bool InstrumentationAction::ParseArgs(const CompilerInstance& Compiler, const std::vector<std::string>& args) {
  for (size_t i = 0, end = args.size(); i < end; ++i) {
    DiagnosticsEngine& diagnostics = Compiler.getDiagnostics();
    if (args[i] == "-output-file") {
      if (i + 1 >= end) {
        diagnostics.Report(diagnostics.getCustomDiagID(DiagnosticsEngine::Error, "Missing -output-file argument"));
        return false;
      }

      ++i;
      this->outputFile = args[i];
    } else if (args[i] == "-target-function") {
      if (i + 1 >= end) {
        diagnostics.Report(diagnostics.getCustomDiagID(DiagnosticsEngine::Error, "Missing -target-function argument"));
        return false;
      }

      ++i;
      this->targetFunction = args[i];
    } else if (args[i] == "-ignore-nonnewton") {
      this->ignoreNonNewton = true;
      ++i;
    } else if (args[i] == "-measure-time") {
      this->measureTime = true;
      ++i;
    } else if (args[i] == "-help") {
      errs() << "--- Merlin plugin ---\n";
      errs() << "Arguments:\n";
      errs() << " -output-file         Name of the instrumented output file.\n";
      errs() << " -target-function     Name of the function to be instrumented.\n";
      errs() << " -ignore-nonnewton    Indicates that Non-Newton programs should be ignored by instrumentation.\n";
      errs() << " -measure-time        Indicates that Merlin should measure and output instrumentation time.\n";
    } else {
      unsigned DiagID = diagnostics.getCustomDiagID(DiagnosticsEngine::Error, "Invalid argument '%0'");
      diagnostics.Report(DiagID) << args[i];

      return false;
    }
  }

  return true;
}
