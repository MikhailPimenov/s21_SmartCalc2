#include "graphCalculator.h"
#include "../rpn/multiCalculatorRpn.h"
#include "../../protocol/protocol.h"

namespace s21 {

namespace Model {

GraphCalculator::GraphCalculator(const std::string& input, double min, double max, int steps)
    : ett_{input}, min_{min}, max_{max}, steps_{steps} {

}

GraphCalculator::GraphCalculator(const Protocol::GraphParameters& gp)  
    : GraphCalculator{gp.input_string, gp.x_min, gp.x_max, gp.steps} {

}

std::optional<Protocol::GraphResult> GraphCalculator::Run() {
  if (!ett_.Run())
    return std::nullopt;

  MultiCalculatorRpn multiCalculatorRpn(ett_.Get(), min_, max_, steps_);
  return multiCalculatorRpn.Run();
}

}   //  namespace Model

}   //  namespace s21