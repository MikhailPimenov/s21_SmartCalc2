#include "model.h"

#include <cmath>
#include <string>

#include "../protocol/protocol.h"

namespace s21 {

int Model::Calculate(const std::string &input_str, double *result,
                     double x_value) {
  std::stack<Token> head;
  std::stack<Token> output;
  std::stack<Token> input;
  const int ex_code = parcer(input_str, head);
  if (ex_code == 0) {
    shuntingYard(head, output);
    flipStack(output, input);
    *result = calcRpn(input, x_value);
  } else {
    while (!head.empty()) {
      head.pop();
    }
  }
  return ex_code;
}

int Model::parcer(const std::string &input_str, std::stack<Token> &head) {
  int ex_code = 0;
  const int len = static_cast<int>(input_str.size());
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
        head.push(Token(number, Type::Number, 1));
        ++operand_qty;
        i--;
        break;
      case '(':
        open_bracket_qty += 1;
        head.push(Token(0, Type::OpenBracket, 0));
        i--;
        break;
      case ')':
        close_bracket_qty += 1;
        head.push(Token(0, Type::CloseBracket, 0));
        i--;
        break;
      case '+':
        if (i == 0 || input_str[i - 1] == '(') {
          head.push(Token(0, Type::Number, 1));
        }
        head.push(Token(0, Type::Sum, 6));
        use_double_operand_operator = 1;  // true
        i--;
        break;
      case '-':
        if (i == 0 || input_str[i - 1] == '(') {
          head.push(Token(-1.0, Type::Number, 1));
          head.push(Token(0, Type::Mult, 6));
          ++operand_qty;
        } else {
          head.push(Token(0, Type::Minus, 6));
        }
        use_double_operand_operator = 1;  // true
        i--;
        break;
      case '*':
        head.push(Token(0, Type::Mult, 8));
        use_double_operand_operator = 1;  // true
        i--;
        break;
      case '/':
        head.push(Token(0, Type::Div, 8));
        use_double_operand_operator = 1;  // true
        i--;
        break;
      case '^':
        head.push(Token(0, Type::Power, 9));
        use_double_operand_operator = 1;  // true
        i--;
        break;
      case 'd':
        head.push(Token(0, Type::Mod, 8));
        use_double_operand_operator = 1;  // true
        i = i - 3;
        break;
      case 's':
        if (i > 2 && input_str[i - 3] == 'a') {
          head.push(Token(0, Type::Acos, 8));
          i = i - 4;
        } else {
          head.push(Token(0, Type::Cos, 8));
          i = i - 3;
        }
        break;
      case 'n':
        if (i > 0 && input_str[i - 1] == 'l') {
          head.push(Token(0, Type::Ln, 8));
          i = i - 2;
        } else if (i > 0 && input_str[i - 1] == 'a') {
          if (i > 2 && input_str[i - 3] == 'a') {
            head.push(Token(0, Type::Atan, 8));
            i = i - 4;
          } else {
            head.push(Token(0, Type::Tan, 8));
            i = i - 3;
          }
        } else if (i > 0 && input_str[i - 1] == 'i') {
          if (i > 2 && input_str[i - 3] == 'a') {
            head.push(Token(0, Type::Asin, 8));
            i = i - 4;
          } else {
            head.push(Token(0, Type::Sin, 8));
            i = i - 3;
          }
        }
        break;
      case 't':
        head.push(Token(0, Type::Sqrt, 8));
        i = i - 4;
        break;
      case 'g':
        head.push(Token(0, Type::Log, 8));
        i = i - 3;
        break;
      case 'x':
        head.push(Token(0, Type::X, 1));
        ++operand_qty;
        i--;
        break;
      default:
        ex_code = 1;
        break;
    }
  }
  if (open_bracket_qty != close_bracket_qty) ex_code = 1;
  if (use_double_operand_operator && operand_qty < 2) ex_code = 1;
  return ex_code;
}

double Model::calcRpn(std::stack<Token> &input, double x_value) {
  double result = 0;
  std::stack<Token> stack;
  while (!input.empty()) {
    if (input.top().type == Type::Number) {
      stack.push(input.top());
      input.pop();
    } else if (input.top().type == Type::X) {
      input.top().value = x_value;
      stack.push(input.top());
      input.pop();
    } else if (input.top().type >= Type::Sum && input.top().type <= Type::Mod &&
               !stack.empty()) {
      double number2 = stack.top().value;
      stack.pop();
      result = binaryFnCalc(stack.top().value, number2, input.top().type);
      stack.pop();
      input.pop();
      stack.push(Token(result, Type::Number, 1));
    } else if (input.top().type >= Type::Cos && !stack.empty()) {
      result = unaryFnCalc(stack.top().value, input.top().type);
      stack.pop();
      input.pop();
      stack.push(Token(result, Type::Number, 1));
    }
  }
  if (!stack.empty()) result = stack.top().value;
  stack.pop();
  return result;
}

double Model::unaryFnCalc(double number1, Type type) {
  double result = 0;
  if (type == Type::Cos) result = std::cos(number1);
  if (type == Type::Sin) result = std::sin(number1);
  if (type == Type::Tan) result = std::tan(number1);
  if (type == Type::Acos) result = std::acos(number1);
  if (type == Type::Asin) result = std::asin(number1);
  if (type == Type::Atan) result = std::atan(number1);
  if (type == Type::Sqrt) result = std::sqrt(number1);
  if (type == Type::Ln) result = std::log(number1);
  if (type == Type::Log) result = std::log10(number1);
  return result;
}

double Model::binaryFnCalc(double number1, double number2, Type type) {
  double result = 0;
  if (type == Type::Sum) result = number1 + number2;
  if (type == Type::Minus) result = number1 - number2;
  if (type == Type::Mult) result = number1 * number2;
  if (type == Type::Div) result = number1 / number2;
  if (type == Type::Power) result = std::pow(number1, number2);
  if (type == Type::Mod) result = std::fmod(number1, number2);
  return result;
}

void Model::shuntingYard(std::stack<Token> &head, std::stack<Token> &output) {
  std::stack<Token> stack;
  while (!head.empty()) {
    if (head.top().type == Type::Number || head.top().type == Type::X) {
      output.push(head.top());
      head.pop();
    } else if (head.top().type == Type::OpenBracket) {
      stack.push(head.top());
      head.pop();
    } else if (head.top().type == Type::CloseBracket) {
      while (!stack.empty() && stack.top().type != Type::OpenBracket) {
        output.push(stack.top());
        stack.pop();
      }
      stack.pop();
      if (!stack.empty() && static_cast<int>(stack.top().type) > 10) {
        output.push(stack.top());
        stack.pop();
      }
      head.pop();
    } else if (static_cast<int>(head.top().type) >=
                   static_cast<int>(Type::Sum) &&
               static_cast<int>(head.top().type) <=
                   static_cast<int>(Type::Mod) &&
               head.top().type != Type::Power) {
      while (!stack.empty() &&
             (stack.top().precedence >= head.top().precedence)) {
        output.push(stack.top());
        stack.pop();
      }
      stack.push(head.top());
      head.pop();
    } else if (head.top().type == Type::Power) {
      while (!stack.empty() &&
             (stack.top().precedence > head.top().precedence)) {
        output.push(stack.top());
        stack.pop();
      }
      stack.push(head.top());
      head.pop();
    } else if (static_cast<int>(head.top().type) >=
               static_cast<int>(Type::Cos)) {
      stack.push(head.top());
      head.pop();
    }
  }
  while (!stack.empty()) {
    output.push(stack.top());
    stack.pop();
  }
}

void Model::flipStack(std::stack<Token> input, std::stack<Token> &output) {
  while (!input.empty()) {
    output.push(input.top());
    input.pop();
  }
}

int Model::CalculateGraph(const Protocol::GraphParameters &gp,
                          Protocol::GraphResult &gr) {
  static constexpr double x_range = 10000.0;
  double x_step = abs(gp.x_max - gp.x_min) / x_range;
  int ex_code = 0;

  gr.x.resize(x_range);
  gr.y.resize(x_range);
  for (int i = 0; i < x_range && ex_code == 0; ++i) {
    gr.x[i] = gp.x_min + x_step * i;
    double result = 0.0;
    ex_code = Calculate(gp.input_string, &result, gr.x[i]);
    gr.y[i] = result;
  }
  return ex_code;
}

}  //  namespace s21