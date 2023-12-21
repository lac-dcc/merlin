#ifndef LOOP_H
#define LOOP_H

#include "clang/AST/Decl.h"
#include "llvm/ADT/SmallSet.h"
#include <memory>
#include <string>
#include <sys/types.h>

/**
 * \struct Loop
 *
 * \brief Structure that represents a loop.
 *
 * This structure represents a loop (for, while or do-while) in the program. It
 * contains all attributes relevant for instrumentation that are associated with
 * this loop.
 */
struct Loop {
  Loop(std::shared_ptr<Loop> parent, unsigned int line) : parent(parent), line(line) {}

  /**
   * \brief Verifies if the loop is constant and, if so, sets the isConstantLoop
   * attribute to true.
   */
  void verifyAndSetIsConstantLoop();

  /**
   * \brief Computes the predicted nesting depth for the loop. Should be called
   * before the parent's controlling variables are taken.
   */
  void computeNestingDepth();

  /**
   * \brief Gets all controlling variables from the loop's parent and updates the child's
   * controlVariables set.
   */
  void takeParentControlVars();

  std::shared_ptr<Loop> parent;                            ///< Pointer to the parent loop, if there is any.
  llvm::SmallSet<clang::ParmVarDecl*, 3> controlVariables; ///< Set of variables that control the loop's complexity.
  u_int32_t nestingDepth;                                  ///< Nesting depth for this loop.
  bool isConstantLoop = false;                             ///< Flag to indicate if the loop is constant.
  std::string counterName;                                 ///< Name of the counter used to instrument the loop.
  unsigned int line;                                       ///< Line where the loop is in the source code.
};

#endif
