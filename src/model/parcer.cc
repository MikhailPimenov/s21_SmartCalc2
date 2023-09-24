#include "model.h"

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
