#include "shuntingYard.h"

namespace s21 {

ShuntingYard::ShuntingYard(std::stack<Model::Token> &input) : input_{input} {}

std::stack<Model::Token> ShuntingYard::Run() {
  std::stack<Model::Token> stack;
  std::stack<Model::Token> output;
  while (!input_.empty()) {
    if (input_.top().type_ == Model::Type::Number ||
        input_.top().type_ == Model::Type::X) {
      output.push(input_.top());
      input_.pop();
    } else if (input_.top().type_ == Model::Type::OpenBracket) {
      stack.push(input_.top());
      input_.pop();
    } else if (input_.top().type_ == Model::Type::CloseBracket) {
      while (!stack.empty() && stack.top().type_ != Model::Type::OpenBracket) {
        output.push(stack.top());
        stack.pop();
      }
      stack.pop();
      if (!stack.empty() && static_cast<int>(stack.top().type_) > 10) {
        output.push(stack.top());
        stack.pop();
      }
      input_.pop();
    } else if (static_cast<int>(input_.top().type_) >=
                   static_cast<int>(Model::Type::Sum) &&
               static_cast<int>(input_.top().type_) <=
                   static_cast<int>(Model::Type::Mod) &&
               input_.top().type_ != Model::Type::Power) {
      while (!stack.empty() &&
             (stack.top().precedence_ >= input_.top().precedence_)) {
        output.push(stack.top());
        stack.pop();
      }
      stack.push(input_.top());
      input_.pop();
    } else if (input_.top().type_ == Model::Type::Power) {
      while (!stack.empty() &&
             (stack.top().precedence_ > input_.top().precedence_)) {
        output.push(stack.top());
        stack.pop();
      }
      stack.push(input_.top());
      input_.pop();
    } else if (static_cast<int>(input_.top().type_) >=
               static_cast<int>(Model::Type::Cos)) {
      stack.push(input_.top());
      input_.pop();
    }
  }
  while (!stack.empty()) {
    output.push(stack.top());
    stack.pop();
  }
  return output;
}

}  // namespace s21