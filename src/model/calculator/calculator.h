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
 * Base class for calculating expression via rpn.
 * The purpose of this class is to parce and check the input expression
 * **/
class Calculator {
private:
    const std::string& input_;
    
protected:
    std::stack<Model::Token> rpn_;

protected:
    explicit Calculator(const std::string& input);

protected:
    bool getRPN();
};

}   // namespace Model

}   // namespace s21

#endif  //  SRC_MODEL_CALCULATOR_RPN_H