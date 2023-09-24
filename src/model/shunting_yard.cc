#include "model.h"

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
