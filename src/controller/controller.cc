#include "controller.h"

#include "../protocol/protocol.h"

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





// Controller::Controller(Model *model) : model_{model} {}

// int Controller::Calculate(const std::string &input_str, double *result,
//                           double x_value) {
//   return model_->Calculate(input_str, result, x_value);
// }

// int Controller::CalculateGraph(const Protocol::GraphParameters &gp,
//                                Protocol::GraphResult &gr) {
//   return model_->CalculateGraph(gp, gr);
// }

// bool Controller::CalculateCredit(const Protocol::CreditParameters &cp,
//                                  Protocol::CreditResult &cr) {
//   return model_->CalculateCredit(cp, cr);
// }

// bool Controller::CalculateDeposit(const Protocol::DepositParameters &dp,
//                                   Protocol::DepositResult &dr) {
//   return model_->CalculateDeposit(dp, dr);
// }

}  // namespace s21