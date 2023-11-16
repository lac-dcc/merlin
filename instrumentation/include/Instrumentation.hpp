#ifndef INSTRUMENTATION_H
#define INSTRUMENTATION_H

#include "Loop.hpp"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallSet.h"
#include "llvm/ADT/SmallVector.h"
#include <string>
#include <unordered_map>
#include <memory>

/**
 * \class InsertPrintVisitor
 *
 * \brief Implementation of a recursive AST Visitor.
 *
 * Auxiliary visitor class used to insert printf's before returns in a function.
 */
class InsertPrintVisitor : public clang::RecursiveASTVisitor<InsertPrintVisitor> {
public:
  std::string printString;

  /**
   * \brief Constructor method.
   * \param rewriter Object use to rewrite the code and add instrumentation.
   */
  explicit InsertPrintVisitor(clang::Rewriter* rewriter) : rewriter(rewriter) {}

  bool VisitReturnStmt(clang::ReturnStmt* retStmt);

private:
  clang::Rewriter* rewriter; ///< Object used to rewrite the code and add instrumentation.
};

/**
 * \class NodeCounterVisitor
 *
 * \brief Implementation of a recursive AST Visitor.
 *
 * Auxiliary visitor class used to count the number of nodes in a function's subtree.
 */
class NodeCounterVisitor : public clang::RecursiveASTVisitor<NodeCounterVisitor> {
public:
  u_int32_t nodeCount;

  /**
   * \brief Constructor method.
   */
  explicit NodeCounterVisitor() : nodeCount(0) {}

  bool VisitStmt(clang::Stmt* stmt);
  bool VisitDecl(clang::Decl* decl);
};

/**
 * \class DependenceVisitor
 *
 * \brief Implementation of a recursive AST Visitor.
 *
 * Auxiliary visitor class used find dependencies between function parameters
 * and variables used in the function.
 */
class DependenceVisitor : public clang::RecursiveASTVisitor<DependenceVisitor> {
private:
  /**
   * \brief Checks whether a statement contains any references to a param. If so, updates the map
   * paramRefs for the given declaration.
   * \param node Statement being visited.
   * \param decl Declaration to consider when updating paramRefs.
   *
   * \return Boolean value that is true if node contains a reference to a param.
   */
  bool containsRefToParam(clang::Stmt* node, clang::NamedDecl* decl);

public:
  /// @brief Map that associates a declaration to the parameters that it references.
  llvm::DenseMap<clang::NamedDecl*, llvm::SmallVector<clang::ParmVarDecl*, 3>>* paramRefs;

  bool VisitBinaryOperator(clang::BinaryOperator* binOp);
  bool VisitVarDecl(clang::VarDecl* decl);
};

/**
 * \class InstrumentationVisitor
 *
 * \brief Implementation of a recursive AST Visitor.
 *
 * Visits the AST to insert instrumentation.
 */
class InstrumentationVisitor : public clang::RecursiveASTVisitor<InstrumentationVisitor> {
public:
  explicit InstrumentationVisitor(clang::ASTContext* context, clang::Rewriter* rewriter, bool ignoreNonNewton)
      : context(context), rewriter(rewriter), ignoreNonNewton(ignoreNonNewton) {
    this->formatSpecifier = {{"char", "%c"},           {"int", "%d"},   {"unsigned int", "%u"}, {"long", "%ld"},
                             {"unsigned long", "%ld"}, {"float", "%f"}, {"double", "%f"}};
  }

  bool VisitFunctionDecl(clang::FunctionDecl* funcDecl);
  bool VisitDoStmt(clang::DoStmt* doStmt);
  bool VisitForStmt(clang::ForStmt* forStmt);
  bool VisitWhileStmt(clang::WhileStmt* whileStmt);
  bool VisitIfStmt(clang::IfStmt* ifStmt);

  /**
   * \brief Adds printf's with the counter and the tainted params to the last visited function.
   */
  void addPrints();

  /**
   * \brief Adds temporary variables that are copies of the tainted params.
   */
  void addTempVariables();

  std::string functionName; ///< Name of the function to be instrumented.

private:
  clang::ASTContext* context; ///< ASTContext to be used by the visitor.
  clang::Rewriter* rewriter;  ///< Object used to rewrite the code and add instrumentation.
  clang::FunctionDecl* currFunc = nullptr; ///< Pointer to the function being currently visited.
  u_int32_t instrumentedLoops; ///< Counter for the number of instrumented loops.

  /// @brief Map that associates a loop statement node with its Loop object.
  llvm::DenseMap<clang::Stmt*, std::shared_ptr<Loop>> loopMap;

  llvm::SmallSet<clang::IfStmt*, 3> visitedIfs; ///< Set of visited if statements.

  /// @brief Map that associates a declaration to the parameters that it references.
  llvm::DenseMap<clang::NamedDecl*, llvm::SmallVector<clang::ParmVarDecl*, 3>> paramRefs;

  /// @brief Map of type names to format specifiers used in printf.
  std::unordered_map<std::string, std::string> formatSpecifier;

  bool ignoreNonNewton; ///< Flag that determines if non-Newton programs are instrumented

  /**
   * \brief Generate the string with the printf statement to be added to the function.
   *
   * \return String with the printf statement to be added to the function.
   */
  std::string getPrintString();

  /**
   * \brief Gets all controlling variables for a given loop that appear in a statement
   * and updates the loop's controlVariables set.
   * \param node Statement being considered.
   * \param loop Loop object to.
   */
  void getControlVars(clang::Stmt* node, std::shared_ptr<Loop> loop);

  /**
   * \brief Determines if a Stmt node is a loop.
   * \param stmt Statement being considered.
   *
   * \return Boolean value that indicates whether the node is a loop.
   */
  bool isLoop(clang::Stmt* stmt);

  /**
   * \brief Auxiliary method used to create the Loop instance for a given loop
   * and its children. It also validates the loop when needed.
   * \param loop Loop being considered.
   * \param bodyLoc SourceLocation for the beginning of the loop's body.
   */
  bool createAndInstrumentLoop(clang::Stmt* loop, clang::SourceLocation& bodyLoc);

  /**
   * \brief Recursive method used to validate if a loop is valid for instrumentation.
   * \param stmt Statement being traversed.
   * \param loop Current outermost loop.
   *
   * \return Boolean value that indicates if the loop is valid
   */
  bool validateLoop(clang::Stmt* stmt, clang::Stmt* loop);

  /**
   * \brief Recursive method used to validate if an IfStmt is valid for instrumentation.
   * \param stmt Statement being traversed.
   *
   * \return Boolean value that indicates if the IfStmt is valid
   */
  bool validateIf(clang::Stmt* stmt);
};

/**
 * \class InstrumentationConsumer
 *
 * \brief Class used to write generic actions on the AST.
 */
class InstrumentationConsumer : public clang::ASTConsumer {
public:
  explicit InstrumentationConsumer(clang::ASTContext* Context, clang::Rewriter* rewriter, std::string outputFile,
                                   std::string targetFunction, bool ignoreNonNewton, bool measureTime)
      : visitor(Context, rewriter, ignoreNonNewton), rewriter(rewriter), outputFile(outputFile),
        targetFunction(targetFunction), measureTime(measureTime) {}

  virtual void HandleTranslationUnit(clang::ASTContext& Context);

private:
  InstrumentationVisitor visitor;
  clang::Rewriter* rewriter;
  std::string outputFile;
  std::string targetFunction;
  bool measureTime;
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
  std::string targetFunction = "main";
  bool ignoreNonNewton = false;
  bool measureTime = false;
};

static clang::FrontendPluginRegistry::Add<InstrumentationAction> X("merlin",
                                                                   "Program instrumentation and cost analysis");

#endif