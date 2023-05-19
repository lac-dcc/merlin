#ifndef TREE_BUILDER
#define TREE_BUILDER

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/ADT/DenseMap.h"
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
   * \param context ASTContext to be used by the visitor.
   * \param rewriter Object use to rewrite the code and add instrumentation.
   */
  explicit InsertPrintVisitor(clang::ASTContext* context, clang::Rewriter* rewriter)
      : context(context), rewriter(rewriter) {}

  bool VisitReturnStmt(clang::ReturnStmt* retStmt);

private:
  clang::ASTContext* context; ///< ASTContext to be used by the visitor.
  clang::Rewriter* rewriter;  ///< Object used to rewrite the code and add instrumentation.
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
  explicit InstrumentationVisitor(clang::ASTContext* context, clang::Rewriter* rewriter)
      : context(context), rewriter(rewriter), printVisitor(context, rewriter) {
    this->formatSpecifier = {
        {"int", "%d"}, {"unsigned int", "%u"}, {"long", "%ld"}, {"float", "%f"}, {"double", "%lf"}};
  }

  bool VisitFunctionDecl(clang::FunctionDecl* funcDecl);
  bool VisitForStmt(clang::ForStmt* forStmt);
  bool VisitWhileStmt(clang::WhileStmt* whileStmt);
  bool VisitIfStmt(clang::IfStmt* ifStmt);
  bool VisitBinaryOperator(clang::BinaryOperator* binOp);
  bool VisitVarDecl(clang::VarDecl* decl);

  /**
   * \brief Adds printf's with the counter and the tainted params to the last visited function.
   */
  void addPrints();

  /**
   * \brief Adds temporary variables that are copies of the tainted params.
   */
  void addTempVariables();

private:
  clang::ASTContext* context; ///< ASTContext to be used by the visitor.
  clang::Rewriter* rewriter;  ///< Object used to rewrite the code and add instrumentation.
  std::string counter;        ///< String that contains the name of the counter being used for instrumentation.
  clang::FunctionDecl* currFunc = nullptr; ///< Pointer to the function being currently visited

  llvm::DenseMap<clang::IfStmt*, bool> visitedIfs; ///< Map used to store visited If statements.
  llvm::DenseMap<clang::Stmt*, bool> visitedLoops; ///< Map used to store visited loops.

  /// @brief Map that associates a declaration to the parameters that it references.
  llvm::DenseMap<clang::NamedDecl*, clang::SmallVector<clang::ParmVarDecl*, 3>> paramRefs;
  llvm::DenseMap<clang::NamedDecl*, std::string> taintedVariables; ///< Map of parameters that influence some loop.

  InsertPrintVisitor printVisitor; ///< Auxiliary visitor used to add printf's before return statements.

  /// @brief Map of type names to format specifiers used in printf.
  std::unordered_map<std::string, std::string> formatSpecifier;

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
  void getTaintedVars(clang::Stmt* node);

  /**
   * \brief Checks whether a statement contains any references to a param. If so, updates the map
   * paramRefs for the given declaration.
   * \param node Statement being visited.
   * \param decl Declaration to consider when updating paramRefs.
   * 
   * \return Boolean value that is true if node contains a reference to a param.
   */
  bool containsRefToParam(clang::Stmt* node, clang::NamedDecl* decl);

  /**
   * \brief Auxiliary method used to visit loops and insert instrumentation.
   * \param loop Loop being visited.
   * \param bodyLoc SourceLocation for the beginning of the loop's body.
   */
  bool visitLoop(clang::Stmt* loop, clang::SourceLocation& bodyLoc);

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