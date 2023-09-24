// #include <stack>
// #include <queue>
#include "model.h"

// void shunting_yard(token **head, token **output) {
void shunting_yard(std::stack<token>& head, std::stack<token>& output) {
  // token *stack = NULL;
  std::stack<token> stack;
  // while (*head != NULL) {
  while (!head.empty()) {
    // if ((*head)->type == type_number || (*head)->type == type_x) {
    if (head.top().type == type_number || head.top().type == type_x) {
      // copy_token(head, output);
      output.push(head.top());
      // pop(head);
      head.pop();
    // } else if ((*head)->type == type_open_bracket) {
    } else if (head.top().type == type_open_bracket) {
      // copy_token(head, &stack);
      stack.push(head.top());
      // pop(head);
      head.pop();
    // } else if ((*head)->type == type_close_bracket) {
    } else if (head.top().type == type_close_bracket) {
      // while (stack != NULL && (*stack).type != type_open_bracket) {
      while (!stack.empty() && stack.top().type != type_open_bracket) {
        // copy_token(&stack, output);
        output.push(stack.top());
        // pop(&stack);
        stack.pop();
      }
      // pop(&stack);
      stack.pop();
      // if (stack != NULL && (*stack).type > 10) {
      if (!stack.empty() && stack.top().type > 10) {
        // copy_token(&stack, output);
        output.push(stack.top());
        // pop(&stack);
        stack.pop();
      }
      // pop(head);
      head.pop();
    // } else if ((*head)->type >= type_sum && (*head)->type <= type_mod &&
    } else if (head.top().type >= type_sum && head.top().type <= type_mod &&
              //  (*head)->type != type_power) {
               head.top().type != type_power) {
      // while (stack != NULL && ((*stack).precedence >= (*head)->precedence)) {
      while (!stack.empty() && (stack.top().precedence >= head.top().precedence)) {
        // copy_token(&stack, output);
        output.push(stack.top());
        // pop(&stack);
        stack.pop();
      }
      // copy_token(head, &stack);
      stack.push(head.top());
      // pop(head);
      head.pop();
    // } else if ((*head)->type == type_power) {
    } else if (head.top().type == type_power) {
      // while (stack != NULL && ((*stack).precedence > (*head)->precedence)) {
      while (!stack.empty() && (stack.top().precedence > head.top().precedence)) {
        // copy_token(&stack, output);
        output.push(stack.top());
        // pop(&stack);
        stack.pop();
      }
      // copy_token(head, &stack);
      stack.push(head.top());
      // pop(head);
      head.pop();
    // } else if ((*head)->type >= type_cos) {
    } else if (head.top().type >= type_cos) {
      // copy_token(head, &stack);
      stack.push(head.top());
      // pop(head);
      head.pop();
    }
  }
  // while (stack != NULL) {
  while (!stack.empty()) {
    // copy_token(&stack, output);
    output.push(stack.top());
    // pop(&stack);
    stack.pop();
  }
}
