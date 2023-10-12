#include <gtest/gtest.h>

#include <iostream>
#include <optional>

#include "../model/model.h"


namespace s21 {

bool operator==(const Model::Token& left, const Model::Token& right) {
    return left.type == right.type && left.precedence == right.precedence && std::abs(left.value - right.value) < 1e-6;
}
bool operator!=(const Model::Token& left, const Model::Token& right) {
    return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const Model::Token& object) {
  out << "Token(" << object.value << ", " << static_cast<int>(object.type) << ", " << object.precedence << ')';
  return out;
}


bool operator==(std::stack<Model::Token> left, std::stack<Model::Token> right) {
  if (left.size() != right.size())
    return false;

  while (!left.empty()) {
    if (left.top() != right.top())
      return false;
    left.pop();
    right.pop();
  }

  return true;
}

std::ostream& operator<<(std::ostream& out, std::stack<Model::Token> object) {
  out << "Stack: " << object.size() << '\n';

  while (!object.empty()) {
    out << object.top() << '\n';
    object.pop();
  }

  return out; 
}

}  // namespace s21

namespace {



TEST(Parcer, T0Simple) {
  const std::string input_str("1");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(1.0, s21::Model::Type::Number, 1));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}


TEST(Parcer, T1Simple) {
  const std::string input_str("cos");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Cos, 8));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}


TEST(Parcer, T2Simple) {
  const std::string input_str("sqrt");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Sqrt, 8));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}

TEST(Parcer, T3Simple) {
  const std::string input_str("666.555");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(666.555, s21::Model::Type::Number, 1));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}

TEST(Parcer, T4Simple) {
  const std::string input_str("cos666.555ln");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Cos, 8));
  expected.push(s21::Model::Token(666.555, s21::Model::Type::Number, 1));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Ln, 8));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}

TEST(Parcer, T0Minus) {
  const std::string input_str("-666.555");  // -1 * 666.555 ^ 2
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Minus, 6));
  expected.push(s21::Model::Token(666.555, s21::Model::Type::Number, 1));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}

TEST(Parcer, T1Minus) {
  const std::string input_str("(-666.555)");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(0.0, s21::Model::Type::OpenBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Minus, 6));
  expected.push(s21::Model::Token(666.555, s21::Model::Type::Number, 1));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}

TEST(Parcer, T2Minus) {
  const std::string input_str("(-666.555))))))");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(0.0, s21::Model::Type::OpenBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Minus, 6));
  expected.push(s21::Model::Token(666.555, s21::Model::Type::Number, 1));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}

TEST(Parcer, T3Minus) {
  const std::string input_str("(-666.555))))))*13");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(0.0, s21::Model::Type::OpenBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Minus, 6));
  expected.push(s21::Model::Token(666.555, s21::Model::Type::Number, 1));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Mult, 8));
  expected.push(s21::Model::Token(13.0, s21::Model::Type::Number, 1));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}

TEST(Parcer, T0Long) {
  const std::string input_str("cos((-666.5sqrt(55))))*13+14/88-x");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Cos, 8));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::OpenBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::OpenBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Minus, 6));
  expected.push(s21::Model::Token(666.5, s21::Model::Type::Number, 1));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Sqrt, 8));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::OpenBracket, 0));
  expected.push(s21::Model::Token(55.0, s21::Model::Type::Number, 1));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Mult, 8));
  expected.push(s21::Model::Token(13.0, s21::Model::Type::Number, 1));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Sum, 6));
  expected.push(s21::Model::Token(14.0, s21::Model::Type::Number, 1));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Div, 8));
  expected.push(s21::Model::Token(88.0, s21::Model::Type::Number, 1));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::Minus, 6));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::X, 1));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}


TEST(Parcer, T1Long) {
  // valid string
  const std::string input_str("14.88+89(^44.666cossqrt-123.99)))))--+-0-0-)))xxx1x1x333xsinx)ln)logatanmodasin/tan");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(14.88,    s21::Model::Type::Number,       1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Sum,          6));
  expected.push(s21::Model::Token(89.0,     s21::Model::Type::Number,       1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::OpenBracket,  0));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Power,        9));
  expected.push(s21::Model::Token(44.666,   s21::Model::Type::Number,       1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Cos,          8));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Sqrt,         8));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Minus,        6));
  expected.push(s21::Model::Token(123.99,   s21::Model::Type::Number,       1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Minus,        6));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Minus,        6));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Sum,          6));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Minus,        6));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Number,       1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Minus,        6));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Number,       1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Minus,        6));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::X,            1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::X,            1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::X,            1));
  expected.push(s21::Model::Token(1.0,      s21::Model::Type::Number,       1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::X,            1));
  expected.push(s21::Model::Token(1.0,      s21::Model::Type::Number,       1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::X,            1));
  expected.push(s21::Model::Token(333.0,    s21::Model::Type::Number,       1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::X,            1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Sin,          8));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::X,            1));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Ln,           8));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::CloseBracket, 0));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Log,          8));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Atan,         8));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Mod,          8));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Asin,         8));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Div,          8));
  expected.push(s21::Model::Token(0.0,      s21::Model::Type::Tan,          8));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}








TEST(Parcer, T0IncorrectStringToParce) {
  const std::string input_str("cocksucker");
  std::stack<s21::Model::Token> expected;
  
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), false);
}

TEST(Parcer, T1IncorrectStringToParce) {
  const std::string input_str("cos(13.99*x)+cocksucker");
  std::stack<s21::Model::Token> expected;
  
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), false);
}
TEST(Parcer, T2IncorrectStringToParce) {
  const std::string input_str("cos((-666.5seqrt(55))))*13+14/88-x");
  std::stack<s21::Model::Token> expected;
  
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), false);
}

} // namespace