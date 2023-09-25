#include <cmath>
#include <array>
#include "model.h"
#include "../controller/controller.h"

int Model::credit_calc_fn(double credit_sum, int credit_term, float credit_percent,
                   int type, double *monthlty_payment, double *overpayment,
                   double *total_sum) {
  int ex_code = 0;
  if (type == 1) {
    credit_percent = credit_percent / 100 / 12;
    *monthlty_payment = credit_sum * credit_percent *
                        std::pow(1. + credit_percent, credit_term) /
                        (std::pow(1. + credit_percent, credit_term) - 1.);
    *total_sum = *monthlty_payment * credit_term;
    *overpayment = *total_sum - credit_sum;
  } else if (type == 2) {
    double mon_loan = credit_sum / credit_term;
    *total_sum = 0;
    for (int i = 0; i < credit_term; i++) {
      *total_sum +=
          mon_loan + (credit_sum - mon_loan * i) * credit_percent / 1200;
    }
    *overpayment = *total_sum - credit_sum;
    *monthlty_payment = mon_loan + credit_sum * credit_percent / 1200;
  }
  return ex_code;
}

// int Model::deposit_calc_fn(double deposit_sum, int deposit_term, float deposit_percent,
//                     float tax_percent, int type_cap, int type_pay,
//                     const double *add_sum, double *interest_income,
//                     double *total_deposit_sum, double *tax_sum) {
//   int ex_code = 0;
//   if (type_cap == 2) {
//     *interest_income = 0;
//     for (int i = 0; i < deposit_term && ex_code == 0; i++) {
//       deposit_sum = deposit_sum + add_sum[i];
//       if (deposit_sum < 0) ex_code = 1;
//       double monthly_percent = deposit_sum * deposit_percent / 1200;
//       *interest_income = *interest_income + monthly_percent;
//     }
//     *total_deposit_sum = deposit_sum + *interest_income;
//     *tax_sum = *interest_income * tax_percent / 100;

//   } else if (type_cap == 1 && type_pay == 2) {
//     *interest_income = 0;
//     double monthly_percent = 0;
//     for (int i = 0; i < deposit_term && ex_code == 0; i++) {
//       deposit_sum = deposit_sum + add_sum[i] + monthly_percent;
//       if (deposit_sum < 0) ex_code = 1;
//       monthly_percent = deposit_sum * deposit_percent / 1200;
//       *interest_income = *interest_income + monthly_percent;
//     }
//     *total_deposit_sum = deposit_sum + monthly_percent;
//     *tax_sum = *interest_income * tax_percent / 100;

//   } else if (type_cap == 1 && type_pay == 1) {
//     *interest_income = 0;
//     for (int i = 0; i < deposit_term && ex_code == 0; i++) {
//       deposit_sum = deposit_sum + add_sum[i];
//       if (deposit_sum < 0) ex_code = 1;
//       double monthly_percent = deposit_sum * deposit_percent / 1200;
//       *interest_income = *interest_income + monthly_percent;
//     }
//     *total_deposit_sum = deposit_sum + *interest_income;
//     *tax_sum = *interest_income * tax_percent / 100;
//   }
//   return ex_code;
// }





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