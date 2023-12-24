#ifndef SRC_MODEL_CALCULATOR_RPN_H
#define SRC_MODEL_CALCULATOR_RPN_H

#include <optional>
#include <stack>

#include "../parcer/token.h"

namespace s21 {

/**
 * @brief Calculator Rpn
 *
 * Defines a type in std::stack operator, bracket or operand
 * Converts a string into tokens and adds tockens into std::vector
 *
 * @param parameters Input parameters
 */

class CalculatorRpn {
 private:
  std::stack<Model::Token> rpn_;
  double x_;

 public:
  explicit CalculatorRpn(std::stack<Model::Token> rpn, double x = 0.0);
  std::optional<double> Run();

 private:
  static double unaryFnCalc(double number1, Model::Type type);
  static double binaryFnCalc(double number1, double number2, Model::Type type);
};

}  // namespace s21

#endif  //  SRC_MODEL_CALCULATOR_RPN_H