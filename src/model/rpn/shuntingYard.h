#ifndef SRC_MODEL_SHUNTINGYARD_H
#define SRC_MODEL_SHUNTINGYARD_H

#include <optional>
#include <stack>
// #include "model.h"
#include "token.h"

namespace s21 {

class ShuntingYard {
private:
    std::stack<Model::Token>& input_;

public:
    ShuntingYard(std::stack<Model::Token> &input);
    std::stack<Model::Token> Run();
};

}   // namespace s21

#endif  //  SRC_MODEL_SHUNTINGYARD_H