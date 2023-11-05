#ifndef SRC_MODEL_CREDITCALCULATOR_H
#define SRC_MODEL_CREDITCALCULATOR_H

#include <optional>
#include "model.h"
#include "../protocol/protocol.h"

namespace s21 {

namespace Model {

class CreditCalculator {
private:
    Protocol::CreditParameters cp_;
    Protocol::CreditResult cr_;
    bool success_;

    class InputChecker {
    private:
        CreditCalculator& owner_;
    public:
        InputChecker(CreditCalculator& owner);
        bool Run() const;
    };


public:
    CreditCalculator(const Protocol::CreditParameters &cp);
    bool Run();
    std::optional<Protocol::CreditResult> Get() const;

};

}   // namespace Model

}   // namespace s21

#endif  //  SRC_MODEL_CREDITCALCULATOR_H