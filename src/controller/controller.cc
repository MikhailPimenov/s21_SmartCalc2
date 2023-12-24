#include "controller.h"

#include "../protocol/protocol.h"

// GCOVR_EXCL_START

namespace s21 {

namespace Controller {

/**
 * @brief Calculator
 *
 * @param inpur Input parameters
 * @param x X-parametr
 * @return true if success
 * @return false if failed (incorrect input)
 */

Calculator::Calculator(const std::string& input, double x) : model_{input, x} {

}
std::optional<double> Calculator::Run() {
  return model_.Run();
}


/**
 * @brief Shows Graph
 * Plots a graph of a function
 * 
 * @param gp Input parameters
 * @param gr Calculated result
 * @return true if success
 * @return false if failed (incorrect input)
 */

GraphCalculator::GraphCalculator(const Protocol::GraphParameters& gp) : model_{gp} {

}
std::optional<Protocol::GraphResult> GraphCalculator::Run() {
  return model_.Run();
}

/**
 * @brief Calculates credit
 *
 * @param cp Input parameters
 * @param cr Calculated result
 * @return true if success
 * @return false if failed (incorrect input)
 */

CreditCalculator::CreditCalculator(const Protocol::CreditParameters& cp) : model_{cp} {

}
bool CreditCalculator::Run() {
  return model_.Run();
}
std::optional<Protocol::CreditResult> CreditCalculator::Get() const {
  return model_.Get();
}

/**
 * @brief Calculates deposit
 *
 * @param parameters Input parameters
 * @param result Calculated result
 * @return true if success
 * @return false if failed (incorrect input)
 */

DepositCalculator::DepositCalculator(const Protocol::DepositParameters& cp) : model_{cp} {

}

bool DepositCalculator::Run() {
  return model_.Run();
}

std::optional<Protocol::DepositResult> DepositCalculator::Get() const {
  return model_.Get();
}

} // namespace Controller

}  // namespace s21

// GCOVR_EXCL_STOP