#ifndef SRC_MODEL_GRAPH_CALCULATOR_H
#define SRC_MODEL_GRAPH_CALCULATOR_H

#include <optional>

#include "../../protocol/protocol.h"
#include "../parcer/token.h"

namespace s21 {

namespace Model {

class MultiCalculatorRpn {
 private:
  std::stack<Model::Token> rpn_;
  double minX_;
  double maxX_;
  int numberOfPoints_;

 public:
  MultiCalculatorRpn(std::stack<Model::Token> rpn, double min = -30.0,
                     double max = 30.0, int n = 10000);
  std::optional<Protocol::GraphResult> Run();
};

}  //  namespace Model

}  //  namespace s21

#endif  //  SRC_MODEL_GRAPH_CALCULATOR_H