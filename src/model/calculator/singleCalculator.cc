#include "singleCalculator.h"
#include "../rpn/calculatorRpn.h"

namespace s21 {

namespace Model {

SingleCalculator::SingleCalculator(const std::string& input, double x) : Calculator{input}, x_{x} {

}

std::optional<double> SingleCalculator::Run() {
  if (!getRPN())
    return std::nullopt;

  CalculatorRpn calculator(rpn_, x_);
  return calculator.Run();
}

}   //  namespace Model

}   //  namespace s21