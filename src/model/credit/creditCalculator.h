#ifndef SRC_MODEL_CREDITCALCULATOR_H
#define SRC_MODEL_CREDITCALCULATOR_H

#include <optional>

#include "../../protocol/protocol.h"

namespace s21 {

namespace Model {

/**
 * @brief Calculates credit
 *
 * @param cp Input parameters
 * @param cr Calculated result
 * @param bool true if success, false if incorrent input
 */

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
  CreditCalculator(const Protocol::CreditParameters& cp);
  bool Run();
  std::optional<Protocol::CreditResult> Get() const;
};

}  // namespace Model

}  // namespace s21

#endif  //  SRC_MODEL_CREDITCALCULATOR_H