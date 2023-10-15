#include <gtest/gtest.h>

#include <iostream>
#include <optional>

#include "../model/model.h"

namespace {

TEST(Validator, T0Simple) {
  const std::string input_str("1+1");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T1Simple) {
  const std::string input_str("1+2");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T2Simple) {
  const std::string input_str("1+2*9-3+123-88/14");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T3Braces) {
  const std::string input_str("(1+2)*9-3+(123-88)/14");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T4Braces) {
  const std::string input_str("((1+2)*(9-3)+(123-88))/14");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T5Braces) {
  const std::string input_str("((1+2)*(9-3)+(123-88))/(14-66)");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T6BracesUnary) {
  const std::string input_str("((1+2)*(9-3)+(123-88))/(14-66)*(-9)");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T7BracesUnary) {
  const std::string input_str("-((1+2)*(9-3)+(123-88))/(14-66)*(-9)");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T8BracesUnary) {
  const std::string input_str("+((1+2)*(9-3)+(123-88))/(14-66)*(-9)*(+3)");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T9BracesUnary) {
  const std::string input_str("+((1+2)*(9-3)+(-1)*(123-88))/(14-66)*(-9)*(+3)");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T10BracesUnary) {
  const std::string input_str("+(-(-(+(-(1+2)*(9-3)+(-1)*(123-88))/(14-66)*(-9)*(+3))))");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}




TEST(Validator, T0SimpleBinaryFail) {
  const std::string input_str("5*");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T1SimpleBinaryFail) {
  const std::string input_str("5/");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T2SimpleBinaryFail) {
  const std::string input_str("/5");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T3SimpleBinaryFail) {
  const std::string input_str("*5");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T4SimpleBinaryFail) {
  const std::string input_str("5+72-");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T5SimpleBinaryFail) {
  const std::string input_str("*5+72");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T0MixedFail) {
  const std::string input_str("-*5");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T1MixedFail) {
  const std::string input_str("--+5");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T2MixedFail) {
  const std::string input_str("--+");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T3MixedFail) {
  const std::string input_str("--+(");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T0NoOperandFail) {
  const std::string input_str("()(())(5)");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T1NoOperandFail) {
  const std::string input_str("+");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T0BracesFail) {
  const std::string input_str("(6))");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T1BracesFail) {
  const std::string input_str("(+(-(-6))");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T2BracesFail) {
  const std::string input_str("(+(-(-6))))((");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T3BracesFail) {
  const std::string input_str("(12+6))8*3(");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

//(5)(+)

TEST(Validator, T4BracesFail) {
  const std::string input_str("(5)(+)");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T5BracesFail) {
  const std::string input_str("(5)(cos)");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T6BracesFail) {
  const std::string input_str("(5)()");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}


TEST(Validator, T0UnaryFail) {
  const std::string input_str("--+56");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T1UnaryFail) {
  const std::string input_str("3--+56");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = false;
  EXPECT_EQ(expected, actual);
}






TEST(Validator, T0Unary) {
  const std::string input_str("-(-5)");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T1Unary) {
  const std::string input_str("-(-5)");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T2Unary) {
  const std::string input_str("+5");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T3Unary) {
  const std::string input_str("-5");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T4Unary) {
  const std::string input_str("5-5");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

TEST(Validator, T5Unary) {
  const std::string input_str("(-5)");
  s21::Model model;
  
  const std::optional<std::vector<s21::Model::Token>> tokens = model.parcer(input_str);
  const bool actual = model.validate(tokens.value());
   

  const bool expected = true;
  EXPECT_EQ(expected, actual);
}

// --+5     false
// +5       true
// -5       true
// -(-(+5)) true

// 5-5      true
// )-5      true
// (-5)     true

} // namespace