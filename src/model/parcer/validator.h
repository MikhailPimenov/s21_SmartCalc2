#ifndef SRC_MODEL_VALIDATOR_H
#define SRC_MODEL_VALIDATOR_H

// #include "model.h"
#include <vector>

#include "token.h"

namespace s21 {

/**
 * @brief Validator
 *
 * Defins if token is a number, or a bracket or an operand 
 * Adds tokens into std::stack
 * 
 * @param input_ Input parameters
 */

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