#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

class Controller 
{
    public:
        Controller();
        static int main_for_calc(const char *input_str, double *result, double x_value);
        static int credit_calc_fn(double credit_sum, int credit_term, float credit_percent,
                    int type, double *monthlty_payment, double *overpayment,
                    double *total_sum);
        static int deposit_calc_fn(double deposit_sum, int deposit_term, float deposit_percent,
                      float tax_percent, int type_cap, int type_pay,
                      const double *add_sum, double *interest_income,
                      double *total_deposit_sum, double *tax_sum);
};

#endif  // SRC_CONTROLLER_CONTROLLER_H