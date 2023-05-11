#include "Instrumentation.hpp"

using namespace clang;
using namespace llvm;

std::string InstrumentationVisitor::getIndentation(SourceManager& srcMgr, SourceLocation& loc) {
  SourceLocation lineStart = srcMgr.translateLineCol(srcMgr.getFileID(loc), srcMgr.getSpellingLineNumber(loc), 1);
  const char* startPtr = srcMgr.getCharacterData(lineStart);
  char* endPtr = const_cast<char*>(startPtr);
  while (endPtr && *endPtr == ' ' || *endPtr == '\t')
    ++endPtr;
  return std::string(startPtr, endPtr - startPtr);
}

bool InstrumentationVisitor::VisitFunctionDecl(FunctionDecl* funcDecl) {
  this->counter = "counter" + funcDecl->getNameAsString();
  std::string counterDeclaration = "int " + this->counter + " = 0;\n";
  this->rewriter->InsertText(funcDecl->getBeginLoc(), counterDeclaration, true, true);

  return true;
}

bool InstrumentationVisitor::visitLoop(Stmt* loop, SourceLocation& bodyLoc) {
  if (this->visitedLoops.find(loop) == this->visitedLoops.end()) {
    this->visitedLoops[loop] = true;
    if (!this->isValidLoop(loop))
      return false;
  }

  SourceLocation beginLoc = loop->getBeginLoc();
  SourceManager& srcMgr = this->rewriter->getSourceMgr();
  std::string increment = "\n" + this->getIndentation(srcMgr, beginLoc) + this->counter + "++;";
  this->rewriter->InsertTextAfterToken(bodyLoc, increment);

  return true;
}

bool InstrumentationVisitor::VisitWhileStmt(WhileStmt* whileStmt) {
  SourceLocation bodyLoc = whileStmt->getBody()->getBeginLoc();

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

void InstrumentationConsumer::HandleTranslationUnit(ASTContext& Context) {
  bool success = this->visitor.TraverseDecl(Context.getTranslationUnitDecl());

  if (success) {
    SourceManager& srcMgr = this->rewriter->getSourceMgr();
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