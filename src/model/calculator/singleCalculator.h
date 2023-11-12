#ifndef SRC_MODEL_SINGLECALCULATOR_H
#define SRC_MODEL_SINGLECALCULATOR_H

#include <optional>
#include <string>

#include "calculator.h"

namespace s21 {

namespace Model {

class SingleCalculator : public Calculator {
private:
    double x_;
public:
    explicit SingleCalculator(const std::string& input, double x);
    std::optional<double> Run();
};

}   // namespace Model

}   // namespace s21

#endif  //  SRC_MODEL_SINGLECALCULATOR_H