#include "Instrumentation.hpp"

using namespace clang;
using namespace llvm;

bool InsertPrintVisitor::VisitReturnStmt(ReturnStmt* retStmt) {
  this->rewriter->InsertText(retStmt->getBeginLoc(), this->printString, false, true);
  return true;
}

std::string InstrumentationVisitor::getPrintString() {
  std::string format = "%d";
  std::string variables = this->counter + ",";
  for (auto const& [decl, name] : this->taintedVariables) {
    if (auto* varDecl = dyn_cast<VarDecl>(decl)) {
      QualType type = varDecl->getType();
      if (type.getTypePtr()->isPointerType()) {
        format +=
            " " +
            this->formatSpecifier[type.getTypePtr()->getPointeeType().getDesugaredType(*this->context).getAsString()];
        variables += "*temp" + name + ",";
      } else {
        format += " " + this->formatSpecifier[type.getDesugaredType(*this->context).getAsString()];
        variables += "temp" + name + ",";
      }
    }
  }

  // Remove last comma
  variables.pop_back();

  return "printf(\"" + format + "\", " + variables + ");\n";
}

void InstrumentationVisitor::addTempVariables() {
  std::string tempVariables = "\n";
  for (auto const& [decl, name] : this->taintedVariables) {
    if (auto* varDecl = dyn_cast<VarDecl>(decl))
      tempVariables += varDecl->getType().getAsString() + " temp" + name + " = " + name + ";\n";
  }

  auto* body = this->currFunc->getBody();
  if (body)
    this->rewriter->InsertTextAfterToken(body->getBeginLoc(), tempVariables);
}

void InstrumentationVisitor::addPrints() {
  this->printVisitor.printString = this->getPrintString();
  this->printVisitor.TraverseDecl(this->currFunc);

  if (this->currFunc->getReturnType().getTypePtr()->isVoidType())
    this->rewriter->InsertText(this->currFunc->getEndLoc(), this->printVisitor.printString, false, true);
}

bool InstrumentationVisitor::VisitFunctionDecl(FunctionDecl* funcDecl) {
  if (this->currFunc != nullptr && this->currFunc->getNameAsString() == functionName) {
    std::string counterDeclaration = "unsigned " + this->counter + " = 0;\n";

    if (auto* body = this->currFunc->getBody())
      this->rewriter->InsertTextAfterToken(body->getBeginLoc(), counterDeclaration);

    this->addTempVariables();
    this->addPrints();
    this->taintedVariables.clear();
  }

  this->counter = "counter" + funcDecl->getNameAsString();
  this->currFunc = funcDecl;

  return true;
}

bool InstrumentationVisitor::visitLoop(Stmt* loop, SourceLocation& bodyLoc) {
  if (this->visitedLoops.find(loop) == this->visitedLoops.end()) {
    this->visitedLoops[loop] = true;
    if (!this->isValidLoop(loop))
      return false;
  }

  if (this->currFunc != nullptr && this->currFunc->getNameAsString() == this->functionName) {
    SourceLocation beginLoc = loop->getBeginLoc();
    SourceManager& srcMgr = this->rewriter->getSourceMgr();
    std::string increment = "\n" + this->counter + "++;";
    this->rewriter->InsertTextAfterToken(bodyLoc, increment);
  }

  return true;
}

void InstrumentationVisitor::getTaintedVars(Stmt* node) {
  for (auto* child : node->children()) {
    if (!child)
      continue;

    if (auto* refExpr = dyn_cast<DeclRefExpr>(child)) {
      NamedDecl* decl = refExpr->getFoundDecl();

      if (this->paramRefs.find(decl) != this->paramRefs.end()) {
        for (auto* param : this->paramRefs[decl]) {
          this->taintedVariables[param] = param->getNameAsString();
        }
      }
    }

    this->getTaintedVars(child);
  }
}

bool InstrumentationVisitor::VisitWhileStmt(WhileStmt* whileStmt) {
  SourceLocation bodyLoc = whileStmt->getBody()->getBeginLoc();
  this->getTaintedVars(whileStmt->getCond());

  return this->visitLoop(whileStmt, bodyLoc);
}

bool InstrumentationVisitor::isValidLoop(Stmt* stmt) {
  for (auto* child : stmt->children()) {
    if (!child)
      continue;

    if (auto* childFor = dyn_cast<ForStmt>(child)) {
      this->visitedLoops[childFor] = true;
    } else if (auto* childWhile = dyn_cast<WhileStmt>(child)) {
      this->visitedLoops[childWhile] = true;
    }

    if (isa<ReturnStmt>(child) || !this->isValidLoop(child)) {
      return false;
    }
  }

  return true;
}

bool InstrumentationVisitor::VisitForStmt(ForStmt* forStmt) {
  SourceLocation bodyLoc = forStmt->getBody()->getBeginLoc();

  BinaryOperator* binOp;
  if (forStmt->getInit() && (binOp = dyn_cast<BinaryOperator>(forStmt->getInit())))
    this->VisitBinaryOperator(binOp);

  if (Expr* cond = forStmt->getCond())
    this->getTaintedVars(cond);

  return this->visitLoop(forStmt, bodyLoc);
}

bool InstrumentationVisitor::isValidIf(Stmt* stmt) {
  for (auto* child : stmt->children()) {
    if (!child)
      continue;

    if (auto* childIf = dyn_cast<IfStmt>(child))
      this->visitedIfs[childIf] = true;

    if (isa<ForStmt>(child) || isa<WhileStmt>(child) || !this->isValidIf(child))
      return false;
  }

  return true;
}

bool InstrumentationVisitor::VisitIfStmt(IfStmt* ifStmt) {
  if (this->visitedIfs.find(ifStmt) != this->visitedIfs.end())
    return true;

  this->visitedIfs[ifStmt] = true;

  return this->isValidIf(ifStmt);
}

bool InstrumentationVisitor::containsRefToParam(clang::Stmt* node, clang::NamedDecl* decl) {
  bool result = false;

  for (auto* child : node->children()) {
    if (!child)
      continue;

    if (auto* refExpr = dyn_cast<DeclRefExpr>(child)) {
      if (auto* param = dyn_cast<ParmVarDecl>(refExpr->getFoundDecl())) {
        this->paramRefs[decl].push_back(param);
        result = true;
      }
    }

    result |= this->containsRefToParam(child, decl);
  }

  return result;
}

bool InstrumentationVisitor::VisitBinaryOperator(clang::BinaryOperator* binOp) {
  if (!binOp->isAssignmentOp())
    return true;

  if (auto* ref = dyn_cast<DeclRefExpr>(binOp->getLHS())) {
    auto* decl = ref->getFoundDecl();
    this->paramRefs[decl].clear();
    bool contains = this->containsRefToParam(binOp->getRHS(), decl);

    if (!contains)
      this->paramRefs.erase(decl);
  }

  return true;
}

bool InstrumentationVisitor::VisitVarDecl(clang::VarDecl* decl) {
  if (auto* param = dyn_cast<ParmVarDecl>(decl)) {
    this->paramRefs[param].push_back(param);
  } else if (auto* init = decl->getInit()) {
    this->paramRefs[decl].clear();
    bool contains = this->containsRefToParam(init, decl);

    if (!contains)
      this->paramRefs.erase(decl);
  }

  return true;
}

std::string InstrumentationConsumer::findFunctionName(std::string inputFile) {
  size_t start, end;
  start = inputFile.find(".h_");
  if (start == std::string::npos) {
    start = inputFile.find(".c_");
  }
  start += 3;

  end = inputFile.find(".c", start);

  return inputFile.substr(start, end - start);
}

void InstrumentationConsumer::HandleTranslationUnit(ASTContext& Context) {
  clang::SourceManager& srcMgr = this->rewriter->getSourceMgr();
  std::string inputFile = srcMgr.getFileEntryForID(srcMgr.getMainFileID())->getName().str();
  this->visitor.functionName = findFunctionName(inputFile);

  bool success = this->visitor.TraverseDecl(Context.getTranslationUnitDecl());

  if (success) {
    std::error_code error_code;
    raw_fd_ostream outFile("output/" + this->outputFile, error_code, sys::fs::FileAccess::FA_Write);
    this->rewriter->getEditBuffer(srcMgr.getMainFileID()).write(outFile);
    outFile.close();
  } else {
    errs() << "Unable to instrument the input\n";
  }
}

std::unique_ptr<ASTConsumer> InstrumentationAction::CreateASTConsumer(CompilerInstance& Compiler, StringRef InFile) {
  this->rewriter.setSourceMgr(Compiler.getSourceManager(), Compiler.getLangOpts());
  return std::make_unique<InstrumentationConsumer>(&Compiler.getASTContext(), &rewriter, outputFile);
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
    } else if (args[i] == "-help") {
      errs() << "--- Merlin plugin ---\n";
      errs() << "Arguments:\n";
      errs() << " -output-file     fileName\n";
    } else {
      unsigned DiagID = diagnostics.getCustomDiagID(DiagnosticsEngine::Error, "Invalid argument '%0'");
      diagnostics.Report(DiagID) << args[i];

      return false;
    }
  }

  return true;
}