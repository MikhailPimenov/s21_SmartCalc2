#include "parcer.h"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace s21 {

Parcer::Parcer(const std::string& input) : input_{input} {}

std::optional<std::vector<Model::Token> > Parcer::Run() const {

  std::vector<Model::Token> result;
  result.reserve(input_.size());
  
  for(int i = 0; i < input_.size(); i++) {
    const char s = input_[i];

    if (s == '(') {
      result.push_back(Model::Token(0.0, Model::Type::OpenBracket, 0));
    } else if(s == ')') {
      result.push_back(Model::Token(0.0, Model::Type::CloseBracket, 0));
    } else if (s == '+') {
      result.push_back(Model::Token(0.0, Model::Type::Sum, 6));
    } else if (s == '-') {
      result.push_back(Model::Token(0.0, Model::Type::Minus, 6));
    } else if (s == '/') {
      result.push_back(Model::Token(0.0, Model::Type::Div, 8));
    } else if (s == '*') {
      result.push_back(Model::Token(0.0, Model::Type::Mult, 8));
    } else if (s == '^') {
      result.push_back(Model::Token(0.0, Model::Type::Power, 9));
    } else if (s == 'x') {
      result.push_back(Model::Token(0.0, Model::Type::X, 1));
    }
    else if (input_.compare(i, 3, "cos") == 0) {
      result.push_back(Model::Token(0.0, Model::Type::Cos, 8));
      i += 2;
    } // else if (input_.find("cot", i)) {
    //   result.push_back(Token(0.0, Type::Cos, 8));
    //   i += 2;
    //}
    else if (input_.compare(i, 3, "sin") == 0) {
      result.push_back(Model::Token(0.0, Model::Type::Sin, 8));
      i += 2;
    } else if (input_.compare(i, 3, "mod") == 0) {
      result.push_back(Model::Token(0.0, Model::Type::Mod, 8));
      i += 2;
    } else if (input_.compare(i, 3, "tan") == 0) {
      result.push_back(Model::Token(0.0, Model::Type::Tan, 8));
      i += 2;
    } else if (input_.compare(i, 4, "acos") == 0) {
      result.push_back(Model::Token(0.0, Model::Type::Acos, 8));
      i += 3;
    } else if (input_.compare(i, 4, "asin") == 0) {
      result.push_back(Model::Token(0.0, Model::Type::Asin, 8));
      i += 3;
    } else if (input_.compare(i, 4, "atan") == 0) {
      result.push_back(Model::Token(0.0, Model::Type::Atan, 8));
      i += 3;
    } else if (input_.compare(i, 4, "sqrt") == 0) {
      result.push_back(Model::Token(0.0, Model::Type::Sqrt, 8));
      i += 3;
    } else if (input_.compare(i, 2, "ln") == 0) {
      result.push_back(Model::Token(0.0, Model::Type::Ln, 8));
      i += 1;
    } else if (input_.compare(i, 3, "log") == 0) {
      result.push_back(Model::Token(0.0, Model::Type::Log, 8));
      i += 2;
    } else if (const auto& [n, index] = number(i); index > i) {
      result.push_back(Model::Token(n, Model::Type::Number, 1));
      // std::cout << index << '\n';
      i = (index - 1);
    } else {
      return std::nullopt;
    }
  } 
  return std::optional<std::vector<Model::Token>>(result);  
}


std::pair<double, int> Parcer::number(int index) const {
  if (input_[index] == '.')
    return std::make_pair(0.0, index);

  std::istringstream iss(input_);
  iss.seekg(index);
  double result = 0.0;
  int i1 = iss.tellg();
  iss >> result;
  int i2 = iss.tellg();
  bool fail = iss.fail();
  bool eof = iss.eof();

  if (iss.eof())
    index = static_cast<int>(input_.size());
  else if (!iss.fail())
    index = static_cast<int>(iss.tellg());

    
  return std::make_pair(result, index);
 }


}   // namespace s21