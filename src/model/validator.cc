#include "validator.h"
#include <iostream>


namespace s21 {

Validator::Validator(const std::vector<Model::Token>& input) : input_{input} {}







bool Validator::validateBraces() const {
  bool isPreviousOpen = false;
  for (const Model::Token& token : input_) {
    if (token.isOpeningBrace()) {
      isPreviousOpen = true;
    }
    else if (token.isClosingBrace()) {
      if (isPreviousOpen)
        return false;
    } else if (token.isOperand()) {
      isPreviousOpen = false;
    }
  }
  std::stack<Model::Token> stack;


  for (const Model::Token& token : input_) {
    if (!token.isOpeningBrace() && !token.isClosingBrace())
      continue;

    if (token.isOpeningBrace())
      stack.push(token);
    if (token.isClosingBrace()) {
      if (stack.empty())
        return false;
      else
        stack.pop();
    }
  }

  return stack.empty(); 
}

bool Validator::validateBinary() const {
  if (input_.front().isBinaryFunction() && !input_.front().isUnaryLeftFunction())
    return false;

  for (int i = 1; i < input_.size() - 1; ++i) {
    if (!input_[i].isBinaryFunction() || input_[i].isUnaryLeftFunction())
      continue;
    if (!input_[i - 1].isOperand() && !input_[i - 1].isClosingBrace())
      return false;
    if (!input_[i + 1].isOperand() && !input_[i + 1].isOpeningBrace() && !input_[i + 1].isUnaryRightFunction())
      return false;
  }
  if (input_.back().isBinaryFunction())
    return false;
  if (input_.back().isUnaryRightFunction())
    return false;

  return true;
}

bool Validator::validateUnary() const {
  for (int i = 1; i < input_.size(); ++i)
    if (input_[i].isUnaryLeftFunction() && input_[i - 1].isUnaryLeftFunction())
      return false;

  return true;
}


bool Validator::Run() const {
    // bool Model::validate(const std::vector<Model::Token>& tokens) {
  if (!validateBinary())
    return false;

  if (!validateBraces())
    return false;

  if (!validateUnary())
    return false;

  return true;  
}


}   // namespace s21