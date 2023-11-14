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
  Loop(u_int32_t depth) : nestingDepth(depth) {}

  Loop(u_int32_t depth, std::shared_ptr<Loop> parent) : nestingDepth(depth), parent(parent) {}

  std::shared_ptr<Loop> parent = nullptr;                  ///< Pointer to the parent loop, if there is any.
  llvm::SmallSet<clang::ParmVarDecl*, 3> controlVariables; ///< Set of variables that control the loop's complexity.
  u_int32_t nestingDepth;                                  ///< Nesting depth for this loop.
};

#endif