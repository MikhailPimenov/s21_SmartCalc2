#include <gtest/gtest.h>

#include <iostream>

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
  const std::string input_str("-666.555");  // -1 * 666.555 ^ 2
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(-666.555, s21::Model::Type::Number, 1));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}

TEST(Parcer, T5Simple) {
  const std::string input_str("(-666.555)");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(0.0, s21::Model::Type::OpenBracket, 0));
  expected.push(s21::Model::Token(-666.555, s21::Model::Type::Number, 1));
  expected.push(s21::Model::Token(0.0, s21::Model::Type::CloseBracket, 0));
   
  s21::Model model;
  const std::optional<std::stack<s21::Model::Token>> actual = model.parcer(input_str);

  EXPECT_EQ(actual.has_value(), true);
  if (actual.has_value())
    EXPECT_EQ(expected, actual.value());
}

TEST(Parcer, T6Simple) {
  const std::string input_str("(-666.555))))))");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(0.0, s21::Model::Type::OpenBracket, 0));
  expected.push(s21::Model::Token(-666.555, s21::Model::Type::Number, 1));
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

TEST(Parcer, T7Simple) {
  const std::string input_str("(-666.555))))))*13");
  std::stack<s21::Model::Token> expected;
  expected.push(s21::Model::Token(0.0, s21::Model::Type::OpenBracket, 0));
  expected.push(s21::Model::Token(-666.555, s21::Model::Type::Number, 1));
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


} // namespace