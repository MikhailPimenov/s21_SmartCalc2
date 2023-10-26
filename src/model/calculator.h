#ifndef SRC_MODEL_CALCULATOR_H
#define SRC_MODEL_CALCULATOR_H

#include <optional>
#include <string>

namespace s21 {

class Calculator {
private:
    const std::string& input_;
    double x_;

public:
    explicit Calculator(const std::string& input, double x);
    std::optional<double> Run() const;
};

}   // namespace s21

#endif  //  SRC_MODEL_CALCULATOR_RPN_H