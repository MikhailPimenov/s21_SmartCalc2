#include "calculator.h"
#include "calculatorRpn.h"
#include "parcer.h"
#include "validator.h"
#include "shuntingYard.h"
#include "flipStack.h"
#include "unaryReplacer.h"
#include "../protocol/protocol.h"
#include "graphCalculator.h"

namespace s21 {

Calculator::Calculator(const std::string& input) : input_{input} {}

bool Calculator::getRPN() {
  Parcer parcer(input_);
  std::optional<std::vector<Model::Token> > tokens = parcer.Run();
  if (!tokens.has_value())
    return false;

  Validator validator(tokens.value());
  if (!validator.Run())
    return false;

  UnaryReplacer unaryReplacer(tokens.value());
  const std::vector<Model::Token> tokensReplaced = unaryReplacer.Run();

  std::stack<Model::Token> head;
  for (auto it = tokensReplaced.crbegin(); it != tokensReplaced.crend(); ++it)
    head.push(*it);

  ShuntingYard shuntingYard(head);
  std::stack<Model::Token> pn = shuntingYard.Run();

  FlipStack flipStack(pn);
  std::stack<Model::Token> rpn = flipStack.Run();

  return true;
}


std::optional<double> SingleCalculator::Run() {
  if (!getRPN())
    return std::nullopt;

  CalculatorRpn calculator(rpn_, x_);
  return calculator.Run();
}

std::optional<Protocol::GraphResult> MultiCalculator::Run() {
  if (!getRPN())
    return std::nullopt;

  GraphCalculator graphCalculator(rpn_, )
}

}