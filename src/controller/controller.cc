#include "controller.h"

#include "../protocol/protocol.h"

// GCOVR_EXCL_START

namespace s21 {

namespace Controller {

Calculator::Calculator(const std::string& input, double x) : model_{input, x} {

}
std::optional<double> Calculator::Run() {
  return model_.Run();
}


GraphCalculator::GraphCalculator(const Protocol::GraphParameters& gp) : model_{gp} {

}
std::optional<Protocol::GraphResult> GraphCalculator::Run() {
  return model_.Run();
}


CreditCalculator::CreditCalculator(const Protocol::CreditParameters& cp) : model_{cp} {

}
bool CreditCalculator::Run() {
  return model_.Run();
}
std::optional<Protocol::CreditResult> CreditCalculator::Get() const {
  return model_.Get();
}


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