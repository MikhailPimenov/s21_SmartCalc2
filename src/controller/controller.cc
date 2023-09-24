#include "controller.h"
#include "../model/model.h"

Controller::Controller() {}

int Controller::main_for_calc(const char *input_str, double *result, double x_value) {
    return Model::main_for_calc(input_str, result, x_value);
}

int Controller::credit_calc_fn(double credit_sum, int credit_term, float credit_percent,
                    int type, double *monthlty_payment, double *overpayment,
                    double *total_sum) {
    return Model::credit_calc_fn(credit_sum, credit_term, credit_percent,
                    type, monthlty_payment, overpayment, total_sum);
}
int Controller::deposit_calc_fn(double deposit_sum, int deposit_term, float deposit_percent,
                      float tax_percent, int type_cap, int type_pay,
                      const double *add_sum, double *interest_income,
                      double *total_deposit_sum, double *tax_sum) {
    return Model::deposit_calc_fn(deposit_sum, deposit_term, deposit_percent,
                      tax_percent, type_cap, type_pay, add_sum, interest_income, total_deposit_sum, tax_sum);
}
