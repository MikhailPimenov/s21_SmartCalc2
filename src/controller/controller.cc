#include "controller.h"
#include "../model/model.h"

Controller::Controller() {}

int Controller::main_for_calc(const char *input_str, double *result, double x_value) {
    return Model::main_for_calc(input_str, result, x_value);
}

bool Controller::CalculateCredit(const CreditParameters& cp, CreditResult& cr) {
    Model::CreditParameters mcp;
    mcp.credit_sum_ = cp.credit_sum_;
    mcp.credit_term_ = cp.credit_term_;
    mcp.credit_percent_= cp.credit_percent_;
    mcp.order_ = static_cast<Model::CreditParameters::RepainmentOrder>(cp.order_);

    Model::CreditResult mcr;
    const bool result = Model::CalculateCredit(mcp, mcr);

    cr.monthlty_payment_  = mcr.monthlty_payment_ ;
    cr.overpayment_ = mcr.overpayment_;
    cr.list_ = std::move(mcr.list_);
    cr.total_sum_ = mcr.total_sum_;

    return result;
}
    

// int Controller::credit_calc_fn(double credit_sum, int credit_term, float credit_percent,
//                     int type, double *monthlty_payment, double *overpayment,
//                     double *total_sum) {
//     return Model::credit_calc_fn(credit_sum, credit_term, credit_percent,
//                     type, monthlty_payment, overpayment, total_sum);
// }
// int Controller::deposit_calc_fn(double deposit_sum, int deposit_term, float deposit_percent,
//                       float tax_percent, int type_cap, int type_pay,
//                       const double *add_sum, double *interest_income,
//                       double *total_deposit_sum, double *tax_sum) {
//     return Model::deposit_calc_fn(deposit_sum, deposit_term, deposit_percent,
//                       tax_percent, type_cap, type_pay, add_sum, interest_income, total_deposit_sum, tax_sum);
// }


bool Controller::CalculateDeposit(const DepositParameters& dp, DepositResult& dr) {
    Model::DepositParameters mdp;
    mdp.amount_ = dp.amount_;
    mdp.interest_ = dp.interest_;
    mdp.tax_ = dp.tax_;
    mdp.period_ = dp.period_;
    mdp.capitalization_ = static_cast<Model::DepositParameters::Capitalization>(dp.capitalization_);
    mdp.frequency_ = static_cast<Model::DepositParameters::PaymentFrequency>(dp.frequency_);

    Model::DepositResult mdr;
    const bool result = Model::CalculateDeposit(mdp, mdr);

    dr.accruedTotal_ = mdr.accruedTotal_;
    dr.amountTotal_ = mdr.amountTotal_;
    dr.list_ = std::move(mdr.list_);
    dr.taxTotal_ = mdr.taxTotal_;

    return result;
}

