#include <cmath>
#include "model.h"

double Model::calc_rpn(std::stack<Token>& input, double x_value) {
  double result = 0;
  std::stack<Token> stack;
  while (!input.empty()) {
    if (input.top().type == type_number) {
      stack.push(input.top());
      input.pop();
    } else if (input.top().type == type_x) {
      input.top().value = x_value;
      stack.push(input.top());
      input.pop();
    } else if (input.top().type >= type_sum && input.top().type <= type_mod &&
               !stack.empty()) {
      double number2 = stack.top().value;
      stack.pop();
      result = binary_fn_calc(stack.top().value, number2, input.top().type);
      stack.pop();
      input.pop();
      stack.push(Token(result, type_number, 1));
    } else if (input.top().type >= type_cos && !stack.empty()) {
      result = unary_fn_calc(stack.top().value, input.top().type);
      stack.pop();
      input.pop();
      stack.push(Token(result, type_number, 1));
    }
  }
  if (!stack.empty()) result = stack.top().value;
  stack.pop();
  return result;
}

double Model::unary_fn_calc(double number1, int type) {
  double result = 0;
  if (type == type_cos) result = std::cos(number1);
  if (type == type_sin) result = std::sin(number1);
  if (type == type_tan) result = std::tan(number1);
  if (type == type_acos) result = std::acos(number1);
  if (type == type_asin) result = std::asin(number1);
  if (type == type_atan) result = std::atan(number1);
  if (type == type_sqrt) result = std::sqrt(number1);
  if (type == type_ln) result = std::log(number1);
  if (type == type_log) result = std::log10(number1);
  return result;
}

double Model::binary_fn_calc(double number1, double number2, int type) {
  double result = 0;
  if (type == type_sum) result = number1 + number2;
  if (type == type_minus) result = number1 - number2;
  if (type == type_mult) result = number1 * number2;
  if (type == type_div) result = number1 / number2;
  if (type == type_power) result = std::pow(number1, number2);
  if (type == type_mod) result = std::fmod(number1, number2);
  return result;
}
