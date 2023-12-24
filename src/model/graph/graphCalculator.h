#ifndef SRC_MODEL_MULTICALCULATOR_H
#define SRC_MODEL_MULTICALCULATOR_H

#include <optional>
#include <string>

#include "../calculator/expressionToTokens.h"

namespace s21 {

namespace Protocol {
    struct GraphParameters;
    struct GraphResult;
}

namespace Model {

/**
 * @brief Plot a graph
 *
 * Calculates graph from model
 * Using dots with steps to show a praph
 * Can scale two axes: x and y
 */

class GraphCalculator {
private:
    ExpressionToTokens ett_;
    double min_;
    double max_;
    int steps_;

public:
    explicit GraphCalculator(const std::string& input, double min, double max, int steps);
    explicit GraphCalculator(const Protocol::GraphParameters& gp);

    std::optional<Protocol::GraphResult> Run();
};

}   // namespace Model

}   // namespace s21

#endif  //  SRC_MODEL_MULTICALCULATOR_H