#include "calculator.h"
#include "../rpn/calculatorRpn.h"
#include "../parcer/parcer.h"
#include "../parcer/validator.h"
#include "../rpn/shuntingYard.h"
#include "../rpn/flipStack.h"
#include "../parcer/unaryReplacer.h"
#include "../../protocol/protocol.h"
#include "../graph/graphCalculator.h"

namespace s21 {

namespace Model {

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
  rpn_ = flipStack.Run();

  return true;
}

}   //  namespace Model

}   //  namespace s21