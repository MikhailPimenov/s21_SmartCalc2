#ifndef SRC_MODEL_CALCULATOR_H
#define SRC_MODEL_CALCULATOR_H

#include <optional>
#include <stack>
#include <string>
#include "../parcer/token.h"

/**
 * General namespace
 * **/
namespace s21 {

namespace Protocol {
    struct GraphParameters;
    struct GraphResult;
}

/**
 * Namespace for all model components
 * **/
namespace Model {

/**
 * The purpose of this class is to parce and check the input expression
 * **/
class ExpressionToTokens {
private:
    const std::string input_;
    std::stack<Model::Token> rpn_;

public:
    explicit ExpressionToTokens(const std::string& input);
    bool Run();
    std::stack<Model::Token>& Get();
};

}   // namespace Model

}   // namespace s21

#endif  //  SRC_MODEL_CALCULATOR_RPN_H