#ifndef SRC_PROTOCOL_PROTOCOL_H
#define SRC_PROTOCOL_PROTOCOL_H

namespace s21 {

/**
 * @brief Business logic. All computations are here
 * Calculates expression using reversed polish notation
 * Plots graphs
 * Calculates credit
 * Calculates deposit
 */
namespace Protocol {
 

  /**
   * @brief Parameters to be passed to model to start credit calculation
   *
   */
  struct CreditParameters {
    /**
     * @brief How much money was given
     *
     */
    double creditSum_ = 0.0;

    /**
     * @brief Period, months
     *
     */
    int creditTerm_ = 0;

    /**
     * @brief Percent
     *
     */
    float creditPercent_ = 0.0f;

    /**
     * @brief Credit type
     * Annuity - constant sum to pay every month
     * Differentiated - sum to pay is decreasing every month
     * Undefined - not selected. Incorrect input
     */
    enum class RepainmentOrder { Undefined, Annuity, Differentiated };

    RepainmentOrder order_ = RepainmentOrder::Undefined;
  };

  /**
   * @brief Result of calculated credit
   *
   */
  struct CreditResult {
    /**
     * @brief How much to pay every month, or the last sum in case of
     * differentiated credit
     *
     */
    double monthlyPayment_ = 0.0;
    /**
     * @brief How much the entire sum to pay exceeds initial credit sum
     *
     */
    double overpayment_ = 0.0;
    /**
     * @brief The entire sum to pay
     *
     */
    double totalSum_ = 0.0;

    /**
     * @brief All sums to pay every month
     *
     */
    std::vector<double> monthlyPaymentList_;
  };

  /**
   * @brief Parameters to be passed to model to start deposit calculation
   *
   */
  struct DepositResult {
    /**
     * @brief Total amount increased because of percent
     *
     */
    double accruedTotal_;
    /**
     * @brief Total amount payed because of taxes
     *
     */
    double taxTotal_;

    /**
     * @brief Sum at the end of the period
     *
     */
    double amountTotal_;

    /**
     * @brief Sum at every month
     *
     */
    std::vector<double> accruedMonthly_;
    /**
     * @brief Monthly addition because of percent
     *
     */
    std::vector<double> percentMonthly_;
  };
  /**
   * @brief Parameters to be passed to model to perform deposit calculation
   *
   */
  struct DepositParameters {
    /**
     * @brief Initial sum
     *
     */
    double amount_ = 0.0;
    /**
     * @brief Period, months
     *
     */
    int period_ = 0;
    /**
     * @brief Percent by which initial sum increases in one year
     *
     */
    double interest_ = 0.0;
    /**
     * @brief Percent of delta which is payed as tax
     *
     */
    double tax_ = 0.0;

    /**
     * @brief Type of capitalization.
     * Monthly - every month additional sum is added to sum
     * Total - additional sum is not added to sum every month
     * Undefined - not selected. Incorrect input
     */
    enum class Capitalization {
      Undefined,
      Total,
      Monthly,
    };
    /**
     * @brief Payment frequency type
     * Monthly - every month additional sum is taken from sum
     * Total - all sum is taken at the end
     * Undefined - not selected. Incorrect input
     */
    enum class PaymentFrequency {
      Undefined,
      Total,
      Monthly,
    };

    Capitalization capitalization_ = Capitalization::Undefined;
    PaymentFrequency frequency_ = PaymentFrequency::Undefined;

    /**
     * @brief Addition or amount of money taken from deposit by the client
     *
     */
    std::vector<double> depositOrWithdrawal_;
  };

  /**
   * @brief Parameters to be passed to model to calculate graph
   *
   */
  struct GraphParameters {
    double x_max = 30.0;
    double x_min = -30.0;
    std::string input_string;
  };
  /**
   * @brief Parameters of calculated graph from model
   *
   */
  struct GraphResult {
    std::vector<double> x;
    std::vector<double> y;
  };

}   // namespace Protocol

}   // namespace s21

#endif  //  SRC_PROTOCOL_PROTOCOL_H