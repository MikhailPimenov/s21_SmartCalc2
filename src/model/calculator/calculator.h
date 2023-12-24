#ifndef SRC_MODEL_SINGLECALCULATOR_H
#define SRC_MODEL_SINGLECALCULATOR_H

#include <optional>
#include <string>

#include "expressionToTokens.h"

namespace s21 {

namespace Model {

/**
 * @brief
 * Calculates expression using reversed polish notation
 * Convert input string to tokens
 */

class Calculator {
 private:
  ExpressionToTokens ett_;
  double x_;

 public:
  explicit Calculator(const std::string& input, double x);
  std::optional<double> Run();
};

}  // namespace Model

}  // namespace s21

#endif  //  SRC_MODEL_SINGLECALCULATOR_H