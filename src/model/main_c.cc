#include "model.h"

int main_for_calc(const char *input_str, double *result, double x_value) {
  printf("main_for_calc...\n");
  int ex_code = 0;
  // token *head = NULL;
  // token *output = NULL;
  // token *input = NULL;
  std::stack<token> head;
  std::stack<token> output;
  std::stack<token> input;
  printf("parcer...\n");
  // ex_code = parcer(input_str, &head);
  ex_code = parcer(input_str, head);
  printf("parcer ended...\n");
  if (ex_code == 0) {
    printf("shunting_yard...\n");
    // shunting_yard(&head, &output);
    // shunting_yard(&head, &output);
    shunting_yard(head, output);
    printf("shunting_yard ended...\n");
    printf("flip_stack...\n");
    // flip_stack(&output, &input);
    flip_stack(output, input);
    printf("flip_stack ended...\n");
    printf("calc_rpn...\n");
    // *result = calc_rpn(&input, x_value);
    *result = calc_rpn(input, x_value);
    printf("calc_rpn ended...\n");
  } else {
    // while (head != NULL) {
    while (!head.empty()) {
      // pop(&head);
      head.pop();
    }
  }
  printf("main_for_calc ended...\n");
  return ex_code;
}
