#include "expressionToTokens.h"
// #include "../rpn/calculatorRpn.h"
#include "../parcer/parcer.h"
#include "../parcer/unaryReplacer.h"
#include "../parcer/validator.h"
#include "../rpn/flipStack.h"
#include "../rpn/shuntingYard.h"

namespace s21 {

namespace Model {

ExpressionToTokens::ExpressionToTokens(const std::string& input)
    : input_{input} {}

bool ExpressionToTokens::Run() {
  Parcer parcer(input_);
  std::optional<std::vector<Model::Token> > tokens = parcer.Run();
  if (!tokens.has_value()) return false;

  Validator validator(tokens.value());
  if (!validator.Run()) return false;

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

std::stack<Model::Token>& ExpressionToTokens::Get() { return rpn_; }

}  //  namespace Model

}  //  namespace s21