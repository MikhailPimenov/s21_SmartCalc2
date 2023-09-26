#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include <vector>

class Controller 
{
public:
    struct CreditParameters {
        double credit_sum_ = 0.0;
        int credit_term_ = 0;
        float credit_percent_ = 0.0f;
        
        enum class RepainmentOrder {
            Undefined,
            Annuity,
            Differentiated
        };

        RepainmentOrder order_ = RepainmentOrder::Undefined;
    };

    struct CreditResult {
        double monthlty_payment_ = 0.0;
        double overpayment_ = 0.0;
        double total_sum_ = 0.0;

        std::vector<double> list_;
    };

    struct DepositResult {
        double accruedTotal_ = 0.0;
        double taxTotal_ = 0.0;
        double amountTotal_ = 0.0;

        std::vector<double> list_;
    };

    struct DepositParameters {
        double amount_ = 0.0;
        int period_ = 0;
        double interest_ = 0.0;
        double tax_ = 0.0;

        enum class Capitalization {
            Undefined,
            Total,
            Monthly,
        };
        enum class PaymentFrequency {
            Undefined,
            Total,
            Monthly
        };

        Capitalization capitalization_ = Capitalization::Undefined;
        PaymentFrequency frequency_ = PaymentFrequency::Undefined;
        
    };


    public:
        Controller();
        static int main_for_calc(const char *input_str, double *result, double x_value);
        static int credit_calc_fn(double credit_sum, int credit_term, float credit_percent,
                    int type, double *monthlty_payment, double *overpayment,
                    double *total_sum);
        // static int deposit_calc_fn(double deposit_sum, int deposit_term, float deposit_percent,
        //               float tax_percent, int type_cap, int type_pay,
        //               const double *add_sum, double *interest_income,
        //               double *total_deposit_sum, double *tax_sum);

        static bool CalculateDeposit(const DepositParameters& dp, DepositResult& dr);
        static bool CalculateCredit(const CreditParameters& cp, CreditResult& cr);

};

#endif  // SRC_CONTROLLER_CONTROLLER_H