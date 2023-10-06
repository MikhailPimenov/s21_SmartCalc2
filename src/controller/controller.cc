#include "controller.h"

#include "../model/model.h"
#include "../protocol/protocol.h"

namespace s21 {

Controller::Controller(Model *model) : model_{model} {}

int Controller::Calculate(const std::string &input_str, double *result, double x_value) {
  return model_->Calculate(input_str, result, x_value);
}

int Controller::CalculateGraph(const Protocol::GraphParameters &gp, Protocol::GraphResult &gr) {
  return model_->CalculateGraph(gp, gr);
}

bool Controller::CalculateCredit(const Protocol::CreditParameters &cp, Protocol::CreditResult &cr) {
  return model_->CalculateCredit(cp, cr);
}

bool Controller::CalculateDeposit(const Protocol::DepositParameters &dp, Protocol::DepositResult &dr) {
  return model_->CalculateDeposit(dp, dr);
}

}  // namespace s21