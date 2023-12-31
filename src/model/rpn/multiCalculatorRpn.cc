#include "multiCalculatorRpn.h"

#include <cmath>

#include "../rpn/calculatorRpn.h"

namespace s21 {

namespace Model {

MultiCalculatorRpn::MultiCalculatorRpn(std::stack<Model::Token> rpn,
                                       double min /* = -30.0 */,
                                       double max /* = 30.0 */,
                                       int n /* = 10000 */)
    : rpn_{rpn}, minX_{min}, maxX_{max}, numberOfPoints_{n} {}

std::optional<Protocol::GraphResult> MultiCalculatorRpn::Run() {
  const double step = abs(maxX_ - minX_) / static_cast<double>(numberOfPoints_);

  Protocol::GraphResult gr;
  gr.x.resize(numberOfPoints_);
  gr.y.resize(numberOfPoints_);
  for (int i = 0; i < numberOfPoints_; ++i) {
    gr.x[i] = minX_ + step * i;

    CalculatorRpn calculator(rpn_, gr.x[i]);
    const std::optional<double> result = calculator.Run();
    if (!result.has_value()) return std::nullopt;
    gr.y[i] = result.value();
  }
  return std::optional<Protocol::GraphResult>(gr);
}

}  // namespace Model

}  // namespace s21