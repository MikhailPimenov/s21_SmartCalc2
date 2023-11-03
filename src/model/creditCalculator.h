#ifndef SRC_MODEL_CREDITCALCULATOR_H
#define SRC_MODEL_CREDITCALCULATOR_H

#include <optional>
#include "model.h"
#include "../protocol/protocol.h"

namespace s21 {

class CreditCalculator {
private:
    Protocol::CreditParameters cp_;
    Protocol::CreditResult cr_;
    bool success_;

public:
    CreditCalculator(const Protocol::CreditParameters &cp);
    bool Run();
    std::optional


};

}   // namespace s21

#endif  //  SRC_MODEL_CREDITCALCULATOR_H