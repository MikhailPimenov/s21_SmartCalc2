#include "model.h"

#include <cmath>
#include <string>

#include "../protocol/protocol.h"

#include "iostream"
#include "iomanip"
#include "sstream"


namespace s21 {

int Model::Calculate(const std::string &input_str, double *result,
                     double x_value) {
  std::stack<Token> head;
  std::stack<Token> output;
  std::stack<Token> input;
  // const int ex_code = parcer(input_str, head);
  const int ex_code = 1;
  if (ex_code == 0) {
    shuntingYard(head, output);
    flipStack(output, input);
    const std::optional<double> opt = calcRpn(input, x_value);
    if (!opt.has_value())
      return 1;
    *result = opt.value();
  } else {
    while (!head.empty()) {
      head.pop();
    }
  }
  return ex_code;
}

//"cos(x)" -> cos, (, x, )
// "cos(x)" -> ), x, (, cos
// "coa(x)" -> std::nullopt
// "(cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150)"




    // Mod = 8,
    // Cos = 11,
    // Sin = 12,
    // Tan = 13,
    // Acos = 14,
    // Asin = 15,
    // Atan = 16,
    // Sqrt = 17,
    // Ln = 18,
    // Log = 19,
// ln(123.4) -> ln, (, 123.4, )
// 1234*5
 std::pair<double, int> number(const std::string& string, int index) {

  std::istringstream iss(string);
  iss.seekg(index);
  double result = 0.0;
  int i1 = iss.tellg();
  iss >> result;
  int i2 = iss.tellg();
  bool fail = iss.fail();
  bool eof = iss.eof();

  if (iss.eof())
    index = static_cast<int>(string.size());
  else if (!iss.fail())
    index = static_cast<int>(iss.tellg());

    
  return std::make_pair(result, index);
 }





std::optional<std::stack<Model::Token>> Model::parcer(const std::string &input_str) {
// пройтись по всей входной строке
// если число, добавить число
// если скобка, добавить скобку
// если функция (+-*/ синус косинус и почее), добавить функцию
  std::stack<Token> result;
  // return std::nullopt;
  for(int i = 0; i < input_str.size(); i++) {
    // std::cout << "aaa\n"; 
    const char s = input_str[i];


    if(s == '(') {
      result.push(Token(0.0, Type::OpenBracket, 0));
    } else if(s == ')') {
      result.push(Token(0.0, Type::CloseBracket, 0));
    } else if (s == '+') {
      result.push(Token(0.0, Type::Sum, 6));
    } else if (s == '-') {
      result.push(Token(0.0, Type::Minus, 6));
    } else if (s == '/') {
      result.push(Token(0.0, Type::Div, 8));
    } else if (s == '*') {
      result.push(Token(0.0, Type::Mult, 8));
    } else if (s == '^') {
      result.push(Token(0.0, Type::Power, 9));
    } else if (s == 'x') {
      result.push(Token(0.0, Type::X, 1));
    }
    else if (input_str.compare(i, 3, "cos") == 0) {
      result.push(Token(0.0, Type::Cos, 8));
      i += 2;
    } // else if (input_str.find("cot", i)) {
    //   result.push(Token(0.0, Type::Cos, 8));
    //   i += 2;
    //}
    else if (input_str.compare(i, 3, "sin") == 0) {
      result.push(Token(0.0, Type::Sin, 8));
      i += 2;
    } else if (input_str.compare(i, 3, "mod") == 0) {
      result.push(Token(0.0, Type::Mod, 8));
      i += 2;
    } else if (input_str.compare(i, 3, "tan") == 0) {
      result.push(Token(0.0, Type::Tan, 8));
      i += 2;
    } else if (input_str.compare(i, 4, "acos") == 0) {
      result.push(Token(0.0, Type::Acos, 8));
      i += 3;
    } else if (input_str.compare(i, 4, "asin") == 0) {
      result.push(Token(0.0, Type::Asin, 8));
      i += 3;
    } else if (input_str.compare(i, 4, "atan") == 0) {
      result.push(Token(0.0, Type::Atan, 8));
      i += 3;
    } else if (input_str.compare(i, 4, "sqrt") == 0) {
      result.push(Token(0.0, Type::Sqrt, 8));
      i += 3;
    } else if (input_str.compare(i, 2, "ln") == 0) {
      result.push(Token(0.0, Type::Ln, 8));
      i += 1;
    } else if (input_str.compare(i, 3, "log") == 0) {
      result.push(Token(0.0, Type::Log, 8));
      i += 2;
    } else if (const auto& [n, index] = number(input_str, i); index > i) {
      result.push(Token(n, Type::Number, 1));
      // std::cout << index << '\n';
      i = (index - 1);
    } else {
      return std::nullopt;
    }
  } 
  return std::optional<std::stack<Token>>(result);  
}

int Model::parcer2(const std::string &input_str, std::stack<Token> &head) {
  int ex_code = 0;
  const int len = static_cast<int>(input_str.size());
  if (len == 0) ex_code = 1;
  double number = 0;
  int dot_qty = 0;
  int open_bracket_qty = 0;
  int close_bracket_qty = 0;
  int operand_qty = 0;
  int use_double_operand_operator = 0;  // false
  int no_operand = 1;                   // true
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
        no_operand = 0;
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
        no_operand = 1;
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
        no_operand = 0;
        ++operand_qty;
        i--;
        break;
      default:
        ex_code = 1;
        break;
    }
  }
  if (open_bracket_qty != close_bracket_qty) ex_code = 1;
  if (no_operand) ex_code = 1;
  if (use_double_operand_operator && operand_qty < 2) ex_code = 1;
  return ex_code;
}

static bool validateBraces(std::stack<Model::Token> tokens) {
  std::stack<Model::Token> stack;

  while (!tokens.empty()) {
    const auto token = tokens.top();
    tokens.pop();
    if (token.type != Model::Type::OpenBracket && token.type != Model::Type::CloseBracket)
      continue;


    
  }
  return true;
}

static bool validateUnary(std::stack<Model::Token> tokens) {
  return true;
}

static bool validateBinary(std::stack<Model::Token> tokens) {
  return true;
}

bool Model::validate(std::stack<Token> tokens) {

  if (!validateBinary(tokens))
    return false;

  if (!validateBraces(tokens))
    return false;

  if (!validateUnary(tokens))
    return false;

  return true;  
}

std::optional<double> Model::calcRpn(std::stack<Token> &input, double x_value) {
  double result = 0.0;
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
      if (stack.empty())
        return std::nullopt;
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