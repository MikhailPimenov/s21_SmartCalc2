#include "depositCalculator.h"
#include <array>

namespace s21 {

namespace Model {

DepositCalculator::InputChecker::InputChecker(DepositCalculator& owner) : owner_{owner} {

}

bool DepositCalculator::InputChecker::Run() const {
  if (owner_.dp_.capitalization_ ==
      Protocol::DepositParameters::Capitalization::Undefined)
    return false;
  if (owner_.dp_.frequency_ ==
      Protocol::DepositParameters::PaymentFrequency::Undefined)
    return false;
  if (owner_.dp_.amount_ < 0.01) return false;
  if (owner_.dp_.interest_ < 0.0) return false;
  if (owner_.dp_.interest_ > 99.9999999) return false;
  if (owner_.dp_.tax_ < 0.0) return false;
  if (owner_.dp_.tax_ > 99.9999999) return false;
  if (owner_.dp_.period_ < 1) return false;
  if (owner_.dp_.period_ > 600) return false;

  return true;
}


DepositCalculator::DepositCalculator(const Protocol::DepositParameters &dp) : dp_{dp} {

}

bool DepositCalculator::Run() {
    InputChecker inputChecker(*this);
    if (!inputChecker.Run()) {
        success_ = false;
        return success_;
    }

    static constexpr std::array<int, 12> daysPerMonth{
      31,  // jan
      28,  // feb
      31,  // mar
      30,  // apr
      31,  // may
      30,  // jun
      31,  // jul
      31,  // aug
      30,  // sep
      31,  // oct
      30,  // nov
      31,  // dec
  };
  static constexpr int months = 12;
  static constexpr int days = 365;


  double sum = dp_.amount_;
  dr_.amountTotal_ = dp_.amount_;
  dr_.taxTotal_ = 0.0;
  dr_.accruedTotal_ = 0.0;

  if (dp_.frequency_ ==
      Protocol::DepositParameters::PaymentFrequency::Monthly) {
    dr_.accruedMonthly_.reserve(dp_.period_);
    dr_.percentMonthly_.reserve(dp_.period_);
  }

  const bool monthlyChanges =
      static_cast<int>(dp_.depositOrWithdrawal_.size()) ==
      dp_.period_;

  for (int i = 0; i < dp_.period_; ++i) {
    const int daysDelta = daysPerMonth[i % months];
    const double deltaInterest =
        sum / 100.0 * dp_.interest_ / days * daysDelta;
    const double deltaTax = deltaInterest / 100.0 * dp_.tax_;
    const double deltaSum = deltaInterest - deltaTax;

    if (monthlyChanges) sum += dp_.depositOrWithdrawal_[i];

    if (dp_.capitalization_ ==
            Protocol::DepositParameters::Capitalization::Monthly &&
        dp_.frequency_ ==
            Protocol::DepositParameters::PaymentFrequency::Total)
      sum += deltaSum;

    if (monthlyChanges)
      dr_.amountTotal_ += dp_.depositOrWithdrawal_[i];

    if (dr_.amountTotal_ < 0.0) {
        success_ = false;
        return success_;
    } 

    dr_.amountTotal_ += deltaSum;

    dr_.accruedMonthly_.push_back(sum);

    dr_.taxTotal_ += deltaTax;
    dr_.accruedTotal_ += deltaInterest;

    dr_.percentMonthly_.push_back(deltaSum);
  }

  success_ = true;
  return success_;
}

std::optional<Protocol::DepositResult> DepositCalculator::Get() const {
    if (!success_)
        return std::nullopt;
    return dr_;
}

}   // namespace Model

}   // namespace s21