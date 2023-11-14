#include "multiCalculator.h"
#include "../../protocol/protocol.h"
#include "../graph/graphCalculator.h"

namespace s21 {

namespace Model {

MultiCalculator::MultiCalculator(const std::string& input, double min, double max, int steps)
    : Calculator{input}, min_{min}, max_{max}, steps_{steps} {

}

MultiCalculator::MultiCalculator(const Protocol::GraphParameters& gp)  
    : MultiCalculator{gp.input_string, gp.x_min, gp.x_max, gp.steps} {

}

std::optional<Protocol::GraphResult> MultiCalculator::Run() {
  if (!getRPN())
    return std::nullopt;

  GraphCalculator graphCalculator(rpn_, min_, max_, steps_);
  return graphCalculator.Run();
}

}   //  namespace Model

}   //  namespace s21