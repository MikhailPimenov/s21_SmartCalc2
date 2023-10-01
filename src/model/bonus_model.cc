#include <cmath>
#include <array>
#include "model.h"
#include "../controller/controller.h"

namespace s21 {


/**
 * @brief Calculates credit
 * 
 * @param cp Input parameters
 * @param cr Calculated result
 * @return true if success
 * @return false if failed (incorrect input)
 */
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
    const double creditPercent = cp.creditPercent_ / 100.0 / months;
    cr.monthltyPayment_ = cp.creditSum_ * creditPercent *
                        std::pow(1. + creditPercent, cp.creditTerm_) /
                        (std::pow(1. + creditPercent, cp.creditTerm_) - 1.);
    for(int i = 0; i < cp.creditTerm_; i++)
      cr.list_.push_back(cr.monthltyPayment_);
    cr.totalSum_ = cr.monthltyPayment_ * cp.creditTerm_;
    cr.overpayment_ = cr.totalSum_ - cp.creditSum_;
  } else if (cp.order_ == CreditParameters::RepainmentOrder::Differentiated) {
    double monthlyLoan = cp.creditSum_ / cp.creditTerm_;
    cr.totalSum_ = 0;
    for (int i = 0; i < cp.creditTerm_; i++) {
      const double delta = monthlyLoan + (cp.creditSum_ - monthlyLoan * i) * cp.creditPercent_ / 100.0 / months;
      cr.totalSum_ += delta;
      cr.list_.push_back(delta);
    }
    cr.overpayment_ = cr.totalSum_ - cp.creditSum_;
    cr.monthltyPayment_= monthlyLoan + cp.creditSum_ * cp.creditPercent_ / 100.0 / months;
  }
  return true;
}


/**
 * @brief Calculates deposit
 * 
 * @param parameters Input parameters
 * @param result Calculated result
 * @return true if success
 * @return false if failed (incorrect input)
 */
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

  if (parameters.frequency_ == DepositParameters::PaymentFrequency::Monthly) {
    result.accruedMonthly_.reserve(parameters.period_);
    result.percentMonthly_.reserve(parameters.period_);
  }
  
  const bool monthlyChanges = static_cast<int>(parameters.depositOrWithdrawal_.size()) == parameters.period_;

  for (int i = 0; i < parameters.period_; ++i) {
    if (monthlyChanges)
      sum += parameters.depositOrWithdrawal_[i];

    const int daysDelta = daysPerMonth[i % months];
    const double deltaInterest = sum / 100.0 * parameters.interest_ / days * daysDelta;
    const double deltaTax = deltaInterest / 100.0 * parameters.tax_;
    const double deltaSum = deltaInterest - deltaTax;

    if (parameters.capitalization_ == DepositParameters::Capitalization::Monthly && parameters.frequency_ == DepositParameters::PaymentFrequency::Total)
      sum += deltaSum;
    
    if (monthlyChanges)
      result.amountTotal_ += parameters.depositOrWithdrawal_[i];
  
    result.amountTotal_ += deltaSum;
    
    if (monthlyChanges)
      result.accruedMonthly_.push_back(result.amountTotal_);

    result.taxTotal_ += deltaTax;
    result.accruedTotal_ += deltaInterest;

    result.percentMonthly_.push_back(deltaSum);
  }

  if (parameters.frequency_ == DepositParameters::PaymentFrequency::Total)
    result.percentMonthly_.push_back(result.amountTotal_ - parameters.amount_);

  return true;
}

}   // namespace s21