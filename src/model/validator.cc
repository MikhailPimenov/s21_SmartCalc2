#include "validator.h"
#include <iostream>


namespace s21 {

Validator::Validator(const std::vector<Model::Token>& input) : input_{input} {}


bool Validator::isUnaryLeftFunction(const Model::Token& token) {
  return token.type == Model::Type::Sum ||
         token.type == Model::Type::Minus;
}

bool Validator::isOpeningBrace(const Model::Token& token) {
  return token.type == Model::Type::OpenBracket;
}


bool Validator::isBinaryFunction(const Model::Token& token) {
  return token.type == Model::Type::Sum ||
         token.type == Model::Type::Minus ||
         token.type == Model::Type::Mult ||
         token.type == Model::Type::Div ||
         token.type == Model::Type::Mod ||
         token.type == Model::Type::Power;
}



bool Validator::isUnaryRightFunction(const Model::Token& token) {
  return token.type == Model::Type::Asin ||
         token.type == Model::Type::Acos ||
         token.type == Model::Type::Atan ||
         token.type == Model::Type::Sqrt ||
         token.type == Model::Type::Sin ||
         token.type == Model::Type::Cos ||
         token.type == Model::Type::Tan ||
         token.type == Model::Type::Log ||
         token.type == Model::Type::Ln;
}

bool Validator::isOperand(const Model::Token& token) {
  return token.type == Model::Type::Number ||
         token.type == Model::Type::X;
}

bool Validator::isClosingBrace(const Model::Token& token) {
  return token.type == Model::Type::CloseBracket;
}




bool Validator::validateBraces() const {
  bool isPreviousOpen = false;
  for (const Model::Token& token : input_) {
    if (isOpeningBrace(token)) {
      isPreviousOpen = true;
    }
    else if (isClosingBrace(token)) {
      if (isPreviousOpen)
        return false;
    } else if (isOperand(token)) {
      isPreviousOpen = false;
    }
  }
  std::stack<Model::Token> stack;


  for (const Model::Token& token : input_) {
    if (!isOpeningBrace(token) && !isClosingBrace(token))
      continue;

    if (isOpeningBrace(token))
      stack.push(token);
    if (isClosingBrace(token)) {
      if (stack.empty())
        return false;
      else
        stack.pop();
    }
  }

  return stack.empty(); 
}

bool Validator::validateBinary() const {
  if (isBinaryFunction(input_.front()) && !isUnaryLeftFunction(input_.front()))
    return false;

  for (int i = 1; i < input_.size() - 1; ++i) {
    if (!isBinaryFunction(input_[i]) || isUnaryLeftFunction(input_[i]))
      continue;
    if (!isOperand(input_[i - 1]) && !isClosingBrace(input_[i - 1]))
      return false;
    if (!isOperand(input_[i + 1]) && !isOpeningBrace(input_[i + 1]) && !isUnaryRightFunction(input_[i + 1]))
      return false;
  }
  if (isBinaryFunction(input_.back()))
    return false;
  if (isUnaryRightFunction(input_.back()))
    return false;

  return true;
}

bool Validator::validateUnary() const {
  for (int i = 1; i < input_.size(); ++i)
    if (isUnaryLeftFunction(input_[i]) && isUnaryLeftFunction(input_[i - 1]))
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
