#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include <string>
#include <vector>

#include "../model/calculator.h"
#include "../model/graphCalculator.h"

namespace s21 {


namespace Controller {

class Calculator {
private:
  Model::Calculator model_;
public:
  Calculator(const std::string& input, double x);
  std::optional<double> Run();

}

namespace Protocol {
  struct GraphParameters;
  struct GraphResult;
}

class GraphCalculator {
private:
  Model::GraphCalculator model_;
public:
  GraphCalculator(const Protocol::GraphParameters& gp);
  std::optional<Protocol::GraphResult> Run();
}

}  //  namespace Controller

}  //  namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H