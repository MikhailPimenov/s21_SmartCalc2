#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H

#include <string>

#include <stack>
#include <vector>

namespace s21 {

class Model {
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
    double accruedTotal_;
    double taxTotal_;
    double amountTotal_;

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
          Monthly,
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

private:

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

  static void flipStack(std::stack<Token>& input, std::stack<Token>& output);
};

} //  namespace s21

#endif  //  SRC_MODEL_MODEL_H