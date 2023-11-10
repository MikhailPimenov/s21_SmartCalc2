#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <optional>

#include "../model/calculator.h"
#include "../protocol/protocol.h"

#define EPS 1e-7
#define EPS2 1e-2

// GCOVR_EXCL_START

namespace {

TEST(ExpressionComputation, T0Simple) {
  const std::string input_str("1+2*3");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 7.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T1Simple) {
  const std::string input_str("2.0/(3.0+2.0)*5.0");
  

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 2.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T2SimpleBraces) {
  const std::string input_str("1+2+(3*4)+(5.1+6.8)");
  

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 26.9;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T3Simple) {
  const std::string input_str("10.0+10.0*10.0");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 110.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T4SimpleMod) {
  const std::string input_str("5.0mod3.0");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 2.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T5SimpleBraces) {
  const std::string input_str("1.0/2.0*(2.0-1.0)");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 0.5;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T6MoreBraces) {
  const std::string input_str("(1-2-(0-3)-4)-5-(0-6)");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = -1.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T7MoreBraces) {
  const std::string input_str("(1+2)*((3-4)+1+(5-6+7))");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 18.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T8MoreBraces) {
  const std::string input_str("sqrt(4)-1/2*sin(3^2-2)");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 1.6715067;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T1Pows) {
  const std::string input_str("2^3^2");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 512.0;

  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T4Simple) {
  const std::string input_str("-1+8");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 7.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T1Mod) {
  const std::string input_str("-5.0mod(-3.0)");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = -2.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T1LongEpression) {
  const std::string input_str("4+4*2/(1-5)");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 2.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T2LongEpression) {
  const std::string input_str("4+4*2/1-5");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 7.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T3LongEpression) {
  const std::string input_str("4+4*(2/1-5)");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = -8.0;

  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T4LongEpression) {
  const std::string input_str("4+(4*2/1-5)");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 7.0;

  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T5LongEpression) {
  const std::string input_str("4+4*(2/1)-5");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 7.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T6LongEpression) {
  const std::string input_str("4+(4*2/1)-5");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 7.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T7LongEpression) {
  const std::string input_str("(4+4*2/1)-5");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 7.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T8LongEpression) {
  const std::string input_str("4+(4*2)/1-5");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 7.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T9LongEpression) {
  const std::string input_str("(4+4*2)/1-5");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 7.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T10LongEpression) {
  const std::string input_str("8*(7+6*4)+3");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 251.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T11LongEpression) {
  const std::string input_str("2/(3+2)*5");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 2.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T12LongEpression) {
  const std::string input_str("2+9.3-8^3/4+56.2");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = -60.5;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T13LongEpression) {
  const std::string input_str("2+9.3-8^3/(4+56.2)");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 2.7950166;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T14LongEpression) {
  const std::string input_str("2^(3^2)");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 512.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T15LongEpression) {
  const std::string input_str("(2^3)^2");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 64.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T16LongEpression) {
  const std::string input_str("cos(431.2*2^2/8)");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = -0.3902501;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T17LongEpression) {
  const std::string input_str("3*sin(4+5)");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 1.2363555;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T18LongEpression) {
  const std::string input_str("431.2*2^2/8");
  

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 215.6;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T19LongEpression) {
  const std::string input_str("cos(sin(2+9*6^1.2-tan(1)))");

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 0.7421823;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}
TEST(ExpressionComputation, T20LongEpression) {
  const std::string input_str("sqrt(cos(sin(2+9*6^1.2-tan(1))))");

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 0.8615000;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}
TEST(ExpressionComputation, T21LongEpression) {
  const std::string input_str("sqrt(cos(sin(2+9*6^1.2-tan(1))))mod0.1");

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 0.0615000;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T22LongEpression) {
  const std::string input_str("sqrt(2^2)*5/(4-3mod2)*(4-sqrt(81))");

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = -16.6666667;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}
TEST(ExpressionComputation, T23LongEpression) {
  const std::string input_str("cos(1/3)*sin(1.352^9/(4+3))");

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 0.7876032;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T24LongEpression) {
  const std::string input_str("(cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150)");

  double x_value = 0.0;
    s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 0.0223863;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}
TEST(ExpressionComputation, T25LongEpression) {
  const std::string input_str("2+(-(-(-(-1))))");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 3.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}
TEST(ExpressionComputation, T26LongEpression) {
  const std::string input_str("cos(6*3)/5");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 0.1320633;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}
TEST(ExpressionComputation, T1EpressionError) {
  const std::string input_str("12.6.9+8");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  EXPECT_EQ(result.has_value(), false);
}

TEST(ExpressionComputation, T2EpressionError) {
  const std::string input_str("(12+6");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  EXPECT_EQ(result.has_value(), false);
}

TEST(ExpressionComputation, T3EpressionError) {
  const std::string input_str("(12+6))8*3(");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  EXPECT_EQ(result.has_value(), false);
}

TEST(ExpressionComputation, T4ExpressionCos) {
  const std::string input_str("acos1");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 0.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T5ExpressionAcos) {
  const std::string input_str("acos0.5");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 1.0471975;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T1ExpressionAtan) {
  const std::string input_str("atan1");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const int ex_expected = 0;
  const double expected = 0.7853981;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T2ExpressionAtan) {
  const std::string input_str("atan15");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 1.5042281;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T3ExpressionAsin) {
  const std::string input_str("asin1");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 1.5707963;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T4ExpressionAsin) {
  const std::string input_str("asin0.5");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 0.5235987;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T5ExpressionLen) {
  const std::string input_str("ln1");

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 0.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T6ExpressionLen) {
  const std::string input_str("ln15");
  

  double x_value = 0.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 2.7080502;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T7ExpressionPow) {
  const std::string input_str("x^2+x*2");

  double x_value = 3.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  const double expected = 15.0;
  EXPECT_EQ(result.has_value(), true);
  if (result.has_value())
    EXPECT_NEAR(result.value(), expected, EPS);
}

TEST(ExpressionComputation, T0IncorrectStringInput) {
  const std::string input_str("cos");

  double x_value = 3.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  EXPECT_EQ(result.has_value(), false);
}

TEST(ExpressionComputation, T1IncorrectStringInput) {
  const std::string input_str("1*cos");

  double x_value = 3.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  EXPECT_EQ(result.has_value(), false);
}

TEST(ExpressionComputation, T2IncorrectStringInput) {
  const std::string input_str("1*cos*3");
  

  double x_value = 3.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  EXPECT_EQ(result.has_value(), false);
}

TEST(ExpressionComputation, T3IncorrectStringInput) {
  const std::string input_str("1*cos*3-3"); // 1, *, cos, *, 3, -, 3
  

  double x_value = 3.0;
  s21::Model::SingleCalculator calculator(input_str, x_value);
  const std::optional<double> result = calculator.Run();
  EXPECT_EQ(result.has_value(), false);
}

}  // namespace

// GCOVR_EXCL_STOP