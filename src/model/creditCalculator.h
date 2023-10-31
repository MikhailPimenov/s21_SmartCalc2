#ifndef SRC_MODEL_CREDITCALCULATOR_H
#define SRC_MODEL_CREDITCALCULATOR_H

#include <optional>
#include "model.h"

namespace s21 {

class CreditCalculator {
private:

public:
    CreditCalculator(const std::string& input);
    bool Run() const;
    std::optional


};

}   // namespace s21

#endif  //  SRC_MODEL_CREDITCALCULATOR_H