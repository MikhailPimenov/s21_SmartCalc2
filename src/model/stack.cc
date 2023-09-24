#include "model.h"

void Model::flip_stack(std::stack<token>& input, std::stack<token>& output) {
  while (!input.empty()) {
    output.push(input.top());
    input.pop();
  }
}
