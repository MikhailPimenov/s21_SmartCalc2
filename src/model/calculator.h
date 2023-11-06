#ifndef SRC_MODEL_CALCULATOR_H
#define SRC_MODEL_CALCULATOR_H

#include <optional>
#include <string>
#include "token.h"

namespace s21 {

class Calculator {
private:
    const std::string& input_;
    
protected:
    std::stack<Model::Token> rpn_;

protected:
    explicit Calculator(const std::string& input);

protected:
    bool getRPN();

};


class SingleCalculator : public Calculator {
private:
    double x_;
public:
    explicit SingleCalculator(const std::string& input, double x);
    std::optional<double> Run();
};

class MultiCalculator : public Calculator {
private:
    double min_;
    double max_;
    int steps_;
public:
    explicit MultiCalculator(const std::string& input, double min, double max, int steps);
    std::optional<Protocol::GraphResult> Run();
};

}   // namespace s21

#endif  //  SRC_MODEL_CALCULATOR_RPN_H