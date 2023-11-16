#include "Loop.hpp"

void Loop::verifyAndSetIsConstantLoop() {
  if (this->controlVariables.empty()) {
    // The loop isn't directly controlled by any parameter, so we assume that it
    // is constant.
    this->isConstantLoop = true;
  }
}

void Loop::computeNestingDepth() {
  u_int32_t nestingDepth = this->parent ? this->parent->nestingDepth : 0;

  if (!this->isConstantLoop)
    nestingDepth++;

  this->nestingDepth = nestingDepth;
}

void Loop::takeParentControlVars() {
  if (this->parent == nullptr)
    return;

  const auto& parentControlVars = this->parent->controlVariables;
  for (auto* controlVar : parentControlVars) {
    this->controlVariables.insert(controlVar);
  }
}
