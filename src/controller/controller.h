#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include <string>
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

    struct GraphParameters {
  double x_max = 30.0;
  double x_min = -30.0;
  std::string input_string;
  };
struct GraphResult {
  std::vector<double> x;
  std::vector<double> y;
};


    public:
        Controller();

        static int Calculate(const std::string& input_str, double *result, double x_value);
        static bool CalculateDeposit(const DepositParameters& dp, DepositResult& dr);
        static bool CalculateCredit(const CreditParameters& cp, CreditResult& cr);

        static int CalculateGraph(const GraphParameters& gp, GraphResult& gr);

};

#endif  // SRC_CONTROLLER_CONTROLLER_H