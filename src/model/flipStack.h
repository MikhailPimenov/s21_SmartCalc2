#ifndef SRC_MODEL_FLIPSTACK_H
#define SRC_MODEL_FLIPSTACK_H

#include <optional>
#include "model.h"

namespace s21 {

class FlipStack {
private:
    std::stack<Model::Token>& input_;

public:
    FlipStack(std::stack<Model::Token> &input);
    std::stack<Model::Token> Run();
};

}   // namespace s21

#endif  //  SRC_MODEL_FLIPSTACK_H