#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include <string>
#include <vector>

class Controller 
{
public:
    struct CreditParameters {
        double creditSum_ = 0.0;
        int creditTerm_ = 0;
        float creditPercent_ = 0.0f;
        
        enum class RepainmentOrder {
            Undefined,
            Annuity,
            Differentiated
        };

        RepainmentOrder order_ = RepainmentOrder::Undefined;
    };

    struct CreditResult {
        double monthltyPayment_ = 0.0;
        double overpayment_ = 0.0;
        double totalSum_ = 0.0;

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
        Controller(class Model* model);

        int Calculate(const std::string& input_str, double *result, double x_value);
        bool CalculateDeposit(const DepositParameters& dp, DepositResult& dr);
        int CalculateGraph(const GraphParameters& gp, GraphResult& gr);
        bool CalculateCredit(const CreditParameters& cp, CreditResult& cr);


    private:
        Model* model_;
};

#endif  // SRC_CONTROLLER_CONTROLLER_H