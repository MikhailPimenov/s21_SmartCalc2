#ifndef SRC_MODEL_VALIDATOR_H
#define SRC_MODEL_VALIDATOR_H

#include "model.h"
#include <vector>

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
    static bool isUnaryLeftFunction(const Model::Token& token);
    static bool isOpeningBrace(const Model::Token& token);
    static bool isBinaryFunction(const Model::Token& token);
    static bool isUnaryRightFunction(const Model::Token& token);
    static bool isOperand(const Model::Token& token);
    static bool isClosingBrace(const Model::Token& token);

};  // class Validator

}   // namespace s21

#endif  //  SRC_MODEL_VALIDATOR_H