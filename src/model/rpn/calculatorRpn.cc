#include "calculatorRpn.h"

#include <cmath>

namespace s21 {

CalculatorRpn::CalculatorRpn(std::stack<Model::Token> rpn, double x /* = 0.0 */)
    : rpn_{rpn}, x_{x} {}

std::optional<double> CalculatorRpn::Run() {
  double result = 0.0;
  std::stack<Model::Token> stack;
  while (!rpn_.empty()) {
    if (rpn_.top().type_ == Model::Type::Number) {
      stack.push(rpn_.top());
      rpn_.pop();
    } else if (rpn_.top().type_ == Model::Type::X) {
      rpn_.top().value_ = x_;
      stack.push(rpn_.top());
      rpn_.pop();
    } else if (rpn_.top().type_ >= Model::Type::Sum &&
               rpn_.top().type_ <= Model::Type::Mod && !stack.empty()) {
      double number2 = stack.top().value_;
      stack.pop();
      if (stack.empty()) return std::nullopt;
      result = binaryFnCalc(stack.top().value_, number2, rpn_.top().type_);
      stack.pop();
      rpn_.pop();
      stack.push(Model::Token(result, Model::Type::Number, 1));
    } else if (rpn_.top().type_ >= Model::Type::Cos && !stack.empty()) {
      result = unaryFnCalc(stack.top().value_, rpn_.top().type_);
      stack.pop();
      rpn_.pop();
      stack.push(Model::Token(result, Model::Type::Number, 1));
    }
  }
  if (!stack.empty()) result = stack.top().value_;
  stack.pop();
  return result;
}

double CalculatorRpn::unaryFnCalc(double number1, Model::Type type) {
  double result = 0;
  if (type == Model::Type::Cos) result = std::cos(number1);
  if (type == Model::Type::Sin) result = std::sin(number1);
  if (type == Model::Type::Tan) result = std::tan(number1);
  if (type == Model::Type::Acos) result = std::acos(number1);
  if (type == Model::Type::Asin) result = std::asin(number1);
  if (type == Model::Type::Atan) result = std::atan(number1);
  if (type == Model::Type::Sqrt) result = std::sqrt(number1);
  if (type == Model::Type::Ln) result = std::log(number1);
  if (type == Model::Type::Log) result = std::log10(number1);
  return result;
}

double CalculatorRpn::binaryFnCalc(double number1, double number2,
                                   Model::Type type) {
  double result = 0;
  if (type == Model::Type::Sum) result = number1 + number2;
  if (type == Model::Type::Minus) result = number1 - number2;
  if (type == Model::Type::Mult) result = number1 * number2;
  if (type == Model::Type::Div) result = number1 / number2;
  if (type == Model::Type::Power) result = std::pow(number1, number2);
  if (type == Model::Type::Mod) result = std::fmod(number1, number2);
  return result;
}

}  // namespace s21