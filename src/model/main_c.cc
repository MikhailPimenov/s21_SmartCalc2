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
