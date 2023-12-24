#ifndef SRC_MODEL_TOKEN_H
#define SRC_MODEL_TOKEN_H

namespace s21 {

namespace Model {

/**
 * @brief Token type. Either number, or function, or bracket, or placeholder X
 *
 */
enum class Type : int {
  Number = 0,
  OpenBracket = 1,
  CloseBracket = 2,
  Sum = 3,
  Minus = 4,
  Mult = 5,
  Div = 6,
  Power = 7,
  Mod = 8,
  Cos = 11,
  Sin = 12,
  Tan = 13,
  Acos = 14,
  Asin = 15,
  Atan = 16,
  Sqrt = 17,
  Ln = 18,
  Log = 19,
  X = 20,
};

/**
 * @brief Type of element the input string consists of
 * Has value, type of value and precedence.
 * Precedence defines the order of calculations
 */
struct Token {
  double value_;
  Type type_;
  int precedence_;

 public:
  Token(double v, Type t, int p) : value_(v), type_(t), precedence_(p) {}

  bool isUnaryLeftFunction() const;
  bool isOpeningBrace() const;
  bool isBinaryFunction() const;
  bool isUnaryRightFunction() const;
  bool isOperand() const;
  bool isClosingBrace() const;
};

}  // namespace Model

}  // namespace s21

#endif  //  SRC_MODEL_TOKEN_H