#include "calculator.h"
#include "calculatorRpn.h"
#include "parcer.h"
#include "validator.h"
#include "shuntingYard.h"
#include "flipStack.h"

#include "model.h"

namespace s21 {

Calculator::Calculator(const std::string& input, double x) : input_{input}, x_{x} {}

std::optional<double> Calculator::Run() const {
  Parcer parcer(input_);
  std::optional<std::vector<Model::Token> > tokens = parcer.Run();
  if (!tokens.has_value())
    return std::nullopt;

  Validator validator(tokens.value());
  if (!validator.Run())
    return std::nullopt;

  const std::vector<Model::Token> tokensReplaced = Model::replaceUnary(tokens.value());
  std::stack<Model::Token> head;
  for (auto it = tokensReplaced.crbegin(); it != tokensReplaced.crend(); ++it)
    head.push(*it);

  ShuntingYard shuntingYard(head);
  std::stack<Model::Token> pn = shuntingYard.Run();

  FlipStack flipStack(pn);
  std::stack<Model::Token> rpn = flipStack.Run();

  CalculatorRpn calculator(rpn, x_);
  return calculator.Run();
}


}