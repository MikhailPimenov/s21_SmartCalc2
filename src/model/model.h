#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H

#include <string>

#include <stack>
#include <vector>

namespace s21 {


/**
 * @brief Business logic. All computations are here
 * Calculates expression using reversed polish notation
 * Plots graphs
 * Calculates credit
 * Calculates deposit
 */
class Model {
public:
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
        enum class RepainmentOrder {
            Undefined,
            Annuity,
            Differentiated
        };

        RepainmentOrder order_ = RepainmentOrder::Undefined;
    };

    /**
     * @brief Result of calculated credit
     * 
     */
    struct CreditResult {
        /**
         * @brief How much to pay every month, or the last sum in case of differentiated credit
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

private:

  /**
   * @brief Token type. Either number, or function, or bracket, or placeholder X
   * 
   */
  enum class Type : int {
    Number        = 0,
    OpenBracket   = 1,
    CloseBracket  = 2,
    Sum = 3,
    Minus = 4,
    Mult = 5 ,
    Div =6,
    Power=7,
    Mod=8,
    Cos=11,
    Sin=12,
    Tan=13,
    Acos=14,
    Asin=15,
    Atan=16,
    Sqrt=17,
    Ln=18,
    Log=19,
    X=20,
  };

  /**
   * @brief Type of element the input string consists of
   * Has value, type of value and precedence.
   * Precedence defines the order of calculations
   */
  struct Token {
    double value;
    Type type;
    int precedence;

  public:
    Token(double v, Type t, int p) : value(v), type(t), precedence(p) {}
  };

public:
  static int Calculate(const std::string& input_str, double *result, double x_value);
  static bool CalculateDeposit(const DepositParameters& parameters, DepositResult& result);
  static bool CalculateCredit(const CreditParameters& cp, CreditResult& cr);
  static int CalculateGraph(const GraphParameters& gp, GraphResult& gr);

private:
  static int parcer(const std::string& input_str, std::stack<Token>& head);
  static void shuntingYard(std::stack<Token>& head, std::stack<Token>& output);
  static double calcRpn(std::stack<Token>& output, double x_value);
  static double unaryFnCalc(double number1, Type type);
  static double binaryFnCalc(double number1, double number2, Type type);  
  static void flipStack(std::stack<Token> input, std::stack<Token>& output);
};

} //  namespace s21

#endif  //  SRC_MODEL_MODEL_H