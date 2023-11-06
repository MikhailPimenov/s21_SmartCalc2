#ifndef SRC_MODEL_VALIDATOR_H
#define SRC_MODEL_VALIDATOR_H

// #include "model.h"
#include <vector>

#include "token.h"

namespace s21 {

class Validator {
private:
    const std::vector<Model::Token>& input_;

public:
    Validator(const std::vector<Model::Token>& input);

    bool Run() const;


private:
    bool validateUnary() const;
    bool validateBinary() const;
    bool validateBraces() const;


public:


};  // class Validator

}   // namespace s21

#endif  //  SRC_MODEL_VALIDATOR_H