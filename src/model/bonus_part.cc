#include <cmath>
#include <array>
#include "model.h"
#include "../controller/controller.h"

bool Model::CalculateCredit(const CreditParameters& cp, CreditResult& cr) {
  if (cp.order_ == CreditParameters::RepainmentOrder::Undefined)
    return false;
  if (cp.creditSum_ < 0.0)
    return false;
  if (cp.creditTerm_ < 1)
    return false;
  if (cp.creditPercent_ < 0.0)
    return false;
  
  static constexpr int months = 12;
  if (cp.order_ == CreditParameters::RepainmentOrder::Annuity) {
    const double credit_percent = cp.creditPercent_ / 100.0 / months;
    cr.monthlty_payment_ = cp.creditSum_ * credit_percent *
                        std::pow(1. + credit_percent, cp.creditTerm_) /
                        (std::pow(1. + credit_percent, cp.creditTerm_) - 1.);
    for(int i = 0; i < cp.creditTerm_; i++)
      cr.list_.push_back(cr.monthlty_payment_);
    cr.total_sum_ = cr.monthlty_payment_ * cp.creditTerm_;
    cr.overpayment_ = cr.total_sum_ - cp.creditSum_;
  } else if (cp.order_ == CreditParameters::RepainmentOrder::Differentiated) {
    double mon_loan = cp.creditSum_ / cp.creditTerm_;
    cr.total_sum_ = 0;
    for (int i = 0; i < cp.creditTerm_; i++) {
      const double delta = mon_loan + (cp.creditSum_ - mon_loan * i) * cp.creditPercent_ / 100.0 / months;
      cr.total_sum_ += delta;
      cr.list_.push_back(delta);
    }
    cr.overpayment_ = cr.total_sum_ - cp.creditSum_;
    cr.monthlty_payment_= mon_loan + cp.creditSum_ * cp.creditPercent_ / 100.0 / months;
  }
  return true;
}

bool Model::CalculateDeposit(const DepositParameters& parameters, DepositResult& result) {
  static constexpr std::array<int, 12> daysPerMonth { 
    31, // jan 
    28, // feb
    31, // mar
    30, // apr
    31, // may
    30, // jun 
    31, // jul
    31, // aug
    30, // sep
    31, // oct
    30, // nov
    31, // dec
  };
  static constexpr int months = 12;
  static constexpr int days = 365;

  if (parameters.capitalization_ == DepositParameters::Capitalization::Undefined)
    return false;
  if (parameters.frequency_ == DepositParameters::PaymentFrequency::Undefined)
    return false;
  if (parameters.amount_ < 0.01)
    return false;
  if (parameters.interest_ < 0.0)
    return false;
  if (parameters.interest_ > 100.0)
    return false;
  if (parameters.tax_ < 0.0)
    return false;
  if (parameters.tax_ > 100.0)
    return false;
  if (parameters.period_ < 1)
    return false;
  if (parameters.period_ > 600)
    return false;
  
  double sum = parameters.amount_;
  result.amountTotal_ = parameters.amount_;
  result.taxTotal_ = 0.0;
  result.accruedTotal_ = 0.0;

  if (parameters.frequency_ == DepositParameters::PaymentFrequency::Monthly)
    result.list_.reserve(parameters.period_);
  
  for (int i = 0; i < parameters.period_; ++i) {
    const int daysDelta = daysPerMonth[i % months];
    const double deltaInterest = sum / 100.0 * parameters.interest_ / days * daysDelta;
    const double deltaTax = deltaInterest / 100.0 * parameters.tax_;
    const double deltaSum = deltaInterest - deltaTax;

    if (parameters.capitalization_ == DepositParameters::Capitalization::Monthly)
      sum += deltaSum;

    result.amountTotal_ += deltaSum;
    result.taxTotal_ += deltaTax;
    result.accruedTotal_ += deltaInterest;

    if (parameters.frequency_ == DepositParameters::PaymentFrequency::Monthly)
      result.list_.push_back(deltaSum);
  }

  if (parameters.frequency_ == DepositParameters::PaymentFrequency::Total)
    result.list_.push_back(result.amountTotal_ - parameters.amount_);

  return true;
}