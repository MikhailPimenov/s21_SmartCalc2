#include "token.h"

namespace s21 {

namespace Model {

bool Token::isUnaryLeftFunction() const {
  return type_ == Type::Sum || type_ == Type::Minus;
}

bool Token::isOpeningBrace() const { return type_ == Type::OpenBracket; }

bool Token::isBinaryFunction() const {
  return type_ == Type::Sum || type_ == Type::Minus || type_ == Type::Mult ||
         type_ == Type::Div || type_ == Type::Mod || type_ == Type::Power;
}

bool Token::isUnaryRightFunction() const {
  return type_ == Type::Asin || type_ == Type::Acos || type_ == Type::Atan ||
         type_ == Type::Sqrt || type_ == Type::Sin || type_ == Type::Cos ||
         type_ == Type::Tan || type_ == Type::Log || type_ == Type::Ln;
}

bool Token::isOperand() const {
  return type_ == Type::Number || type_ == Type::X;
}

bool Token::isClosingBrace() const { return type_ == Type::CloseBracket; }

}  // namespace Model

}  // namespace s21