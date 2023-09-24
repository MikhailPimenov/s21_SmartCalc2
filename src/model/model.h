#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H


#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <stack>

class Model {
private:
  struct Token {
    double value;
    int type;
    int precedence;

  public:
    Token(double v, int t, int p) : value(v), type(t), precedence(p) {}
  };

  enum fn_type {
    type_number = 0,
    type_open_bracket = 1,
    type_close_bracket = 2,
    type_sum = 3,
    type_minus = 4,
    type_mult = 5,
    type_div = 6,
    type_power = 7,
    type_mod = 8,
    type_cos = 11,
    type_sin = 12,
    type_tan = 13,
    type_acos = 14,
    type_asin = 15,
    type_atan = 16,
    type_sqrt = 17,
    type_ln = 18,
    type_log = 19,
    type_x = 20
  };

public:
  static int main_for_calc(const char *input_str, double *result, double x_value);
  static int credit_calc_fn(double credit_sum, int credit_term, float credit_percent,
                    int type, double *monthlty_payment, double *overpayment,
                    double *total_sum);
  static int deposit_calc_fn(double deposit_sum, int deposit_term, float deposit_percent,
                      float tax_percent, int type_cap, int type_pay,
                      const double *add_sum, double *interest_income,
                      double *total_deposit_sum, double *tax_sum);


private:
  static int parcer(const char *input_str, std::stack<Token>& head);
  static void shunting_yard(std::stack<Token>& head, std::stack<Token>& output);
  static double calc_rpn(std::stack<Token>& output, double x_value);
  static double unary_fn_calc(double number1, int type);
  static double binary_fn_calc(double number1, double number2, int type);

  static void flip_stack(std::stack<Token>& input, std::stack<Token>& output);
};

#endif  //  SRC_MODEL_MODEL_H