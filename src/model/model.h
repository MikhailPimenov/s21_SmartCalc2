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
//  private:
 public:
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
    double value_;     // TODO: rename value -> value_
    Type type_;
    int precedence_;

   public:
    Token(double v, Type t, int p) : value_(v), type_(t), precedence_(p) {}


    bool isUnaryLeftFunction() const;
    bool isOpeningBrace() const;
    bool isBinaryFunction() const;
    bool isUnaryRightFunction() const;
    bool isOperand() const;
    bool isClosingBrace() const;
  };

 public:
  // static int Calculate(const std::string &input_str, double *result,
  //                      double x_value);
  // std::optional<double> Calculate(const std::string &input_str, double x_value);
                       
  bool CalculateDeposit(const Protocol::DepositParameters &parameters,
                               Protocol::DepositResult &result);
  bool CalculateCredit(const Protocol::CreditParameters &cp,
                              Protocol::CreditResult &cr);
  int CalculateGraph(const Protocol::GraphParameters &gp,
                            Protocol::GraphResult &gr);

//  private:
public:
  // static std::optional<std::vector<Token>> parcer(const std::string& input);
  // static bool validate(const std::vector<Token>& tokens);

  // static int parcer2(const std::string &input_str, std::stack<Token> &head);
  // // static void shuntingYard(std::stack<Token> &head, std::stack<Token> &output);
  // // static std::optional<double> calcRpn(std::stack<Token> &output, double x_value);
  // static std::vector<Model::Token> replaceUnary(const std::vector<Model::Token>& tokens);
  // static double unaryFnCalc(double number1, Type type);
  // static double binaryFnCalc(double number1, double number2, Type type);
  // static void flipStack(std::stack<Token> input, std::stack<Token> &output);
};


// calcRPN
//  parce
//  validate
//  transform to RPN
//  calculateRPN (x) -> y

// graph
//  parce
//  validate
//  transform to RPN
//  calculate (x1,x2,x3,...) -> y1,y2,y3,...

}  //  namespace s21

#endif  //  SRC_MODEL_MODEL_H 