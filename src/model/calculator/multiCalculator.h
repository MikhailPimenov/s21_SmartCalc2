#ifndef SRC_MODEL_MULTICALCULATOR_H
#define SRC_MODEL_MULTICALCULATOR_H

#include <optional>
#include <string>

#include "calculator.h"

namespace s21 {

namespace Protocol {
    struct GraphParameters;
    struct GraphResult;
}

namespace Model {

class MultiCalculator : public Calculator {
private:
    double min_;
    double max_;
    int steps_;
public:
    explicit MultiCalculator(const std::string& input, double min, double max, int steps);
    explicit MultiCalculator(const Protocol::GraphParameters& gp);

    std::optional<Protocol::GraphResult> Run();
};

}   // namespace Model

}   // namespace s21

#endif  //  SRC_MODEL_MULTICALCULATOR_H