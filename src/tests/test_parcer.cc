#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <stack>

#include "../model/parcer/parcer.h"

// GCOVR_EXCL_START

namespace s21 {

namespace Model {

bool operator==(const Token& left, const Token& right) {
  return left.type_ == right.type_ && left.precedence_ == right.precedence_ &&
         std::abs(left.value_ - right.value_) < 1e-6;
}
bool operator!=(const Token& left, const Token& right) {
  return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const Token& object) {
  out << "Token(" << object.value_ << ", " << static_cast<int>(object.type_)
      << ", " << object.precedence_ << ')';
  return out;
}

bool operator==(std::stack<Token> left, std::stack<Token> right) {
  if (left.size() != right.size()) return false;

  while (!left.empty()) {
    if (left.top() != right.top()) return false;
    left.pop();
    right.pop();
  }

  return true;
}

std::ostream& operator<<(std::ostream& out, std::stack<Token> object) {
  out << "Stack: " << object.size() << '\n';

  while (!object.empty()) {
    out << object.top() << '\n';
    object.pop();
  }

  return out;
}

}  // namespace Model

}  // namespace s21

namespace {

TEST(Parcer, T0Simple) {
  const std::string input_str("1");
  std::vector<s21::Model::Token> expected;
  expected.emplace_back(1.0, s21::Model::Type::Number, 1);

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value()) {
    EXPECT_EQ(expected, actual.value());
  }
}

TEST(Parcer, T1Simple) {
  const std::string input_str("cos");
  std::vector<s21::Model::Token> expected;
  expected.emplace_back(0.0, s21::Model::Type::Cos, 8);

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value()) {
    EXPECT_EQ(expected, actual.value());
  }
}

TEST(Parcer, T2Simple) {
  const std::string input_str("sqrt");
  std::vector<s21::Model::Token> expected;
  expected.emplace_back(0.0, s21::Model::Type::Sqrt, 8);

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value()) {
    EXPECT_EQ(expected, actual.value());
  }
}

TEST(Parcer, T3Simple) {
  const std::string input_str("666.555");
  std::vector<s21::Model::Token> expected;
  expected.emplace_back(666.555, s21::Model::Type::Number, 1);

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value()) {
    EXPECT_EQ(expected, actual.value());
  }
}

TEST(Parcer, T4Simple) {
  const std::string input_str("cos666.555ln");
  std::vector<s21::Model::Token> expected;
  expected.emplace_back(0.0, s21::Model::Type::Cos, 8);
  expected.emplace_back(666.555, s21::Model::Type::Number, 1);
  expected.emplace_back(0.0, s21::Model::Type::Ln, 8);

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value()) {
    EXPECT_EQ(expected, actual.value());
  }
}

TEST(Parcer, T0Minus) {
  const std::string input_str("-666.555");  // -1 * 666.555 ^ 2
  std::vector<s21::Model::Token> expected;
  expected.emplace_back(0.0, s21::Model::Type::Minus, 6);
  expected.emplace_back(666.555, s21::Model::Type::Number, 1);

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value()) {
    EXPECT_EQ(expected, actual.value());
  }
}

TEST(Parcer, T1Minus) {
  const std::string input_str("(-666.555)");
  std::vector<s21::Model::Token> expected;
  expected.emplace_back(0.0, s21::Model::Type::OpenBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::Minus, 6);
  expected.emplace_back(666.555, s21::Model::Type::Number, 1);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value()) {
    EXPECT_EQ(expected, actual.value());
  }
}

TEST(Parcer, T2Minus) {
  const std::string input_str("(-666.555))))))");
  std::vector<s21::Model::Token> expected;
  expected.emplace_back(0.0, s21::Model::Type::OpenBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::Minus, 6);
  expected.emplace_back(666.555, s21::Model::Type::Number, 1);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value()) {
    EXPECT_EQ(expected, actual.value());
  }
}

TEST(Parcer, T3Minus) {
  const std::string input_str("(-666.555))))))*13");
  std::vector<s21::Model::Token> expected;
  expected.emplace_back(0.0, s21::Model::Type::OpenBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::Minus, 6);
  expected.emplace_back(666.555, s21::Model::Type::Number, 1);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::Mult, 8);
  expected.emplace_back(13.0, s21::Model::Type::Number, 1);

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value()) {
    EXPECT_EQ(expected, actual.value());
  }
}

TEST(Parcer, T0Exp) {
  const std::string input_str("(-666.555e-8))))))*13e3");
  std::vector<s21::Model::Token> expected;
  expected.emplace_back(0.0, s21::Model::Type::OpenBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::Minus, 6);
  expected.emplace_back(666.555e-8, s21::Model::Type::Number, 1);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::Mult, 8);
  expected.emplace_back(13.0e3, s21::Model::Type::Number, 1);

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value()) {
    EXPECT_EQ(expected, actual.value());
  }
}

TEST(Parcer, T0Long) {
  const std::string input_str("cos((-666.5sqrt(55))))*13+14/88-x");
  std::vector<s21::Model::Token> expected;
  expected.emplace_back(0.0, s21::Model::Type::Cos, 8);
  expected.emplace_back(0.0, s21::Model::Type::OpenBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::OpenBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::Minus, 6);
  expected.emplace_back(666.5, s21::Model::Type::Number, 1);
  expected.emplace_back(0.0, s21::Model::Type::Sqrt, 8);
  expected.emplace_back(0.0, s21::Model::Type::OpenBracket, 0);
  expected.emplace_back(55.0, s21::Model::Type::Number, 1);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::CloseBracket, 0);
  expected.emplace_back(0.0, s21::Model::Type::Mult, 8);
  expected.emplace_back(13.0, s21::Model::Type::Number, 1);
  expected.emplace_back(0.0, s21::Model::Type::Sum, 6);
  expected.emplace_back(14.0, s21::Model::Type::Number, 1);
  expected.emplace_back(0.0, s21::Model::Type::Div, 8);
  expected.emplace_back(88.0, s21::Model::Type::Number, 1);
  expected.emplace_back(0.0, s21::Model::Type::Minus, 6);
  expected.emplace_back(0.0, s21::Model::Type::X, 1);

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value()) {
    EXPECT_EQ(expected, actual.value());
  }
}

TEST(Parcer, T0IncorrectStringToParce) {
  const std::string input_str("cocksucker");
  std::vector<s21::Model::Token> expected;

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), false);
}

TEST(Parcer, T1IncorrectStringToParce) {
  const std::string input_str("cos(13.99*x)+cocksucker");
  std::vector<s21::Model::Token> expected;

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), false);
}
TEST(Parcer, T2IncorrectStringToParce) {
  const std::string input_str("cos((-666.5seqrt(55))))*13+14/88-x");
  std::vector<s21::Model::Token> expected;

  s21::Parcer parcer(input_str);
  const std::optional<std::vector<s21::Model::Token>> actual = parcer.Run();

  EXPECT_EQ(actual.has_value(), false);
}

}  // namespace

// GCOVR_EXCL_STOP