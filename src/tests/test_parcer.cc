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

}