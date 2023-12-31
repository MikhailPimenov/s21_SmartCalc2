#include "creditCalculator.h"

#include <cmath>

namespace s21 {

namespace Model {

CreditCalculator::InputChecker::InputChecker(CreditCalculator& owner)
    : owner_{owner} {}

bool CreditCalculator::InputChecker::Run() const {
  if (owner_.cp_.order_ ==
      Protocol::CreditParameters::RepainmentOrder::Undefined)
    return false;
  if (owner_.cp_.creditSum_ < 10000.0) return false;
  if (owner_.cp_.creditSum_ > 100000000.0) return false;
  if (owner_.cp_.creditTerm_ < 1) return false;
  if (owner_.cp_.creditTerm_ > 600) return false;
  if (owner_.cp_.creditPercent_ < 0.01) return false;
  if (owner_.cp_.creditPercent_ > 99.999999) return false;

  return true;
}

CreditCalculator::CreditCalculator(const Protocol::CreditParameters& cp)
    : cp_{cp} {}

bool CreditCalculator::Run() {
  InputChecker inputChecker(*this);
  if (!inputChecker.Run()) {
    success_ = false;
    return success_;
  }

  static constexpr int months = 12;

  if (cp_.order_ == Protocol::CreditParameters::RepainmentOrder::Annuity) {
    const double creditPercent = cp_.creditPercent_ / 100.0 / months;
    cr_.monthlyPayment_ = cp_.creditSum_ * creditPercent *
                          std::pow(1. + creditPercent, cp_.creditTerm_) /
                          (std::pow(1. + creditPercent, cp_.creditTerm_) - 1.);
    for (int i = 0; i < cp_.creditTerm_; i++)
      cr_.monthlyPaymentList_.push_back(cr_.monthlyPayment_);
    cr_.totalSum_ = cr_.monthlyPayment_ * cp_.creditTerm_;
    cr_.overpayment_ = cr_.totalSum_ - cp_.creditSum_;
  } else /* if (cp.order_ == CreditParameters::RepainmentOrder::Differentiated)
          */
  {
    double monthlyLoan = cp_.creditSum_ / cp_.creditTerm_;
    cr_.totalSum_ = 0.0;
    for (int i = 0; i < cp_.creditTerm_; i++) {
      const double delta = monthlyLoan + (cp_.creditSum_ - monthlyLoan * i) *
                                             cp_.creditPercent_ / 100.0 /
                                             months;
      cr_.totalSum_ += delta;
      cr_.monthlyPaymentList_.push_back(delta);
    }
    cr_.overpayment_ = cr_.totalSum_ - cp_.creditSum_;
    cr_.monthlyPayment_ =
        monthlyLoan + cp_.creditSum_ * cp_.creditPercent_ / 100.0 / months;
  }

  success_ = true;
  return success_;
}

std::optional<Protocol::CreditResult> CreditCalculator::Get() const {
  if (!success_) return std::nullopt;
  return cr_;
}

}  // namespace Model

}  // namespace s21