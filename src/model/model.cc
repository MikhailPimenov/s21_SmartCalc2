#include <cmath>

#include "model.h"

int Model::main_for_calc(const char *input_str, double *result, double x_value) {
  printf("string = %s\nx_value = %f\n", input_str, x_value);
  printf("main_for_calc...\n");
  int ex_code = 0;
  std::stack<Token> head;
  std::stack<Token> output;
  std::stack<Token> input;
  printf("parcer...\n");
  ex_code = parcer(input_str, head);
  printf("parcer ended...\n");
  if (ex_code == 0) {
    printf("shunting_yard...\n");
    shunting_yard(head, output);
    printf("shunting_yard ended...\n");
    printf("flip_stack...\n");
    flip_stack(output, input);
    printf("flip_stack ended...\n");
    printf("calc_rpn...\n");
    *result = calc_rpn(input, x_value);
    printf("calc_rpn ended...\n");
  } else {
    while (!head.empty()) {
      head.pop();
    }
  }
  printf("main_for_calc ended...\n");
  return ex_code;
}

int Model::parcer(const char *input_str, std::stack<Token>& head) {
  int ex_code = 0;
  int len = static_cast<int>(strlen(input_str));
  if (len == 0) ex_code = 1;
  double number = 0;
  int dot_qty = 0;
  int open_bracket_qty = 0;
  int close_bracket_qty = 0;
  int operand_qty = 0;
  int use_double_operand_operator = 0;  // false
  for (int i = len - 1;
       i >= 0 && ex_code == 0 && open_bracket_qty <= close_bracket_qty;) {
    switch (input_str[i]) {
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '0':
      case '.':
        dot_qty = 0;
        while (i >= 0 && ((input_str[i] > 47 && input_str[i] < 58) ||
                          input_str[i] == '.')) {
          if (input_str[i] == '.') dot_qty += 1;
          if (dot_qty > 1) {
            ex_code = 1;
            break;
          }
          i--;
        }
        i++;
        number = strtod(&input_str[i], NULL);
        head.push(Token(number, type_number, 1));
        ++operand_qty;
        i--;
        break;
      case '(':
        open_bracket_qty += 1;
        head.push(Token(0, type_open_bracket, 0));
        i--;
        break;
      case ')':
        close_bracket_qty += 1;
        head.push(Token(0, type_close_bracket, 0));
        i--;
        break;
      case '+':
        if (i == 0 || input_str[i - 1] == '(') {
          head.push(Token(0, type_number, 1));
        }
        head.push(Token(0, type_sum, 6));
        use_double_operand_operator = 1;  // true
        i--;
        break;
      case '-':
        if (i == 0 || input_str[i - 1] == '(') {
          head.push(Token(0, type_number, 1));
        }
        head.push(Token(0, type_minus, 6));
        use_double_operand_operator = 1;  // true
        i--;
        break;
      case '*':
        head.push(Token(0, type_mult, 8));
        use_double_operand_operator = 1;  // true
        i--;
        break;
      case '/':
        head.push(Token(0, type_div, 8));
        use_double_operand_operator = 1;  // true
        i--;
        break;
      case '^':
        head.push(Token(0, type_power, 9));
        use_double_operand_operator = 1;  // true
        i--;
        break;
      case 'd':
        head.push(Token(0, type_mod, 8));
        use_double_operand_operator = 1;  // true
        i = i - 3;
        break;
      case 's':
        if (i > 2 && input_str[i - 3] == 'a') {
          head.push(Token(0, type_acos, 8));
          i = i - 4;
        } else {
          head.push(Token(0, type_cos, 8));
          i = i - 3;
        }
        break;
      case 'n':
        if (i > 0 && input_str[i - 1] == 'l') {
          head.push(Token(0, type_ln, 8));
          i = i - 2;
        } else if (i > 0 && input_str[i - 1] == 'a') {
          if (i > 2 && input_str[i - 3] == 'a') {
            head.push(Token(0, type_atan, 8));
            i = i - 4;
          } else {
            head.push(Token(0, type_tan, 8));
            i = i - 3;
          }
        } else if (i > 0 && input_str[i - 1] == 'i') {
          if (i > 2 && input_str[i - 3] == 'a') {
            head.push(Token(0, type_asin, 8));
            i = i - 4;
          } else {
            head.push(Token(0, type_sin, 8));
            i = i - 3;
          }
        }
        break;
      case 't':
        head.push(Token(0, type_sqrt, 8));
        i = i - 4;
        break;
      case 'g':
        head.push(Token(0, type_log, 8));
        i = i - 3;
        break;
      case 'x':
        head.push(Token(0, type_x, 1));
        ++operand_qty;
        i--;
        break;
    }
  }
  if (open_bracket_qty != close_bracket_qty) ex_code = 1;
  if (use_double_operand_operator && operand_qty < 2) ex_code = 1;
  return ex_code;
}

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

void Model::shunting_yard(std::stack<Token>& head, std::stack<Token>& output) {
  std::stack<Token> stack;
  while (!head.empty()) {
    if (head.top().type == type_number || head.top().type == type_x) {
      output.push(head.top());
      head.pop();
    } else if (head.top().type == type_open_bracket) {
      stack.push(head.top());
      head.pop();
    } else if (head.top().type == type_close_bracket) {
      while (!stack.empty() && stack.top().type != type_open_bracket) {
        output.push(stack.top());
        stack.pop();
      }
      stack.pop();
      if (!stack.empty() && stack.top().type > 10) {
        output.push(stack.top());
        stack.pop();
      }
      head.pop();
    } else if (head.top().type >= type_sum && head.top().type <= type_mod &&
               head.top().type != type_power) {
      while (!stack.empty() && (stack.top().precedence >= head.top().precedence)) {
        output.push(stack.top());
        stack.pop();
      }
      stack.push(head.top());
      head.pop();
    } else if (head.top().type == type_power) {
      while (!stack.empty() && (stack.top().precedence > head.top().precedence)) {
        output.push(stack.top());
        stack.pop();
      }
      stack.push(head.top());
      head.pop();
    } else if (head.top().type >= type_cos) {
      stack.push(head.top());
      head.pop();
    }
  }
  while (!stack.empty()) {
    output.push(stack.top());
    stack.pop();
  }
}


void Model::flip_stack(std::stack<Token>& input, std::stack<Token>& output) {
  while (!input.empty()) {
    output.push(input.top());
    input.pop();
  }
}
