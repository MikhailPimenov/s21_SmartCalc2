#include "model.h"

void Model::flip_stack(std::stack<Token>& input, std::stack<Token>& output) {
  while (!input.empty()) {
    output.push(input.top());
    input.pop();
  }
}
