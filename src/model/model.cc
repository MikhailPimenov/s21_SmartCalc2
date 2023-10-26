#include "model.h"

#include <cmath>
#include <string>

#include "../protocol/protocol.h"



#include "calculatorRpn.h"
#include "parcer.h"
#include "validator.h"

namespace s21 {

// bool isUnaryLeftFunction(const Model::Token& token) {
//   return token.type == Model::Type::Sum ||
//          token.type == Model::Type::Minus;
// }

// bool isOpeningBrace(const Model::Token& token) {
//   return token.type == Model::Type::OpenBracket;
// }


bool Model::Token::isUnaryLeftFunction() const {
  return type_ == Type::Sum ||
         type_ == Type::Minus;
}

bool Model::Token::isOpeningBrace() const {
  return type_ == Type::OpenBracket;
}

bool Model::Token::isBinaryFunction() const {
  return type_ == Type::Sum ||
         type_ == Type::Minus ||
         type_ == Type::Mult ||
         type_ == Type::Div ||
         type_ == Type::Mod ||
         type_ == Type::Power;
}

bool Model::Token::isUnaryRightFunction() const {
  return type_ == Type::Asin ||
         type_ == Type::Acos ||
         type_ == Type::Atan ||
         type_ == Type::Sqrt ||
         type_ == Type::Sin ||
         type_ == Type::Cos ||
         type_ == Type::Tan ||
         type_ == Type::Log ||
         type_ == Type::Ln;
}

bool Model::Token::isOperand() const {
  return type_ == Type::Number ||
         type_ == Type::X;
}

bool Model::Token::isClosingBrace() const {
  return type_ == Type::CloseBracket;
}




std::vector<Model::Token> Model::replaceUnary(const std::vector<Model::Token>& tokens) {
  std::vector<Model::Token> result;
  result.reserve(4ull * tokens.size());

  if (!tokens.front().isUnaryLeftFunction()) {
    result.push_back(tokens.front());
  } else if (tokens.front().type_ == Model::Type::Minus) {
    result.emplace_back( 0.0, Model::Type::OpenBracket,   0);
    result.emplace_back(-1.0, Model::Type::Number,        1);
    result.emplace_back( 0.0, Model::Type::CloseBracket,  0);
    result.emplace_back( 0.0, Model::Type::Mult,          8);
  }

  for (int i = 1; i < tokens.size(); ++i) {
    if (tokens[i].type_ == Model::Type::Sum && tokens[i - 1].isOpeningBrace())
      continue;

    if (tokens[i].type_ == Model::Type::Minus && tokens[i - 1].isOpeningBrace()) {
      result.emplace_back( 0.0, Model::Type::OpenBracket,   0);
      result.emplace_back(-1.0, Model::Type::Number,        1);
      result.emplace_back( 0.0, Model::Type::CloseBracket,  0);
      result.emplace_back( 0.0, Model::Type::Mult,          8);
      continue;
    }
    result.push_back(tokens[i]);
  }

  return result;
}

std::optional<double> Model::Calculate(const std::string &input_str, double x_value) {
  std::stack<Token> head;
  std::stack<Token> output;
  std::stack<Token> input;

  Parcer parcer3(input_str);
  std::optional<std::vector<Token> > tokens = parcer3.Run();
  if (!tokens.has_value())
    return std::nullopt;

  Validator validator(tokens.value());
  if (!validator.Run())
    return std::nullopt;

  const std::vector<Model::Token> tokensReplaced = replaceUnary(tokens.value());
  for (auto it = tokensReplaced.crbegin(); it != tokensReplaced.crend(); ++it)
    head.push(*it);

  shuntingYard(head, output);
  flipStack(output, input);
  CalculatorRpn calculator(input, x_value);
  return calculator.Run();
}









// int Model::parcer2(const std::string &input_str, std::stack<Token> &head) {
//   int ex_code = 0;
//   const int len = static_cast<int>(input_str.size());
//   if (len == 0) ex_code = 1;
//   double number = 0;
//   int dot_qty = 0;
//   int open_bracket_qty = 0;
//   int close_bracket_qty = 0;
//   int operand_qty = 0;
//   int use_double_operand_operator = 0;  // false
//   int no_operand = 1;                   // true
//   for (int i = len - 1;
//        i >= 0 && ex_code == 0 && open_bracket_qty <= close_bracket_qty;) {
//     switch (input_str[i]) {
//       case '1':
//       case '2':
//       case '3':
//       case '4':
//       case '5':
//       case '6':
//       case '7':
//       case '8':
//       case '9':
//       case '0':
//       case '.':
//         dot_qty = 0;
//         while (i >= 0 && ((input_str[i] > 47 && input_str[i] < 58) ||
//                           input_str[i] == '.')) {
//           if (input_str[i] == '.') dot_qty += 1;
//           if (dot_qty > 1) {
//             ex_code = 1;
//             break;
//           }
//           i--;
//         }
//         i++;
//         number = strtod(&input_str[i], NULL);
//         head.push(Token(number, Type::Number, 1));
//         no_operand = 0;
//         ++operand_qty;
//         i--;
//         break;
//       case '(':
//         open_bracket_qty += 1;
//         head.push(Token(0, Type::OpenBracket, 0));
//         i--;
//         break;
//       case ')':
//         close_bracket_qty += 1;
//         head.push(Token(0, Type::CloseBracket, 0));
//         i--;
//         break;
//       case '+':
//         if (i == 0 || input_str[i - 1] == '(') {
//           head.push(Token(0, Type::Number, 1));
//         }
//         head.push(Token(0, Type::Sum, 6));
//         use_double_operand_operator = 1;  // true
//         i--;
//         break;
//       case '-':
//         if (i == 0 || input_str[i - 1] == '(') {
//           head.push(Token(-1.0, Type::Number, 1));
//           head.push(Token(0, Type::Mult, 6));
//           ++operand_qty;
//         } else {
//           head.push(Token(0, Type::Minus, 6));
//         }
//         use_double_operand_operator = 1;  // true
//         i--;
//         break;
//       case '*':
//         head.push(Token(0, Type::Mult, 8));
//         use_double_operand_operator = 1;  // true
//         no_operand = 1;
//         i--;
//         break;
//       case '/':
//         head.push(Token(0, Type::Div, 8));
//         use_double_operand_operator = 1;  // true
//         i--;
//         break;
//       case '^':
//         head.push(Token(0, Type::Power, 9));
//         use_double_operand_operator = 1;  // true
//         i--;
//         break;
//       case 'd':
//         head.push(Token(0, Type::Mod, 8));
//         use_double_operand_operator = 1;  // true
//         i = i - 3;
//         break;
//       case 's':
//         if (i > 2 && input_str[i - 3] == 'a') {
//           head.push(Token(0, Type::Acos, 8));
//           i = i - 4;
//         } else {
//           head.push(Token(0, Type::Cos, 8));
//           i = i - 3;
//         }
//         break;
//       case 'n':
//         if (i > 0 && input_str[i - 1] == 'l') {
//           head.push(Token(0, Type::Ln, 8));
//           i = i - 2;
//         } else if (i > 0 && input_str[i - 1] == 'a') {
//           if (i > 2 && input_str[i - 3] == 'a') {
//             head.push(Token(0, Type::Atan, 8));
//             i = i - 4;
//           } else {
//             head.push(Token(0, Type::Tan, 8));
//             i = i - 3;
//           }
//         } else if (i > 0 && input_str[i - 1] == 'i') {
//           if (i > 2 && input_str[i - 3] == 'a') {
//             head.push(Token(0, Type::Asin, 8));
//             i = i - 4;
//           } else {
//             head.push(Token(0, Type::Sin, 8));
//             i = i - 3;
//           }
//         }
//         break;
//       case 't':
//         head.push(Token(0, Type::Sqrt, 8));
//         i = i - 4;
//         break;
//       case 'g':
//         head.push(Token(0, Type::Log, 8));
//         i = i - 3;
//         break;
//       case 'x':
//         head.push(Token(0, Type::X, 1));
//         no_operand = 0;
//         ++operand_qty;
//         i--;
//         break;
//       default:
//         ex_code = 1;
//         break;
//     }
//   }
//   if (open_bracket_qty != close_bracket_qty) ex_code = 1;
//   if (no_operand) ex_code = 1;
//   if (use_double_operand_operator && operand_qty < 2) ex_code = 1;
//   return ex_code;
// }


// bool isBinaryFunction(const Model::Token& token) {
//   return token.type == Model::Type::Sum ||
//          token.type == Model::Type::Minus ||
//          token.type == Model::Type::Mult ||
//          token.type == Model::Type::Div ||
//          token.type == Model::Type::Mod ||
//          token.type == Model::Type::Power;
// }



// bool isUnaryRightFunction(const Model::Token& token) {
//   return token.type == Model::Type::Asin ||
//          token.type == Model::Type::Acos ||
//          token.type == Model::Type::Atan ||
//          token.type == Model::Type::Sqrt ||
//          token.type == Model::Type::Sin ||
//          token.type == Model::Type::Cos ||
//          token.type == Model::Type::Tan ||
//          token.type == Model::Type::Log ||
//          token.type == Model::Type::Ln;
// }

// bool isOperand(const Model::Token& token) {
//   return token.type == Model::Type::Number ||
//          token.type == Model::Type::X;
// }

// bool isClosingBrace(const Model::Token& token) {
//   return token.type == Model::Type::CloseBracket;
// }


//(5)(+)
// static bool validateBraces(const std::vector<Model::Token>& tokens) {
//   bool isPreviousOpen = false;
//   for (const Model::Token& token : tokens) {
//     if (isOpeningBrace(token)) {
//       isPreviousOpen = true;
//     }
//     else if (isClosingBrace(token)) {
//       if (isPreviousOpen)
//         return false;
//     } else if (isOperand(token)) {
//       isPreviousOpen = false;
//     }
//   }
//   std::stack<Model::Token> stack;


//   for (const Model::Token& token : tokens) {
//     if (!isOpeningBrace(token) && !isClosingBrace(token))
//       continue;

//     if (isOpeningBrace(token))
//       stack.push(token);
//     if (isClosingBrace(token)) {
//       if (stack.empty())
//         return false;
//       else
//         stack.pop();
//     }
//   }

//   return stack.empty(); 
// }


// static bool validateUnary(const std::vector<Model::Token>& tokens) {
//   for (int i = 1; i < tokens.size(); ++i)
//     if (isUnaryLeftFunction(tokens[i]) && isUnaryLeftFunction(tokens[i - 1]))
//       return false;

//   return true;
// }

// static bool validateBinary(const std::vector<Model::Token>& tokens) {
//   if (isBinaryFunction(tokens.front()) && !isUnaryLeftFunction(tokens.front()))
//     return false;

//   for (int i = 1; i < tokens.size() - 1; ++i) {
//     if (!isBinaryFunction(tokens[i]) || isUnaryLeftFunction(tokens[i]))
//       continue;
//     if (!isOperand(tokens[i - 1]) && !isClosingBrace(tokens[i - 1]))
//       return false;
//     if (!isOperand(tokens[i + 1]) && !isOpeningBrace(tokens[i + 1]) && !isUnaryRightFunction(tokens[i + 1]))
//       return false;
//   }
//   if (isBinaryFunction(tokens.back()))
//     return false;
//   if (isUnaryRightFunction(tokens.back()))
//     return false;

//   return true;
// }

// bool Model::validate(const std::vector<Model::Token>& tokens) {
//   if (!validateBinary(tokens))
//     return false;

//   if (!validateBraces(tokens))
//     return false;

//   if (!validateUnary(tokens))
//     return false;

//   return true;  
// }

// std::optional<double> Model::calcRpn(std::stack<Token> &input, double x_value) {
//   double result = 0.0;
//   std::stack<Token> stack;
//   while (!input.empty()) {
//     if (input.top().type == Type::Number) {
//       stack.push(input.top());
//       input.pop();
//     } else if (input.top().type == Type::X) {
//       input.top().value = x_value;
//       stack.push(input.top());
//       input.pop();
//     } else if (input.top().type >= Type::Sum && input.top().type <= Type::Mod &&
//                !stack.empty()) {
//       double number2 = stack.top().value;
//       stack.pop();
//       if (stack.empty())
//         return std::nullopt;
//       result = binaryFnCalc(stack.top().value, number2, input.top().type);
//       stack.pop();
//       input.pop();
//       stack.push(Token(result, Type::Number, 1));
//     } else if (input.top().type >= Type::Cos && !stack.empty()) {
//       result = unaryFnCalc(stack.top().value, input.top().type);
//       stack.pop();
//       input.pop();
//       stack.push(Token(result, Type::Number, 1));
//     }
//   }
//   if (!stack.empty()) result = stack.top().value;
//   stack.pop();
//   return result;
// }



void Model::shuntingYard(std::stack<Token> &head, std::stack<Token> &output) {
  std::stack<Token> stack;
  while (!head.empty()) {
    if (head.top().type_ == Type::Number || head.top().type_ == Type::X) {
      output.push(head.top());
      head.pop();
    } else if (head.top().type_ == Type::OpenBracket) {
      stack.push(head.top());
      head.pop();
    } else if (head.top().type_ == Type::CloseBracket) {
      while (!stack.empty() && stack.top().type_ != Type::OpenBracket) {
        output.push(stack.top());
        stack.pop();
      }
      stack.pop();
      if (!stack.empty() && static_cast<int>(stack.top().type_) > 10) {
        output.push(stack.top());
        stack.pop();
      }
      head.pop();
    } else if (static_cast<int>(head.top().type_) >=
                   static_cast<int>(Type::Sum) &&
               static_cast<int>(head.top().type_) <=
                   static_cast<int>(Type::Mod) &&
               head.top().type_ != Type::Power) {
      while (!stack.empty() &&
             (stack.top().precedence_ >= head.top().precedence_)) {
        output.push(stack.top());
        stack.pop();
      }
      stack.push(head.top());
      head.pop();
    } else if (head.top().type_ == Type::Power) {
      while (!stack.empty() &&
             (stack.top().precedence_ > head.top().precedence_)) {
        output.push(stack.top());
        stack.pop();
      }
      stack.push(head.top());
      head.pop();
    } else if (static_cast<int>(head.top().type_) >=
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
    // double result = 0.0;
    // const std::optional<double> result = Calculate(gp.input_string, gr.x[i]);
    const std::optional<double> result = std::nullopt;
    if (!result.has_value())
      return 1;
    gr.y[i] = result.value();
  }
  return ex_code;
}

}  //  namespace s21