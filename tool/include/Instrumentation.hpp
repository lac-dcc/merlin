#ifndef TREE_BUILDER
#define TREE_BUILDER

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/ADT/DenseMap.h"

/**
 * \class InstrumentationVisitor
 *
 * \brief Implementation of a recursive AST Visitor.
 *
 * This class implements a recursive AST Visitor, using Clang's RecursiveASTVisitor class.
 */
class InstrumentationVisitor : public clang::RecursiveASTVisitor<InstrumentationVisitor> {
public:
  llvm::DenseMap<clang::NamedDecl*, std::string> taintedVariables;

  /**
   * \brief Constructor method.
   * \param context ASTContext to be used by the visitor.
   * \param rewriter Object use to rewrite the code and add instrumentation.
   */
  explicit InstrumentationVisitor(clang::ASTContext* context, clang::Rewriter* rewriter)
      : context(context), rewriter(rewriter) {}

  bool VisitFunctionDecl(clang::FunctionDecl* funcDecl);
  bool VisitForStmt(clang::ForStmt* forStmt);
  bool VisitWhileStmt(clang::WhileStmt* whileStmt);
  bool VisitIfStmt(clang::IfStmt* ifStmt);

private:
  clang::ASTContext* context; ///< ASTContext to be used by the visitor.
  clang::Rewriter* rewriter;  ///< Object used to rewrite the code and add instrumentation.
  std::string counter;        ///< String that contains the name of the counter being used for instrumentation.
  llvm::DenseMap<clang::IfStmt*, bool> visitedIfs; ///< Map used to store visited If statements.
  llvm::DenseMap<clang::Stmt*, bool> visitedLoops; ///< Map used to store visited loops.
  llvm::DenseMap<clang::NamedDecl*, bool> checkedVars;

  void getTaintedVars(clang::Stmt* node);

  /**
   * \brief Auxiliary method used to visit loops and insert instrumentation.
   * \param loop Loop being visited.
   * \param bodyLoc SourceLocation for the beginning of the loop's body.
   */
  bool visitLoop(clang::Stmt* loop, clang::SourceLocation& bodyLoc);

  /**
   * \brief Given a location in the program, identify its level of indentation.
   * \param srcMgr SourceManager object.
   * \param loc SourceLocation to be analyzed.
   *
   * \return String with whitespaces correspondent to the location's indentation level.
   */
  std::string getIndentation(clang::SourceManager& srcMgr, clang::SourceLocation& loc);

  /**
   * \brief Recursive method used to indicate if an IfStmt is valid for instrumentation.
   * \param stmt Statement being traversed.
   */
  bool isValidIf(clang::Stmt* stmt);

  /**
   * \brief Recursive method used to indicate if a loop is valid for instrumentation.
   * \param stmt Statement being traversed.
   */
  bool isValidLoop(clang::Stmt* stmt);
};

/**
 * \class InstrumentationConsumer
 *
 * \brief Class used to write generic actions on the AST.
 */
class InstrumentationConsumer : public clang::ASTConsumer {
public:
  explicit InstrumentationConsumer(clang::ASTContext* Context, clang::Rewriter* rewriter, std::string outputFile)
      : visitor(Context, rewriter), rewriter(rewriter), outputFile(outputFile) {}

  virtual void HandleTranslationUnit(clang::ASTContext& Context);

private:
  InstrumentationVisitor visitor;
  clang::Rewriter* rewriter;
  std::string outputFile;
};

/**
 * \class InstrumentationAction
 *
 * \brief Class used to define a Clang plugin action.
 * To know more about Clang plugins: https://youtu.be/SnP-8QM-TlI
 */
class InstrumentationAction : public clang::PluginASTAction {
protected:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& Compiler,
                                                                llvm::StringRef InFile) override;

  bool ParseArgs(const clang::CompilerInstance& Compiler, const std::vector<std::string>& args) override;

private:
  clang::Rewriter rewriter;
  std::string outputFile = "output.c";
};

static clang::FrontendPluginRegistry::Add<InstrumentationAction> X("merlin",
                                                                   "Program instrumentation and cost analysis");

#endif