#ifndef SRC_MODEL_DEPOSITCALCULATOR_H
#define SRC_MODEL_DEPOSITCALCULATOR_H

#include <optional>
#include "../../protocol/protocol.h"

namespace s21 {

namespace Model {

class DepositCalculator {
private:
    Protocol::DepositParameters dp_;
    Protocol::DepositResult dr_;
    bool success_;

    class InputChecker {
    private:
        DepositCalculator& owner_;
    public:
        InputChecker(DepositCalculator& owner);
        bool Run() const;
    };


public:
    DepositCalculator(const Protocol::DepositParameters &cp);
    bool Run();
    std::optional<Protocol::DepositResult> Get() const;
};

}   // namespace Model

}   // namespace s21

#endif  //  SRC_MODEL_DEPOSITCALCULATOR_H