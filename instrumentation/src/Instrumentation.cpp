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

  header += "\nprintf(\"Number of counters: " + std::to_string(this->counters.size()) + "\\n\");\n";
  for (auto const& [loop, counterName] : this->counters) {
    header += "printf(\"At line " + std::to_string(srcMgr.getSpellingLineNumber(loop->getBeginLoc())) + " :\");\n";

    std::string format = "";
    std::string variables = "";
    std::string originalNames = "";
    for (ParmVarDecl* controlParam : this->controlVariables[loop]) {
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
    variables += counterName;

    counters += "printf(\"" + format + "\\n\", " + variables + ");\n";
    header += "printf(\"" + originalNames + "\\n\");\n";
    header += "printf(\"Nesting depth: " + std::to_string(this->nestingDepth[loop]) + "\\n\");\n";
  }

  return header + counters;
}

void InstrumentationVisitor::addTempVariables() {
  std::string tempVariables = "\n";
  DenseMap<ParmVarDecl*, bool> added;

  for (auto const& [_, controlParams] : this->controlVariables) {
    for (ParmVarDecl* controlParam : controlParams) {
      if (added.find(controlParam) == added.end()) {
        added[controlParam] = true;
        std::string name = controlParam->getNameAsString();
        tempVariables += controlParam->getType().getAsString() + " temp" + name + " = " + name + ";\n";
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
    for (auto const& [_, counterName] : this->counters) {
      countersDecls += "unsigned " + counterName + " = 0;\n";
    }

    if (auto* body = this->currFunc->getBody())
      this->rewriter->InsertTextAfterToken(body->getBeginLoc(), countersDecls);

    this->addTempVariables();
    this->addPrints();
  }

  this->currFunc = funcDecl;

  return true;
}

bool InstrumentationVisitor::isLoop(clang::Stmt* stmt) {
  return isa<ForStmt>(stmt) || isa<WhileStmt>(stmt) || isa<DoStmt>(stmt);
}

bool InstrumentationVisitor::validateLoop(clang::Stmt* stmt, Stmt* loop, u_int32_t nestingDepth) {
  Stmt* lastLoop = loop;
  for (auto* child : stmt->children()) {
    if (!child)
      continue;

    u_int32_t nextNestingDepth = nestingDepth;
    if (this->isLoop(child)) {
      nextNestingDepth++;
      this->nestingDepth[child] = nextNestingDepth;

      this->parentLoops[child] = loop;
      this->visitedLoops.insert(child);

      lastLoop = child;
    }

    if (this->ignoreNonNewton && isa<ReturnStmt>(child))
      return false;

    bool childIsValid = this->validateLoop(child, lastLoop, nextNestingDepth);
    if (this->ignoreNonNewton && !childIsValid)
      return false;

    lastLoop = loop;
  }

  return true;
}

bool InstrumentationVisitor::visitLoop(Stmt* loop, SourceLocation& bodyLoc) {
  if (!this->visitedLoops.contains(loop)) {
    this->nestingDepth[loop] = 1;
    this->visitedLoops.insert(loop);

    bool isValidLoop = this->validateLoop(loop, loop, 1);
    if (this->ignoreNonNewton && !isValidLoop)
      return false;
  }

  this->getParentControlVars(loop);

  // Add counter increment if this loop is within the target function
  if (this->currFunc != nullptr && this->currFunc->getNameAsString() == this->functionName) {
    std::string counter = "counter" + this->functionName + std::to_string(this->counters.size());
    this->counters[loop] = counter;

    std::string increment = "\n" + counter + "++;";
    this->rewriter->InsertTextAfterToken(bodyLoc, increment);
  }

  return true;
}

void InstrumentationVisitor::getControlVars(Stmt* node, Stmt* loop) {
  for (auto* child : node->children()) {
    if (!child)
      continue;

    if (auto* refExpr = dyn_cast<DeclRefExpr>(child)) {
      NamedDecl* decl = refExpr->getFoundDecl();
      if (this->paramRefs.find(decl) != this->paramRefs.end()) {
        for (ParmVarDecl* param : this->paramRefs[decl]) {
          this->controlVariables[loop].insert(param);
        }
      }
    }

    this->getControlVars(child, loop);
  }
}

void InstrumentationVisitor::getParentControlVars(Stmt* loop) {
  if (this->parentLoops.find(loop) == this->parentLoops.end())
    return;

  Stmt* parentLoop = this->parentLoops[loop];
  for (ParmVarDecl* controlVar : this->controlVariables[parentLoop]) {
    this->controlVariables[loop].insert(controlVar);
  }
}

bool InstrumentationVisitor::VisitWhileStmt(WhileStmt* whileStmt) {
  this->getControlVars(whileStmt->getCond(), whileStmt);

  SourceLocation bodyLoc = whileStmt->getBody()->getBeginLoc();
  return this->visitLoop(whileStmt, bodyLoc);
}

bool InstrumentationVisitor::VisitDoStmt(DoStmt* doStmt) {
  this->getControlVars(doStmt->getCond(), doStmt);

  SourceLocation bodyLoc = doStmt->getBody()->getBeginLoc();
  return this->visitLoop(doStmt, bodyLoc);
}

bool InstrumentationVisitor::VisitForStmt(ForStmt* forStmt) {
  if (forStmt->getInit()) {
    if (auto* binOp = dyn_cast<BinaryOperator>(forStmt->getInit())) {
      this->VisitBinaryOperator(binOp);
    } else {
      this->getControlVars(forStmt->getInit(), forStmt);
    }
  }

  if (Expr* cond = forStmt->getCond())
    this->getControlVars(cond, forStmt);

  SourceLocation bodyLoc = forStmt->getBody()->getBeginLoc();
  return this->visitLoop(forStmt, bodyLoc);
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

bool InstrumentationVisitor::VisitIfStmt(IfStmt* ifStmt) {
  if (!this->ignoreNonNewton || this->visitedIfs.contains(ifStmt))
    return true;

  this->visitedIfs.insert(ifStmt);

  bool isValidIf = this->validateIf(ifStmt);
  return isValidIf;
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