#ifndef SRC_MODEL_CALCULATOR_RPN_H
#define SRC_MODEL_CALCULATOR_RPN_H

// #include "model.h"
#include <optional>
#include <stack>
#include "token.h"

namespace s21 {

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

}   // namespace s21

#endif  //  SRC_MODEL_CALCULATOR_RPN_H