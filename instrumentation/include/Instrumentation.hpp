#ifndef INSTRUMENTATION_H
#define INSTRUMENTATION_H

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
  /**
   * \brief Constructor method.
   * \param context ASTContext to be used by the visitor.
   * \param rewriter Object use to rewrite the code and add instrumentation.
   */
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

  u_int32_t maxNestingDepth = 0; ///< Maximum loop nesting depth

private:
  clang::ASTContext* context; ///< ASTContext to be used by the visitor.
  clang::Rewriter* rewriter;  ///< Object used to rewrite the code and add instrumentation.
  /// @brief Vector with the names of the counters used for instrumentation.
  llvm::DenseMap<clang::Stmt*, std::string> counters;
  clang::FunctionDecl* currFunc = nullptr; ///< Pointer to the function being currently visited.

  llvm::DenseMap<clang::Stmt*, clang::Stmt*> parentLoops; ///< Map that associates nested loops with their parents
  llvm::SmallSet<clang::Stmt*, 3> visitedLoops;           ///< Set of visited loops.

  llvm::SmallSet<clang::IfStmt*, 3> visitedIfs; ///< Set of visited if statements.

  /// @brief Map that associates a declaration to the parameters that it references.
  llvm::DenseMap<clang::NamedDecl*, llvm::SmallVector<clang::ParmVarDecl*, 3>> paramRefs;
  /// @brief Map that associates a loop with all function parameters that control it.
  llvm::DenseMap<clang::Stmt*, llvm::SmallSet<clang::ParmVarDecl*, 3>> controlVariables;

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
   * \brief Gets all tainted params for a given statement and updates the taintedVars map.
   * \param node Statement being considered.
   */
  void getControlVars(clang::Stmt* node, clang::Stmt* loop);

  /**
   * \brief Gets all tainted params for a given statement and updates the taintedVars map.
   * \param node Statement being considered.
   */
  void getParentControlVars(clang::Stmt* loop);

  /**
   * \brief Determines if a Stmt node is a loop.
   *
   * \return Boolean value that indicates whether the node is a loop.
   */
  bool isLoop(clang::Stmt* stmt);

  /**
   * \brief Auxiliary method used to visit loops and insert instrumentation.
   * \param loop Loop being visited.
   * \param bodyLoc SourceLocation for the beginning of the loop's body.
   */
  bool visitLoop(clang::Stmt* loop, clang::SourceLocation& bodyLoc);

  /**
   * \brief Recursive method used to validate if a loop is valid for instrumentation.
   *        Also identifies the maximum depth nesting for this loop.
   * \param stmt Statement being traversed.
   * \param loop Current outermost loop.
   * \param nestingDepth Current loop nesting depth.
   * \param maxDepth Maximum nesting depth for this loop.
   *
   * \return Boolean value that indicates if the loop is valid
   */
  bool validateLoop(clang::Stmt* stmt, clang::Stmt* loop, u_int32_t nestingDepth, u_int32_t& maxDepth);

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
                                   std::string targetFunction, bool ignoreNonNewton)
      : visitor(Context, rewriter, ignoreNonNewton), rewriter(rewriter), outputFile(outputFile),
        targetFunction(targetFunction) {}

  virtual void HandleTranslationUnit(clang::ASTContext& Context);

private:
  InstrumentationVisitor visitor;
  clang::Rewriter* rewriter;
  std::string outputFile;
  std::string targetFunction;
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
};

static clang::FrontendPluginRegistry::Add<InstrumentationAction> X("merlin",
                                                                   "Program instrumentation and cost analysis");

#endif