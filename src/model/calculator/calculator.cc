#include "calculator.h"

#include "../rpn/calculatorRpn.h"

namespace s21 {

namespace Model {

Calculator::Calculator(const std::string& input, double x)
    : ett_{input}, x_{x} {}

std::optional<double> Calculator::Run() {
  if (!ett_.Run()) return std::nullopt;

  CalculatorRpn calculator(ett_.Get(), x_);
  return calculator.Run();
}

}  //  namespace Model

}  //  namespace s21