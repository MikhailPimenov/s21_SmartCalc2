#include <gtest/gtest.h>

#include <iostream>
#include <optional>

#include "../model/model.h"


namespace s21 {

// bool operator==(const Model::Token& left, const Model::Token& right) {
//     return left.type == right.type && left.precedence == right.precedence && std::abs(left.value - right.value) < 1e-6;
// }
// bool operator!=(const Model::Token& left, const Model::Token& right) {
//     return !(left == right);
// }

// std::ostream& operator<<(std::ostream& out, const Model::Token& object) {
//   out << "Token(" << object.value << ", " << static_cast<int>(object.type) << ", " << object.precedence << ')';
//   return out;
// }


// bool operator==(std::stack<Model::Token> left, std::stack<Model::Token> right) {
//   if (left.size() != right.size())
//     return false;

//   while (!left.empty()) {
//     if (left.top() != right.top())
//       return false;
//     left.pop();
//     right.pop();
//   }

//   return true;
// }

// std::ostream& operator<<(std::ostream& out, std::stack<Model::Token> object) {
//   out << "Stack: " << object.size() << '\n';

//   while (!object.empty()) {
//     out << object.top() << '\n';
//     object.pop();
//   }

//   return out; 
// }

}  // namespace s21

namespace {



TEST(Validator, T0Simple) {
  const std::string input_str("1+1");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T1Simple) {
  const std::string input_str("1+2");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T2Simple) {
  const std::string input_str("1+2*9-3+123-88/14");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T3Braces) {
  const std::string input_str("(1+2)*9-3+(123-88)/14");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T4Braces) {
  const std::string input_str("((1+2)*(9-3)+(123-88))/14");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T5Braces) {
  const std::string input_str("((1+2)*(9-3)+(123-88))/(14-66)");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T6BracesUnary) {
  const std::string input_str("((1+2)*(9-3)+(123-88))/(14-66)*(-9)");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T7BracesUnary) {
  const std::string input_str("-((1+2)*(9-3)+(123-88))/(14-66)*(-9)");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T8BracesUnary) {
  const std::string input_str("+((1+2)*(9-3)+(123-88))/(14-66)*(-9)*(+3)");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T9BracesUnary) {
  const std::string input_str("+((1+2)*(9-3)+(-1)*(123-88))/(14-66)*(-9)*(+3)");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T10BracesUnary) {
  const std::string input_str("+(-(-(+(-(1+2)*(9-3)+(-1)*(123-88))/(14-66)*(-9)*(+3))))");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}




TEST(Validator, T0SimpleBinaryFail) {
  const std::string input_str("5*");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T1SimpleBinaryFail) {
  const std::string input_str("5/");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T2SimpleBinaryFail) {
  const std::string input_str("/5");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T3SimpleBinaryFail) {
  const std::string input_str("*5");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T4SimpleBinaryFail) {
  const std::string input_str("5+72-");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T5SimpleBinaryFail) {
  const std::string input_str("*5+72");
  s21::Model model;
  
  const std::optional<std::stack<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

} // namespace