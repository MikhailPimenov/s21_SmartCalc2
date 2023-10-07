#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H

#include <stack>
#include <string>
#include <optional>
#include <vector>

namespace s21 {

namespace Protocol {

struct DepositParameters;
struct DepositResult;
struct GraphParameters;
struct GraphResult;
struct CreditParameters;
struct CreditResult;

}  // namespace Protocol

/**
 * @brief Business logic. All computations are here
 * Calculates expression using reversed polish notation
 * Plots graphs
 * Calculates credit
 * Calculates deposit
 */
class Model {
 private:
  /**
   * @brief Token type. Either number, or function, or bracket, or placeholder X
   *
   */
  enum class Type : int {
    Number = 0,
    OpenBracket = 1,
    CloseBracket = 2,
    Sum = 3,
    Minus = 4,
    Mult = 5,
    Div = 6,
    Power = 7,
    Mod = 8,
    Cos = 11,
    Sin = 12,
    Tan = 13,
    Acos = 14,
    Asin = 15,
    Atan = 16,
    Sqrt = 17,
    Ln = 18,
    Log = 19,
    X = 20,
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
  static int Calculate(const std::string &input_str, double *result,
                       double x_value);
  static bool CalculateDeposit(const Protocol::DepositParameters &parameters,
                               Protocol::DepositResult &result);
  static bool CalculateCredit(const Protocol::CreditParameters &cp,
                              Protocol::CreditResult &cr);
  static int CalculateGraph(const Protocol::GraphParameters &gp,
                            Protocol::GraphResult &gr);

 private:
  // static std::optional<std::stack<Token>> parcer(const std::string& input);
  static int parcer(const std::string &input_str, std::stack<Token> &head);
  static void shuntingYard(std::stack<Token> &head, std::stack<Token> &output);
  static std::optional<double> calcRpn(std::stack<Token> &output, double x_value);
  static double unaryFnCalc(double number1, Type type);
  static double binaryFnCalc(double number1, double number2, Type type);
  static void flipStack(std::stack<Token> input, std::stack<Token> &output);
};

}  //  namespace s21

#endif  //  SRC_MODEL_MODEL_H