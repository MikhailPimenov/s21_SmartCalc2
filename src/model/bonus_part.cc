#include <cmath>
#include <array>
#include "model.h"
#include "../controller/controller.h"

// int Model::credit_calc_fn(double credit_sum, int credit_term, float credit_percent,
//                    int type, double *monthlty_payment, double *overpayment,
//                    double *total_sum) {
//   int ex_code = 0;
//   if (type == 1) {
//     credit_percent = credit_percent / 100 / 12;
//     *monthlty_payment = credit_sum * credit_percent *
//                         std::pow(1. + credit_percent, credit_term) /
//                         (std::pow(1. + credit_percent, credit_term) - 1.);
//     *total_sum = *monthlty_payment * credit_term;
//     *overpayment = *total_sum - credit_sum;
//   } else if (type == 2) {
//     double mon_loan = credit_sum / credit_term;
//     *total_sum = 0;
//     for (int i = 0; i < credit_term; i++) {
//       *total_sum +=
//           mon_loan + (credit_sum - mon_loan * i) * credit_percent / 1200;
//     }
//     *overpayment = *total_sum - credit_sum;
//     *monthlty_payment = mon_loan + credit_sum * credit_percent / 1200;
//   }
//   return ex_code;
// }

bool Model::CalculateCredit(const CreditParameters& cp, CreditResult& cr) {
  if (cp.order_ == CreditParameters::RepainmentOrder::Undefined)
    return false;
  if (cp.credit_sum_ < 0.0)
    return false;
  if (cp.credit_term_ < 1)
    return false;
  if (cp.credit_percent_ < 0.0)
    return false;
  if (cp.order_ == CreditParameters::RepainmentOrder::Annuity) {
    const double credit_percent = cp.credit_percent_ / 100 / 12;
    cr.monthlty_payment_ = cp.credit_sum_ * credit_percent *
                        std::pow(1. + credit_percent, cp.credit_term_) /
                        (std::pow(1. + credit_percent, cp.credit_term_) - 1.);
    for(int i = 0; i < cp.credit_term_; i++)
      cr.list_.push_back(cr.monthlty_payment_);
    cr.total_sum_ = cr.monthlty_payment_ * cp.credit_term_;
    cr.overpayment_ = cr.total_sum_ - cp.credit_sum_;
  } else if (cp.order_ == CreditParameters::RepainmentOrder::Differentiated) {
    double mon_loan = cp.credit_sum_ / cp.credit_term_;
    cr.total_sum_ = 0;
    for (int i = 0; i < cp.credit_term_; i++) {
      const double delta = mon_loan + (cp.credit_sum_ - mon_loan * i) * cp.credit_percent_ / 1200;
      cr.total_sum_ += delta;
      cr.list_.push_back(delta);
    }
    cr.overpayment_ = cr.total_sum_ - cp.credit_sum_;
    cr.monthlty_payment_= mon_loan + cp.credit_sum_ * cp.credit_percent_ / 1200;
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