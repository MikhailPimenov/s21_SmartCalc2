#include "calculator.h"
#include "calculatorRpn.h"
#include "parcer.h"
#include "validator.h"

#include "model.h"

namespace s21 {

Calculator::Calculator(const std::string& input, double x) : input_{input}, x_{x} {

}

std::optional<double> Calculator::Run() const {

  Parcer parcer3(input_);
  std::optional<std::vector<Model::Token> > tokens = parcer3.Run();
  if (!tokens.has_value())
    return std::nullopt;

  Validator validator(tokens.value());
  if (!validator.Run())
    return std::nullopt;

  const std::vector<Model::Token> tokensReplaced = Model::replaceUnary(tokens.value());
  std::stack<Model::Token> head;
  for (auto it = tokensReplaced.crbegin(); it != tokensReplaced.crend(); ++it)
    head.push(*it);

    // TODO: refactor that in OOP style
  std::stack<Model::Token> output;
  Model::shuntingYard(head, output);
  std::stack<Model::Token> input;
  Model::flipStack(output, input);
  CalculatorRpn calculator(input, x_);
  return calculator.Run();
}


}