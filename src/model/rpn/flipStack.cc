#include "flipStack.h"

namespace s21 {

FlipStack::FlipStack(std::stack<Model::Token>& input) : input_{input} {}

std::stack<Model::Token> FlipStack::Run() {
  std::stack<Model::Token> output;
  while (!input_.empty()) {
    output.push(input_.top());
    input_.pop();
  }
  return output;
}

}  // namespace s21