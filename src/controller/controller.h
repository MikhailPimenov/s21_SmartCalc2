#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include <string>
#include <vector>


/*!
\file
\brief Controller. Mediator between view (interface) and model (calculator)

*/

namespace s21 {

class Controller 
{
public:

    /**
     * @brief Parameters passed from view to controller to calculate credit
     * Same as parameters to be passed to model.
     * Different structures are used to underline independence.
     * Model must not be dependened on data structures, so it uses its own ones.
     * View must not be dependened on data structures of model, so controller provides its own ones. 
     * 
     */
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

    /**
     * @brief Parameters passed from controller to view with calculated credit
     * Same as parameters to be passed from model.
     * Different structures are used to underline independence.
     * Model must not be dependened on data structures, so it uses its own ones.
     * View must not be dependened on data structures of model, so controller provides its own ones. 
     * 
     */
    struct CreditResult {
        double monthlyPayment_ = 0.0;
        double overpayment_ = 0.0;
        double totalSum_ = 0.0;

        std::vector<double> list_;
    };

    /**
     * @brief Parameters passed from controller to view with calculated deposit
     * Same as parameters to be passed from model.
     * Different structures are used to underline independence.
     * Model must not be dependened on data structures, so it uses its own ones.
     * View must not be dependened on data structures of model, so controller provides its own ones. 
     * 
     */
    struct DepositResult {
        double accruedTotal_ = 0.0;
        double taxTotal_ = 0.0;
        double amountTotal_ = 0.0;

        std::vector<double> accruedMonthly_;
        std::vector<double> percentMonthly_;
    };


    /**
     * @brief Parameters passed from view to controller to calculate deposit
     * Same as parameters to be passed to model.
     * Different structures are used to underline independence.
     * Model must not be dependened on data structures, so it uses its own ones.
     * View must not be dependened on data structures of model, so controller provides its own ones. 
     * 
     */
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
        
        mutable std::vector<double> depositOrWithdrawal_;
    };

    /**
     * @brief Parameters passed from view to controller to calculate graph
     * Same as parameters to be passed to model.
     * Different structures are used to underline independence.
     * Model must not be dependened on data structures, so it uses its own ones.
     * View must not be dependened on data structures of model, so controller provides its own ones. 
     * 
     */
    struct GraphParameters {
        double x_max = 30.0;
        double x_min = -30.0;
        std::string input_string;
    };

    /**
     * @brief Parameters passed from controller to view with calculated deposit
     * Same as parameters to be passed from model.
     * Different structures are used to underline independence.
     * Model must not be dependened on data structures, so it uses its own ones.
     * View must not be dependened on data structures of model, so controller provides its own ones. 
     * 
     */
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

}   //  namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H