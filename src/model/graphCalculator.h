#ifndef SRC_MODEL_GRAPH_CALCULATOR_H
#define SRC_MODEL_GRAPH_CALCULATOR_H

#include "model.h"
#include "../protocol/protocol.h"
#include <optional>

namespace s21 {

class GraphCalculator {
private:
    std::stack<Model::Token> rpn_;
    double minX_;
    double maxX_;
    int numberOfPoints_;

public:
    GraphCalculator(std::stack<Model::Token> rpn, double min = -30.0, double max = 30.0, int n = 10000);
    std::optional<Protocol::GraphResult> Run();

// private:
//     static double unaryFnCalc(double number1, Model::Type type);
//     static double binaryFnCalc(double number1, double number2, Model::Type type);
};

}   // namespace s21

#endif  //  SRC_MODEL_GRAPH_CALCULATOR_H