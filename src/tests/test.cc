#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

#include "../model/model.h"
#include "../protocol/protocol.h"

#define EPS 1e-7
#define EPS2 1e-2

// GCOVR_EXCL_START

namespace s21 {

namespace Protocol {

static constexpr double tolerance = 1e-3;
static constexpr double tolerance2 = 1e-2;

bool operator==(const Protocol::CreditResult &left,
                const Protocol::CreditResult &right) {
  if (std::abs(left.overpayment_ - right.overpayment_) >
      tolerance * std::abs(left.overpayment_))
    return false;
  if (std::abs(left.totalSum_ - right.totalSum_) >
      tolerance * std::abs(left.totalSum_))
    return false;

  if (std::abs(left.monthlyPayment_ - right.monthlyPayment_) >
      tolerance * std::abs(left.monthlyPayment_))
    return false;

  if (left.monthlyPaymentList_.size() != right.monthlyPaymentList_.size())
    return false;

  auto left_it = left.monthlyPaymentList_.begin();
  auto right_it = right.monthlyPaymentList_.begin();

  while (left_it != left.monthlyPaymentList_.end() &&
         right_it != right.monthlyPaymentList_.end()) {
    if (std::abs(*left_it - *right_it) > tolerance * std::abs(*left_it))
      return false;

    ++left_it;
    ++right_it;
  }

  return true;
}

bool operator!=(const Protocol::CreditResult &left,
                const Protocol::CreditResult &right) {
  return !(left == right);
}

bool isFebruary(int index) {
  static constexpr int months = 12;
  return index % months == 1;
}

bool operator==(const Protocol::DepositResult &left,
                const Protocol::DepositResult &right) {
  if (std::abs(left.accruedTotal_ - right.accruedTotal_) >
      tolerance * std::abs(left.accruedTotal_))
    return false;
  if (std::abs(left.taxTotal_ - right.taxTotal_) >
      tolerance * std::abs(left.taxTotal_))
    return false;

  if (std::abs(left.amountTotal_ - right.amountTotal_) >
      tolerance * std::abs(left.amountTotal_))
    return false;

  if (left.accruedMonthly_.size() != right.accruedMonthly_.size()) return false;

  auto left_it1 = left.accruedMonthly_.begin();
  auto right_it1 = right.accruedMonthly_.begin();

  int month = 0;
  while (left_it1 != left.accruedMonthly_.end() &&
         right_it1 != right.accruedMonthly_.end()) {
    if (std::abs(*left_it1 - *right_it1) >
        (isFebruary(month) ? 0.1 * std::abs(*left_it1)
                           : tolerance * std::abs(*left_it1)))
      return false;

    ++left_it1;
    ++right_it1;

    ++month;
  }

  auto left_it2 = left.percentMonthly_.begin();
  auto right_it2 = right.percentMonthly_.begin();

  month = 0;
  while (left_it2 != left.percentMonthly_.end() &&
         right_it2 != right.percentMonthly_.end()) {
    if (std::abs(*left_it2 - *right_it2) >
        (isFebruary(month) ? 0.1 * std::abs(*left_it2)
                           : tolerance2 * std::abs(*left_it2)))
      return false;

    ++left_it2;
    ++right_it2;

    ++month;
  }

  return true;
}

bool operator!=(const Protocol::DepositResult &left,
                const Protocol::DepositResult &right) {
  return !(left == right);
}

std::ostream &operator<<(std::ostream &out, const Protocol::CreditResult &cr) {
  out << "CreditResult:\n";
  out << cr.monthlyPayment_ << '\n';
  out << cr.overpayment_ << '\n';
  out << cr.totalSum_ << '\n';
  out << "Monthly payment by months:\n";
  for (double value : cr.monthlyPaymentList_) out << value << '\n';

  return out;
}

std::ostream &operator<<(std::ostream &out, const Protocol::DepositResult &dr) {
  out << "DepositResult:\n";
  out << dr.accruedTotal_ << '\n';
  out << dr.taxTotal_ << '\n';
  out << dr.amountTotal_ << '\n';
  out << "Percent increase by months:\n";
  for (double value : dr.percentMonthly_) out << value << '\n';
  out << "Total sum by months:\n";
  for (double value : dr.accruedMonthly_) out << value << '\n';

  return out;
}

bool operator==(const std::vector<double> &left,
                const std::vector<double> &right) {
  if (left.size() != right.size()) return false;

  auto it_left = left.begin();
  auto it_right = right.begin();

  while (it_left != left.end() && it_right != right.end()) {
    if (std::abs(*it_left - *it_right) > 1e-6) return false;

    ++it_left;
    ++it_right;
  }
  return true;
}

bool operator==(const Protocol::GraphResult &left,
                const Protocol::GraphResult &right) {
  return left.x == right.x && left.y == right.y;
}

}  // namespace Protocol

}  // namespace s21

namespace {

TEST(ExpressionComputation, T0Simple) {
  const std::string input_str("1+2*3");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  const int ex_code = model.Calculate(input_str, &result, x_value);
  const double expected = 7.0;
  const int ex_expected = 0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T1Simple) {
  const std::string input_str("2.0/(3.0+2.0)*5.0");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  const int ex_code = model.Calculate(input_str, &result, x_value);
  const double expected = 2.0;
  const int ex_expected = 0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T2SimpleBraces) {
  const std::string input_str("1+2+(3*4)+(5.1+6.8)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  const int ex_code = model.Calculate(input_str, &result, x_value);
  const double expected = 26.9;
  const int ex_expected = 0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T3Simple) {
  const std::string input_str("10.0+10.0*10.0");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  const int ex_code = model.Calculate(input_str, &result, x_value);
  const double expected = 110.0;
  const int ex_expected = 0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T4SimpleMod) {
  const std::string input_str("5.0mod3.0");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  const int ex_code = model.Calculate(input_str, &result, x_value);
  const double expected = 2.0;
  const int ex_expected = 0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T5SimpleBraces) {
  const std::string input_str("1.0/2.0*(2.0-1.0)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  const int ex_code = model.Calculate(input_str, &result, x_value);
  const double expected = 0.5;
  const int ex_expected = 0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T6MoreBraces) {
  const std::string input_str("(1-2-(0-3)-4)-5-(0-6)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  const int ex_code = model.Calculate(input_str, &result, x_value);
  const double expected = -1.0;
  const int ex_expected = 0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T7MoreBraces) {
  const std::string input_str("(1+2)*((3-4)+1+(5-6+7))");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  const int ex_code = model.Calculate(input_str, &result, x_value);
  const double expected = 18.0;
  const int ex_expected = 0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T8MoreBraces) {
  const std::string input_str("sqrt(4)-1/2*sin(3^2-2)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 1.6715067;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T1Pows) {
  const std::string input_str("2^3^2");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 512.0;

  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

// // DON'T!!!!!!!!!!!!!!!!!!!!!
// // DON'T!!!!!!!!!!!!!!!!!!!!!
// // DON'T!!!!!!!!!!!!!!!!!!!!!
// // START_TEST(test_case_11) {
// //   char *input_str = "sin(+3)";
// //   double result = 0;
// //   double x_value = 0;
// //   int ex_code;
// //   ex_code = main_for_calc(input_str, &result, x_value);
// //   ck_assert_int_eq(ex_code, 0);
// //   ck_assert_double_eq_tol(result, 0.1411200, EPS);
// // }
// // END_TEST

TEST(ExpressionComputation, T4Simple) {
  const std::string input_str("-1+8");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 7.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T1Mod) {
  const std::string input_str("-5.0mod(-3.0)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = -2.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T1LongEpression) {
  const std::string input_str("4+4*2/(1-5)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 2.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T2LongEpression) {
  const std::string input_str("4+4*2/1-5");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 7.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T3LongEpression) {
  const std::string input_str("4+4*(2/1-5)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = -8.0;

  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T4LongEpression) {
  const std::string input_str("4+(4*2/1-5)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 7.0;

  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T5LongEpression) {
  const std::string input_str("4+4*(2/1)-5");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 7.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T6LongEpression) {
  const std::string input_str("4+(4*2/1)-5");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 7.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T7LongEpression) {
  const std::string input_str("(4+4*2/1)-5");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 7.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T8LongEpression) {
  const std::string input_str("4+(4*2)/1-5");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 7.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T9LongEpression) {
  const std::string input_str("(4+4*2)/1-5");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 7.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T10LongEpression) {
  const std::string input_str("8*(7+6*4)+3");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 251.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T11LongEpression) {
  const std::string input_str("2/(3+2)*5");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 2.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T12LongEpression) {
  const std::string input_str("2+9.3-8^3/4+56.2");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = -60.5;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T13LongEpression) {
  const std::string input_str("2+9.3-8^3/(4+56.2)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 2.7950166;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T14LongEpression) {
  const std::string input_str("2^(3^2)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 512.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T15LongEpression) {
  const std::string input_str("(2^3)^2");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 64.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T16LongEpression) {
  const std::string input_str("cos(431.2*2^2/8)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = -0.3902501;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T17LongEpression) {
  const std::string input_str("3*sin(4+5)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 1.2363555;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T18LongEpression) {
  const std::string input_str("431.2*2^2/8");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 215.6;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T19LongEpression) {
  const std::string input_str("cos(sin(2+9*6^1.2-tan(1)))");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 0.7421823;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}
TEST(ExpressionComputation, T20LongEpression) {
  const std::string input_str("sqrt(cos(sin(2+9*6^1.2-tan(1))))");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 0.8615000;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}
TEST(ExpressionComputation, T21LongEpression) {
  const std::string input_str("sqrt(cos(sin(2+9*6^1.2-tan(1))))mod0.1");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 0.0615000;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T22LongEpression) {
  const std::string input_str("sqrt(2^2)*5/(4-3mod2)*(4-sqrt(81))");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = -16.6666667;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}
TEST(ExpressionComputation, T23LongEpression) {
  const std::string input_str("cos(1/3)*sin(1.352^9/(4+3))");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 0.7876032;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T24LongEpression) {
  const std::string input_str("(cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150)");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 0.0223863;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}
TEST(ExpressionComputation, T25LongEpression) {
  const std::string input_str("2+(-(-(-(-1))))");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 3.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}
TEST(ExpressionComputation, T26LongEpression) {
  const std::string input_str("cos(6*3)/5");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 0.1320633;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}
TEST(ExpressionComputation, T1EpressionError) {
  const std::string input_str("12.6.9+8");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 1;
  EXPECT_EQ(ex_code, ex_expected);
}

TEST(ExpressionComputation, T2EpressionError) {
  const std::string input_str("(12+6");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 1;
  EXPECT_EQ(ex_code, ex_expected);
}

TEST(ExpressionComputation, T3EpressionError) {
  const std::string input_str("(12+6))8*3(");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 1;
  EXPECT_EQ(ex_code, ex_expected);
}

TEST(ExpressionComputation, T4ExpressionCos) {
  const std::string input_str("acos1");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 0.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T5ExpressionAcos) {
  const std::string input_str("acos0.5");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 1.0471975;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T1ExpressionAtan) {
  const std::string input_str("atan1");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 0.7853981;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T2ExpressionAtan) {
  const std::string input_str("atan15");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 1.5042281;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T3ExpressionAsin) {
  const std::string input_str("asin1");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 1.5707963;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T4ExpressionAsin) {
  const std::string input_str("asin0.5");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 0.5235987;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T5ExpressionLen) {
  const std::string input_str("ln1");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 0.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T6ExpressionLen) {
  const std::string input_str("ln15");
  s21::Model model;

  double result = 0.0;
  double x_value = 0.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 2.7080502;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T7ExpressionPow) {
  const std::string input_str("x^2+x*2");
  s21::Model model;

  double result = 0.0;
  double x_value = 3.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 0;
  const double expected = 15.0;
  EXPECT_EQ(ex_code, ex_expected);
  EXPECT_NEAR(result, expected, EPS);
}

TEST(ExpressionComputation, T0IncorrectStringInput) {
  const std::string input_str("cos");
  s21::Model model;

  double result = 0.0;
  double x_value = 3.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 1;
  EXPECT_EQ(ex_code, ex_expected);
}

TEST(ExpressionComputation, T1IncorrectStringInput) {
  const std::string input_str("1*cos");
  s21::Model model;

  double result = 0.0;
  double x_value = 3.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 1;
  EXPECT_EQ(ex_code, ex_expected);
}

TEST(ExpressionComputation, T2IncorrectStringInput) {
  const std::string input_str("1*cos*3");
  s21::Model model;

  double result = 0.0;
  double x_value = 3.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 1;
  EXPECT_EQ(ex_code, ex_expected);
}

TEST(ExpressionComputation, T3IncorrectStringInput) {
  const std::string input_str("1*cos*3-3"); // 1, *, cos, *, 3, -, 3
  s21::Model model;

  double result = 0.0;
  double x_value = 3.0;
  int ex_code = model.Calculate(input_str, &result, x_value);
  const int ex_expected = 1;
  EXPECT_EQ(ex_code, ex_expected);
}










TEST(Credit, T0CreditSimpleAnnuity) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 700000.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Protocol::CreditResult expected;
  expected.monthlyPaymentList_.reserve(cp.creditTerm_);
  for (int i = 0; i < cp.creditTerm_; ++i)
    expected.monthlyPaymentList_.push_back(14872.93);

  expected.overpayment_ = 192375.80;
  expected.totalSum_ = cp.creditSum_ + expected.overpayment_;

  expected.monthlyPayment_ = 14872.93;

  s21::Protocol::CreditResult actual;
  s21::Model::CalculateCredit(cp, actual);

  EXPECT_EQ(expected, actual);
}

TEST(Credit, T0CreditSimpleDifferentiated) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 700000.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Differentiated;

  s21::Protocol::CreditResult expected;
  expected.monthlyPaymentList_.resize(cp.creditTerm_);

  expected.monthlyPaymentList_.at(1 - 1) = 17500.00;
  expected.monthlyPaymentList_.at(2 - 1) = 17402.78;
  expected.monthlyPaymentList_.at(3 - 1) = 17305.56;
  expected.monthlyPaymentList_.at(4 - 1) = 17208.33;
  expected.monthlyPaymentList_.at(5 - 1) = 17111.11;
  expected.monthlyPaymentList_.at(6 - 1) = 17013.89;
  expected.monthlyPaymentList_.at(7 - 1) = 16916.67;
  expected.monthlyPaymentList_.at(8 - 1) = 16819.44;
  expected.monthlyPaymentList_.at(9 - 1) = 16722.22;
  expected.monthlyPaymentList_.at(10 - 1) = 16625.00;
  expected.monthlyPaymentList_.at(11 - 1) = 16527.78;
  expected.monthlyPaymentList_.at(12 - 1) = 16430.56;
  expected.monthlyPaymentList_.at(13 - 1) = 16333.33;
  expected.monthlyPaymentList_.at(14 - 1) = 16236.11;
  expected.monthlyPaymentList_.at(15 - 1) = 16138.89;
  expected.monthlyPaymentList_.at(16 - 1) = 16041.67;
  expected.monthlyPaymentList_.at(17 - 1) = 15944.44;
  expected.monthlyPaymentList_.at(18 - 1) = 15847.22;
  expected.monthlyPaymentList_.at(19 - 1) = 15750.00;
  expected.monthlyPaymentList_.at(20 - 1) = 15652.78;
  expected.monthlyPaymentList_.at(21 - 1) = 15555.56;
  expected.monthlyPaymentList_.at(22 - 1) = 15458.33;
  expected.monthlyPaymentList_.at(23 - 1) = 15361.11;
  expected.monthlyPaymentList_.at(24 - 1) = 15263.89;
  expected.monthlyPaymentList_.at(25 - 1) = 15166.67;
  expected.monthlyPaymentList_.at(26 - 1) = 15069.44;
  expected.monthlyPaymentList_.at(27 - 1) = 14972.22;
  expected.monthlyPaymentList_.at(28 - 1) = 14875.00;
  expected.monthlyPaymentList_.at(29 - 1) = 14777.78;
  expected.monthlyPaymentList_.at(30 - 1) = 14680.56;
  expected.monthlyPaymentList_.at(31 - 1) = 14583.33;
  expected.monthlyPaymentList_.at(32 - 1) = 14486.11;
  expected.monthlyPaymentList_.at(33 - 1) = 14388.89;
  expected.monthlyPaymentList_.at(34 - 1) = 14291.67;
  expected.monthlyPaymentList_.at(35 - 1) = 14194.44;
  expected.monthlyPaymentList_.at(36 - 1) = 14097.22;
  expected.monthlyPaymentList_.at(37 - 1) = 14000.00;
  expected.monthlyPaymentList_.at(38 - 1) = 13902.78;
  expected.monthlyPaymentList_.at(39 - 1) = 13805.56;
  expected.monthlyPaymentList_.at(40 - 1) = 13708.33;
  expected.monthlyPaymentList_.at(41 - 1) = 13611.11;
  expected.monthlyPaymentList_.at(42 - 1) = 13513.89;
  expected.monthlyPaymentList_.at(43 - 1) = 13416.67;
  expected.monthlyPaymentList_.at(44 - 1) = 13319.44;
  expected.monthlyPaymentList_.at(45 - 1) = 13222.22;
  expected.monthlyPaymentList_.at(46 - 1) = 13125.00;
  expected.monthlyPaymentList_.at(47 - 1) = 13027.78;
  expected.monthlyPaymentList_.at(48 - 1) = 12930.56;
  expected.monthlyPaymentList_.at(49 - 1) = 12833.33;
  expected.monthlyPaymentList_.at(50 - 1) = 12736.11;
  expected.monthlyPaymentList_.at(51 - 1) = 12638.89;
  expected.monthlyPaymentList_.at(52 - 1) = 12541.67;
  expected.monthlyPaymentList_.at(53 - 1) = 12444.44;
  expected.monthlyPaymentList_.at(54 - 1) = 12347.22;
  expected.monthlyPaymentList_.at(55 - 1) = 12250.00;
  expected.monthlyPaymentList_.at(56 - 1) = 12152.78;
  expected.monthlyPaymentList_.at(57 - 1) = 12055.56;
  expected.monthlyPaymentList_.at(58 - 1) = 11958.33;
  expected.monthlyPaymentList_.at(59 - 1) = 11861.11;
  expected.monthlyPaymentList_.at(60 - 1) = 11763.89;

  expected.overpayment_ = 177916.67;
  expected.totalSum_ = cp.creditSum_ + expected.overpayment_;

  expected.monthlyPayment_ = expected.monthlyPaymentList_.at(0);

  s21::Protocol::CreditResult actual;
  s21::Model::CalculateCredit(cp, actual);

  EXPECT_EQ(expected, actual);
}

TEST(Credit, T0CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = -700000.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Protocol::CreditResult actual;
  const bool status = s21::Model::CalculateCredit(cp, actual);

  EXPECT_EQ(status, false);
}

TEST(Credit, T1CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 700000.0;
  cp.creditTerm_ = 60000;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Protocol::CreditResult actual;
  const bool status = s21::Model::CalculateCredit(cp, actual);

  EXPECT_EQ(status, false);
}

TEST(Credit, T2CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 700000.0;
  cp.creditTerm_ = -60;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Protocol::CreditResult actual;
  const bool status = s21::Model::CalculateCredit(cp, actual);

  EXPECT_EQ(status, false);
}

TEST(Credit, T3CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 700000.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = -10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Protocol::CreditResult actual;
  const bool status = s21::Model::CalculateCredit(cp, actual);

  EXPECT_EQ(status, false);
}

TEST(Credit, T4CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 700000.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Undefined;

  s21::Protocol::CreditResult actual;
  const bool status = s21::Model::CalculateCredit(cp, actual);

  EXPECT_EQ(status, false);
}

TEST(Credit, T5CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 100.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Protocol::CreditResult actual;
  const bool status = s21::Model::CalculateCredit(cp, actual);

  EXPECT_EQ(status, false);
}

TEST(Credit, T6CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 20000000000.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Protocol::CreditResult actual;
  const bool status = s21::Model::CalculateCredit(cp, actual);

  EXPECT_EQ(status, false);
}

TEST(Credit, T7CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 700000.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = 999.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Protocol::CreditResult actual;
  const bool status = s21::Model::CalculateCredit(cp, actual);

  EXPECT_EQ(status, false);
}

TEST(Deposit, T0DepositCapitalization) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 60;
  dp.interest_ = 12.0;
  dp.tax_ = 0.0;
  dp.capitalization_ =
      s21::Protocol::DepositParameters::Capitalization::Monthly;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Total;

  s21::Protocol::DepositResult expected;
  expected.taxTotal_ = 0.0;
  expected.accruedTotal_ = 571685.0;
  expected.amountTotal_ = dp.amount_ + expected.accruedTotal_;

  expected.percentMonthly_.resize(dp.period_);
  expected.accruedMonthly_.resize(dp.period_);

  expected.percentMonthly_.at(0) = 7115;
  expected.accruedMonthly_.at(0) = 707115;
  expected.percentMonthly_.at(1) = 6723;
  expected.accruedMonthly_.at(1) = 713838;
  expected.percentMonthly_.at(2) = 7255;
  expected.accruedMonthly_.at(2) = 721094;
  expected.percentMonthly_.at(3) = 7093;
  expected.accruedMonthly_.at(3) = 728186;
  expected.percentMonthly_.at(4) = 7401;
  expected.accruedMonthly_.at(4) = 735588;
  expected.percentMonthly_.at(5) = 7235;
  expected.accruedMonthly_.at(5) = 742823;
  expected.percentMonthly_.at(6) = 7550;
  expected.accruedMonthly_.at(6) = 750373;
  expected.percentMonthly_.at(7) = 7627;
  expected.accruedMonthly_.at(7) = 758000;
  expected.percentMonthly_.at(8) = 7456;
  expected.accruedMonthly_.at(8) = 765455;
  expected.percentMonthly_.at(9) = 7780;
  expected.accruedMonthly_.at(9) = 773235;
  expected.percentMonthly_.at(10) = 7606;
  expected.accruedMonthly_.at(10) = 780841;
  expected.percentMonthly_.at(11) = 7936;
  expected.accruedMonthly_.at(11) = 788777;
  expected.percentMonthly_.at(12) = 8039;
  expected.accruedMonthly_.at(12) = 796816;
  expected.percentMonthly_.at(13) = 7335;
  expected.accruedMonthly_.at(13) = 804151;
  expected.percentMonthly_.at(14) = 8196;
  expected.accruedMonthly_.at(14) = 812347;
  expected.percentMonthly_.at(15) = 8012;
  expected.accruedMonthly_.at(15) = 820359;
  expected.percentMonthly_.at(16) = 8361;
  expected.accruedMonthly_.at(16) = 828720;
  expected.percentMonthly_.at(17) = 8174;
  expected.accruedMonthly_.at(17) = 836894;
  expected.percentMonthly_.at(18) = 8529;
  expected.accruedMonthly_.at(18) = 845423;
  expected.percentMonthly_.at(19) = 8616;
  expected.accruedMonthly_.at(19) = 854040;
  expected.percentMonthly_.at(20) = 8423;
  expected.accruedMonthly_.at(20) = 862463;
  expected.percentMonthly_.at(21) = 8790;
  expected.accruedMonthly_.at(21) = 871253;
  expected.percentMonthly_.at(22) = 8593;
  expected.accruedMonthly_.at(22) = 879846;
  expected.percentMonthly_.at(23) = 8967;
  expected.accruedMonthly_.at(23) = 888814;
  expected.percentMonthly_.at(24) = 9059;
  expected.accruedMonthly_.at(24) = 897872;
  expected.percentMonthly_.at(25) = 8265;
  expected.accruedMonthly_.at(25) = 906138;
  expected.percentMonthly_.at(26) = 9235;
  expected.accruedMonthly_.at(26) = 915373;
  expected.percentMonthly_.at(27) = 9028;
  expected.accruedMonthly_.at(27) = 924401;
  expected.percentMonthly_.at(28) = 9421;
  expected.accruedMonthly_.at(28) = 933822;
  expected.percentMonthly_.at(29) = 9210;
  expected.accruedMonthly_.at(29) = 943033;
  expected.percentMonthly_.at(30) = 9611;
  expected.accruedMonthly_.at(30) = 952644;
  expected.percentMonthly_.at(31) = 9709;
  expected.accruedMonthly_.at(31) = 962353;
  expected.percentMonthly_.at(32) = 9492;
  expected.accruedMonthly_.at(32) = 971845;
  expected.percentMonthly_.at(33) = 9905;
  expected.accruedMonthly_.at(33) = 981749;
  expected.percentMonthly_.at(34) = 9683;
  expected.accruedMonthly_.at(34) = 991432;
  expected.percentMonthly_.at(35) = 10104;
  expected.accruedMonthly_.at(35) = 1001537;
  expected.percentMonthly_.at(36) = 10207;
  expected.accruedMonthly_.at(36) = 1011744;
  expected.percentMonthly_.at(37) = 9314;
  expected.accruedMonthly_.at(37) = 1021058;
  expected.percentMonthly_.at(38) = 10406;
  expected.accruedMonthly_.at(38) = 1031464;
  expected.percentMonthly_.at(39) = 10173;
  expected.accruedMonthly_.at(39) = 1041638;
  expected.percentMonthly_.at(40) = 10616;
  expected.accruedMonthly_.at(40) = 1052254;
  expected.percentMonthly_.at(41) = 10378;
  expected.accruedMonthly_.at(41) = 1062632;
  expected.percentMonthly_.at(42) = 10830;
  expected.accruedMonthly_.at(42) = 1073462;
  expected.percentMonthly_.at(43) = 10940;
  expected.accruedMonthly_.at(43) = 1084403;
  expected.percentMonthly_.at(44) = 10695;
  expected.accruedMonthly_.at(44) = 1095098;
  expected.percentMonthly_.at(45) = 11161;
  expected.accruedMonthly_.at(45) = 1106259;
  expected.percentMonthly_.at(46) = 10911;
  expected.accruedMonthly_.at(46) = 1117170;
  expected.percentMonthly_.at(47) = 11386;
  expected.accruedMonthly_.at(47) = 1128556;
  expected.percentMonthly_.at(48) = 11471;
  expected.accruedMonthly_.at(48) = 1140027;
  expected.percentMonthly_.at(49) = 10840;
  expected.accruedMonthly_.at(49) = 1150867;
  expected.percentMonthly_.at(50) = 11697;
  expected.accruedMonthly_.at(50) = 1162564;
  expected.percentMonthly_.at(51) = 11435;
  expected.accruedMonthly_.at(51) = 1173999;
  expected.percentMonthly_.at(52) = 11932;
  expected.accruedMonthly_.at(52) = 1185931;
  expected.percentMonthly_.at(53) = 11665;
  expected.accruedMonthly_.at(53) = 1197596;
  expected.percentMonthly_.at(54) = 12172;
  expected.accruedMonthly_.at(54) = 1209769;
  expected.percentMonthly_.at(55) = 12296;
  expected.accruedMonthly_.at(55) = 1222065;
  expected.percentMonthly_.at(56) = 12020;
  expected.accruedMonthly_.at(56) = 1234085;
  expected.percentMonthly_.at(57) = 12543;
  expected.accruedMonthly_.at(57) = 1246628;
  expected.percentMonthly_.at(58) = 12262;
  expected.accruedMonthly_.at(58) = 1258890;
  expected.percentMonthly_.at(59) = 12795;
  expected.accruedMonthly_.at(59) = 1271685;

  s21::Protocol::DepositResult actual;
  s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(expected, actual);
}

TEST(Deposit, T0Deposit) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = 10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Protocol::DepositResult expected;
  expected.taxTotal_ = 0.0;
  expected.accruedTotal_ = 70000.0;
  expected.amountTotal_ = 770000.0;

  expected.percentMonthly_.resize(dp.period_);
  expected.accruedMonthly_.resize(dp.period_);

  expected.percentMonthly_.at(0) = 5929.0;
  expected.percentMonthly_.at(1) = 5546.0;
  expected.percentMonthly_.at(2) = 5929.0;
  expected.percentMonthly_.at(3) = 5738.0;
  expected.percentMonthly_.at(4) = 5929.0;
  expected.percentMonthly_.at(5) = 5738.0;
  expected.percentMonthly_.at(6) = 5929.0;
  expected.percentMonthly_.at(7) = 5929.0;
  expected.percentMonthly_.at(8) = 5738.0;
  expected.percentMonthly_.at(9) = 5929.0;
  expected.percentMonthly_.at(10) = 5738.0;
  expected.percentMonthly_.at(11) = 5929.0;

  expected.accruedMonthly_.at(0) = 700000.0;
  expected.accruedMonthly_.at(1) = 700000.0;
  expected.accruedMonthly_.at(2) = 700000.0;
  expected.accruedMonthly_.at(3) = 700000.0;
  expected.accruedMonthly_.at(4) = 700000.0;
  expected.accruedMonthly_.at(5) = 700000.0;
  expected.accruedMonthly_.at(6) = 700000.0;
  expected.accruedMonthly_.at(7) = 700000.0;
  expected.accruedMonthly_.at(8) = 700000.0;
  expected.accruedMonthly_.at(9) = 700000.0;
  expected.accruedMonthly_.at(10) = 700000.0;
  expected.accruedMonthly_.at(11) = 700000.0;

  s21::Protocol::DepositResult actual;
  s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(expected, actual);
}

TEST(Deposit, T1Deposit) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = 10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Total;

  s21::Protocol::DepositResult expected;
  expected.taxTotal_ = 0.0;
  expected.accruedTotal_ = 70000.0;
  expected.amountTotal_ = 770000.0;

  expected.percentMonthly_.resize(dp.period_);
  expected.accruedMonthly_.resize(dp.period_);

  expected.percentMonthly_.at(0) = 5929.0;
  expected.percentMonthly_.at(1) = 5546.0;
  expected.percentMonthly_.at(2) = 5929.0;
  expected.percentMonthly_.at(3) = 5738.0;
  expected.percentMonthly_.at(4) = 5929.0;
  expected.percentMonthly_.at(5) = 5738.0;
  expected.percentMonthly_.at(6) = 5929.0;
  expected.percentMonthly_.at(7) = 5929.0;
  expected.percentMonthly_.at(8) = 5738.0;
  expected.percentMonthly_.at(9) = 5929.0;
  expected.percentMonthly_.at(10) = 5738.0;
  expected.percentMonthly_.at(11) = 5929.0;

  expected.accruedMonthly_.at(0) = 700000.0;
  expected.accruedMonthly_.at(1) = 700000.0;
  expected.accruedMonthly_.at(2) = 700000.0;
  expected.accruedMonthly_.at(3) = 700000.0;
  expected.accruedMonthly_.at(4) = 700000.0;
  expected.accruedMonthly_.at(5) = 700000.0;
  expected.accruedMonthly_.at(6) = 700000.0;
  expected.accruedMonthly_.at(7) = 700000.0;
  expected.accruedMonthly_.at(8) = 700000.0;
  expected.accruedMonthly_.at(9) = 700000.0;
  expected.accruedMonthly_.at(10) = 700000.0;
  expected.accruedMonthly_.at(11) = 700000.0;

  s21::Protocol::DepositResult actual;
  s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(expected, actual);
}

TEST(Deposit, T2Deposit) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = 10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ =
      s21::Protocol::DepositParameters::Capitalization::Monthly;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Protocol::DepositResult expected;
  expected.taxTotal_ = 0.0;
  expected.accruedTotal_ = 70000.0;
  expected.amountTotal_ = 770000.0;

  expected.percentMonthly_.resize(dp.period_);
  expected.accruedMonthly_.resize(dp.period_);

  expected.percentMonthly_.at(0) = 5929.0;
  expected.percentMonthly_.at(1) = 5546.0;
  expected.percentMonthly_.at(2) = 5929.0;
  expected.percentMonthly_.at(3) = 5738.0;
  expected.percentMonthly_.at(4) = 5929.0;
  expected.percentMonthly_.at(5) = 5738.0;
  expected.percentMonthly_.at(6) = 5929.0;
  expected.percentMonthly_.at(7) = 5929.0;
  expected.percentMonthly_.at(8) = 5738.0;
  expected.percentMonthly_.at(9) = 5929.0;
  expected.percentMonthly_.at(10) = 5738.0;
  expected.percentMonthly_.at(11) = 5929.0;

  expected.accruedMonthly_.at(0) = 700000.0;
  expected.accruedMonthly_.at(1) = 700000.0;
  expected.accruedMonthly_.at(2) = 700000.0;
  expected.accruedMonthly_.at(3) = 700000.0;
  expected.accruedMonthly_.at(4) = 700000.0;
  expected.accruedMonthly_.at(5) = 700000.0;
  expected.accruedMonthly_.at(6) = 700000.0;
  expected.accruedMonthly_.at(7) = 700000.0;
  expected.accruedMonthly_.at(8) = 700000.0;
  expected.accruedMonthly_.at(9) = 700000.0;
  expected.accruedMonthly_.at(10) = 700000.0;
  expected.accruedMonthly_.at(11) = 700000.0;

  s21::Protocol::DepositResult actual;
  s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(expected, actual);
}

TEST(Deposit, T0DepositCapitalizationAddition) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 60;
  dp.interest_ = 12.0;
  dp.tax_ = 0.0;
  dp.capitalization_ =
      s21::Protocol::DepositParameters::Capitalization::Monthly;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Total;
  dp.depositOrWithdrawal_.resize(dp.period_);
  for (double &value : dp.depositOrWithdrawal_) value = 10000.0;
  dp.depositOrWithdrawal_.at(dp.period_ - 1) = 0.0;

  s21::Protocol::DepositResult expected;
  expected.taxTotal_ = 0.0;
  expected.accruedTotal_ = 788533.0;
  expected.amountTotal_ = 590000.0 + expected.accruedTotal_ + dp.amount_;

  expected.percentMonthly_.resize(dp.period_);
  expected.accruedMonthly_.resize(dp.period_);

  expected.percentMonthly_.at(0) = 7115;
  expected.accruedMonthly_.at(0) = 717115;
  expected.percentMonthly_.at(1) = 6818;
  expected.accruedMonthly_.at(1) = 733933;
  expected.percentMonthly_.at(2) = 7460;
  expected.accruedMonthly_.at(2) = 751393;
  expected.percentMonthly_.at(3) = 7391;
  expected.accruedMonthly_.at(3) = 768784;
  expected.percentMonthly_.at(4) = 7814;
  expected.accruedMonthly_.at(4) = 786597;
  expected.percentMonthly_.at(5) = 7737;
  expected.accruedMonthly_.at(5) = 804335;
  expected.percentMonthly_.at(6) = 8175;
  expected.accruedMonthly_.at(6) = 822510;
  expected.percentMonthly_.at(7) = 8360;
  expected.accruedMonthly_.at(7) = 840870;
  expected.percentMonthly_.at(8) = 8271;
  expected.accruedMonthly_.at(8) = 859140;
  expected.percentMonthly_.at(9) = 8732;
  expected.accruedMonthly_.at(9) = 877873;
  expected.percentMonthly_.at(10) = 8635;
  expected.accruedMonthly_.at(10) = 896508;
  expected.percentMonthly_.at(11) = 9112;
  expected.accruedMonthly_.at(11) = 915620;
  expected.percentMonthly_.at(12) = 9332;
  expected.accruedMonthly_.at(12) = 934951;
  expected.percentMonthly_.at(13) = 8607;
  expected.accruedMonthly_.at(13) = 953558;
  expected.percentMonthly_.at(14) = 9718;
  expected.accruedMonthly_.at(14) = 973277;
  expected.percentMonthly_.at(15) = 9599;
  expected.accruedMonthly_.at(15) = 992876;
  expected.percentMonthly_.at(16) = 10119;
  expected.accruedMonthly_.at(16) = 1012995;
  expected.percentMonthly_.at(17) = 9991;
  expected.accruedMonthly_.at(17) = 1032986;
  expected.percentMonthly_.at(18) = 10528;
  expected.accruedMonthly_.at(18) = 1053514;
  expected.percentMonthly_.at(19) = 10737;
  expected.accruedMonthly_.at(19) = 1074251;
  expected.percentMonthly_.at(20) = 10595;
  expected.accruedMonthly_.at(20) = 1094847;
  expected.percentMonthly_.at(21) = 11158;
  expected.accruedMonthly_.at(21) = 1116005;
  expected.percentMonthly_.at(22) = 11007;
  expected.accruedMonthly_.at(22) = 1137012;
  expected.percentMonthly_.at(23) = 11588;
  expected.accruedMonthly_.at(23) = 1158601;
  expected.percentMonthly_.at(24) = 11808;
  expected.accruedMonthly_.at(24) = 1180409;
  expected.percentMonthly_.at(25) = 10866;
  expected.accruedMonthly_.at(25) = 1201275;
  expected.percentMonthly_.at(26) = 12243;
  expected.accruedMonthly_.at(26) = 1223518;
  expected.percentMonthly_.at(27) = 12068;
  expected.accruedMonthly_.at(27) = 1245586;
  expected.percentMonthly_.at(28) = 12695;
  expected.accruedMonthly_.at(28) = 1268281;
  expected.percentMonthly_.at(29) = 12509;
  expected.accruedMonthly_.at(29) = 1290790;
  expected.percentMonthly_.at(30) = 13155;
  expected.accruedMonthly_.at(30) = 1313945;
  expected.percentMonthly_.at(31) = 13391;
  expected.accruedMonthly_.at(31) = 1337336;
  expected.percentMonthly_.at(32) = 13190;
  expected.accruedMonthly_.at(32) = 1360527;
  expected.percentMonthly_.at(33) = 13866;
  expected.accruedMonthly_.at(33) = 1384393;
  expected.percentMonthly_.at(34) = 13654;
  expected.accruedMonthly_.at(34) = 1408047;
  expected.percentMonthly_.at(35) = 14351;
  expected.accruedMonthly_.at(35) = 1432398;
  expected.percentMonthly_.at(36) = 14599;
  expected.accruedMonthly_.at(36) = 1456996;
  expected.percentMonthly_.at(37) = 13412;
  expected.accruedMonthly_.at(37) = 1480409;
  expected.percentMonthly_.at(38) = 15088;
  expected.accruedMonthly_.at(38) = 1505497;
  expected.percentMonthly_.at(39) = 14849;
  expected.accruedMonthly_.at(39) = 1530345;
  expected.percentMonthly_.at(40) = 15597;
  expected.accruedMonthly_.at(40) = 1555942;
  expected.percentMonthly_.at(41) = 15346;
  expected.accruedMonthly_.at(41) = 1581289;
  expected.percentMonthly_.at(42) = 16116;
  expected.accruedMonthly_.at(42) = 1607405;
  expected.percentMonthly_.at(43) = 16382;
  expected.accruedMonthly_.at(43) = 1633787;
  expected.percentMonthly_.at(44) = 16114;
  expected.accruedMonthly_.at(44) = 1659901;
  expected.percentMonthly_.at(45) = 16917;
  expected.accruedMonthly_.at(45) = 1686818;
  expected.percentMonthly_.at(46) = 16637;
  expected.accruedMonthly_.at(46) = 1713456;
  expected.percentMonthly_.at(47) = 17463;
  expected.accruedMonthly_.at(47) = 1740919;
  expected.percentMonthly_.at(48) = 17695;
  expected.accruedMonthly_.at(48) = 1768613;
  expected.percentMonthly_.at(49) = 16816;
  expected.accruedMonthly_.at(49) = 1795430;
  expected.percentMonthly_.at(50) = 18249;
  expected.accruedMonthly_.at(50) = 1823678;
  expected.percentMonthly_.at(51) = 17938;
  expected.accruedMonthly_.at(51) = 1851616;
  expected.percentMonthly_.at(52) = 18820;
  expected.accruedMonthly_.at(52) = 1880436;
  expected.percentMonthly_.at(53) = 18496;
  expected.accruedMonthly_.at(53) = 1908932;
  expected.percentMonthly_.at(54) = 19402;
  expected.accruedMonthly_.at(54) = 1938334;
  expected.percentMonthly_.at(55) = 19701;
  expected.accruedMonthly_.at(55) = 1968035;
  expected.percentMonthly_.at(56) = 19358;
  expected.accruedMonthly_.at(56) = 1997393;
  expected.percentMonthly_.at(57) = 20301;
  expected.accruedMonthly_.at(57) = 2027694;
  expected.percentMonthly_.at(58) = 19945;
  expected.accruedMonthly_.at(58) = 2057639;
  expected.percentMonthly_.at(59) = 20914;
  expected.accruedMonthly_.at(59) = 2078553;

  s21::Protocol::DepositResult actual;
  s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(expected, actual);
}

TEST(Deposit, T0DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = -700000.0;
  dp.period_ = 12;
  dp.interest_ = 10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Protocol::DepositResult actual;
  const bool status = s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(status, false);
}

TEST(Deposit, T1DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 699;
  dp.interest_ = 10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Protocol::DepositResult actual;
  const bool status = s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(status, false);
}

TEST(Deposit, T2DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = -12;
  dp.interest_ = 10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Protocol::DepositResult actual;
  const bool status = s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(status, false);
}

TEST(Deposit, T3DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = -10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Protocol::DepositResult actual;
  const bool status = s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(status, false);
}

TEST(Deposit, T4DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = 100.0;
  dp.tax_ = 0.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Protocol::DepositResult actual;
  const bool status = s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(status, false);
}

TEST(Deposit, T5DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = 10.0;
  dp.tax_ = -10.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Protocol::DepositResult actual;
  const bool status = s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(status, false);
}

TEST(Deposit, T6DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = 10.0;
  dp.tax_ = 100.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Protocol::DepositResult actual;
  const bool status = s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(status, false);
}

TEST(Deposit, T7DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = 10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ =
      s21::Protocol::DepositParameters::Capitalization::Undefined;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Protocol::DepositResult actual;
  const bool status = s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(status, false);
}

TEST(Deposit, T8DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = 10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ =
      s21::Protocol::DepositParameters::Capitalization::Monthly;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Undefined;

  s21::Protocol::DepositResult actual;
  const bool status = s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(status, false);
}

TEST(Deposit, T9DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 60;
  dp.interest_ = 12.0;
  dp.tax_ = 0.0;
  dp.capitalization_ =
      s21::Protocol::DepositParameters::Capitalization::Monthly;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Total;
  dp.depositOrWithdrawal_.resize(dp.period_);
  dp.depositOrWithdrawal_.at(dp.period_ - 1) = -99999999999.9;

  s21::Protocol::DepositResult actual;
  const bool status = s21::Model::CalculateDeposit(dp, actual);

  EXPECT_EQ(status, false);
}

TEST(Graph, T0Simple) {
  s21::Protocol::GraphParameters gp;
  gp.x_min = -30.0;
  gp.x_max = 30.0;
  gp.input_string = "x";
  s21::Protocol::GraphResult expected;

  static constexpr double x_range = 10000.0;
  double x_step = abs(gp.x_max - gp.x_min) / x_range;
  int ex_code = 0;

  expected.x.resize(x_range);
  expected.y.resize(x_range);
  for (int i = 0; i < x_range && ex_code == 0; ++i) {
    expected.x[i] = gp.x_min + x_step * i;
    expected.y[i] = expected.x[i];
  }

  s21::Protocol::GraphResult actual;
  const int status = s21::Model::CalculateGraph(gp, actual);
  EXPECT_EQ(status, 0);
  EXPECT_EQ(expected, actual);
}

TEST(Graph, T1Simple) {
  s21::Protocol::GraphParameters gp;
  gp.x_min = -30.0;
  gp.x_max = 30.0;
  gp.input_string = "2*x";
  s21::Protocol::GraphResult expected;

  static constexpr double x_range = 10000.0;
  double x_step = abs(gp.x_max - gp.x_min) / x_range;
  int ex_code = 0;

  expected.x.resize(x_range);
  expected.y.resize(x_range);
  for (int i = 0; i < x_range && ex_code == 0; ++i) {
    expected.x[i] = gp.x_min + x_step * i;
    expected.y[i] = 2.0 * expected.x[i];
  }

  s21::Protocol::GraphResult actual;
  const int status = s21::Model::CalculateGraph(gp, actual);
  EXPECT_EQ(status, 0);
  EXPECT_EQ(expected, actual);
}

TEST(Graph, T2Simple) {
  s21::Protocol::GraphParameters gp;
  gp.x_min = -30.0;
  gp.x_max = 30.0;
  gp.input_string = "2*x+1";
  s21::Protocol::GraphResult expected;

  static constexpr double x_range = 10000.0;
  double x_step = abs(gp.x_max - gp.x_min) / x_range;
  int ex_code = 0;

  expected.x.resize(x_range);
  expected.y.resize(x_range);
  for (int i = 0; i < x_range && ex_code == 0; ++i) {
    expected.x[i] = gp.x_min + x_step * i;
    expected.y[i] = 2.0 * expected.x[i] + 1.0;
  }

  s21::Protocol::GraphResult actual;
  const int status = s21::Model::CalculateGraph(gp, actual);
  EXPECT_EQ(status, 0);
  EXPECT_EQ(expected, actual);
}

TEST(Graph, T3Simple) {
  s21::Protocol::GraphParameters gp;
  gp.x_min = -30.0;
  gp.x_max = 30.0;
  gp.input_string = "-x";
  s21::Protocol::GraphResult expected;

  static constexpr double x_range = 10000.0;
  double x_step = abs(gp.x_max - gp.x_min) / x_range;
  int ex_code = 0;

  expected.x.resize(x_range);
  expected.y.resize(x_range);
  for (int i = 0; i < x_range && ex_code == 0; ++i) {
    expected.x[i] = gp.x_min + x_step * i;
    expected.y[i] = -1.0 * expected.x[i];
  }

  s21::Protocol::GraphResult actual;
  const int status = s21::Model::CalculateGraph(gp, actual);
  EXPECT_EQ(status, 0);
  EXPECT_EQ(expected, actual);
}

TEST(Graph, T0Complex) {
  s21::Protocol::GraphParameters gp;
  gp.x_min = -30.0;
  gp.x_max = 30.0;
  gp.input_string = "2*(x+1)*sin(4-x)*x";
  s21::Protocol::GraphResult expected;

  static constexpr double x_range = 10000.0;
  double x_step = abs(gp.x_max - gp.x_min) / x_range;
  int ex_code = 0;

  expected.x.resize(x_range);
  expected.y.resize(x_range);
  for (int i = 0; i < x_range && ex_code == 0; ++i) {
    expected.x[i] = gp.x_min + x_step * i;
    expected.y[i] = 2.0 * (expected.x[i] + 1.0) *
                    std::sin(4.0 - expected.x[i]) * expected.x[i];
  }

  s21::Protocol::GraphResult actual;
  const int status = s21::Model::CalculateGraph(gp, actual);
  EXPECT_EQ(status, 0);
  EXPECT_EQ(expected, actual);
}

TEST(Graph, T0IncorrectInput) {
  s21::Protocol::GraphParameters gp;
  gp.x_min = -30.0;
  gp.x_max = 30.0;
  gp.input_string = "2*(x+1(*sin(4-x)*x";

  s21::Protocol::GraphResult actual;
  const int status = s21::Model::CalculateGraph(gp, actual);
  EXPECT_EQ(status, 1);
}

TEST(Graph, T1IncorrectInput) {
  s21::Protocol::GraphParameters gp;
  gp.x_min = -30.0;
  gp.x_max = 30.0;
  gp.input_string = "2*(x+1()(((*sin(4-x)*x";

  s21::Protocol::GraphResult actual;
  const int status = s21::Model::CalculateGraph(gp, actual);
  EXPECT_EQ(status, 1);
}

TEST(Graph, T2IncorrectInput) {
  s21::Protocol::GraphParameters gp;
  gp.x_min = -30.0;
  gp.x_max = 30.0;
  gp.input_string = "hello";

  s21::Protocol::GraphResult actual;
  const int status = s21::Model::CalculateGraph(gp, actual);
  EXPECT_EQ(status, 1);
}

TEST(Graph, T3IncorrectInput) {
  s21::Protocol::GraphParameters gp;
  gp.x_min = -30.0;
  gp.x_max = 30.0;
  gp.input_string = "x + 1";

  s21::Protocol::GraphResult actual;
  const int status = s21::Model::CalculateGraph(gp, actual);
  EXPECT_EQ(status, 1);
}

// START_TEST(test_case_54) {
//   double credit_sum = 100000;
//   int credit_term = 6;
//   float credit_percent = 15;
//   int type = 2;
//   double monthlty_payment;
//   double overpayment;
//   double total_sum;
//   int ex_code;
//   ex_code = credit_calc_fn(credit_sum, credit_term, credit_percent, type,
//                            &monthlty_payment, &overpayment, &total_sum);
//   ck_assert_int_eq(ex_code, 0);
//   ck_assert_double_eq_tol(monthlty_payment, 17916.67, EPS2);
//   ck_assert_double_eq_tol(overpayment, 4375.00, EPS2);
//   ck_assert_double_eq_tol(total_sum, 104375.00, EPS2);
// }
// END_TEST

// START_TEST(test_case_55) {
//   double deposit_sum = 100000;
//   int deposit_term = 6;
//   float deposit_percent = 7;
//   float tax_percent = 0;
//   int type_cap = 1;
//   int type_pay = 1;
//   double add_sum[6] = {5000, 0, 0, 0, 0, 0};
//   double interest_income;
//   double total_deposit_sum;
//   double tax_sum;
//   int ex_code;
//   ex_code = deposit_calc_fn(deposit_sum, deposit_term, deposit_percent,
//                             tax_percent, type_cap, type_pay, add_sum,
//                             &interest_income, &total_deposit_sum, &tax_sum);
//   ck_assert_int_eq(ex_code, 0);
//   ck_assert_double_eq_tol(interest_income, 3675.00, EPS2);
//   ck_assert_double_eq_tol(total_deposit_sum, 108675.00, EPS2);
//   ck_assert_double_eq_tol(tax_sum, 0, EPS2);
// }
// END_TEST

// START_TEST(test_case_56) {
//   double deposit_sum = 100000;
//   int deposit_term = 6;
//   float deposit_percent = 7;
//   float tax_percent = 0;
//   int type_cap = 2;
//   int type_pay = 1;
//   double add_sum[6] = {5000, 0, 0, 0, 0, 0};
//   double interest_income;
//   double total_deposit_sum;
//   double tax_sum;
//   int ex_code;
//   ex_code = deposit_calc_fn(deposit_sum, deposit_term, deposit_percent,
//                             tax_percent, type_cap, type_pay, add_sum,
//                             &interest_income, &total_deposit_sum, &tax_sum);
//   ck_assert_int_eq(ex_code, 0);
//   ck_assert_double_eq_tol(interest_income, 3675.00, EPS2);
//   ck_assert_double_eq_tol(total_deposit_sum, 108675.00, EPS2);
//   ck_assert_double_eq_tol(tax_sum, 0, EPS2);
// }
// END_TEST

// START_TEST(test_case_57) {
//   double deposit_sum = 100000;
//   int deposit_term = 6;
//   float deposit_percent = 7;
//   float tax_percent = 0;
//   int type_cap = 1;
//   int type_pay = 2;
//   double add_sum[6] = {5000, 0, 0, 0, 0, 0};
//   double interest_income;
//   double total_deposit_sum;
//   double tax_sum;
//   int ex_code;
//   ex_code = deposit_calc_fn(deposit_sum, deposit_term, deposit_percent,
//                             tax_percent, type_cap, type_pay, add_sum,
//                             &interest_income, &total_deposit_sum, &tax_sum);
//   ck_assert_int_eq(ex_code, 0);
//   ck_assert_double_eq_tol(interest_income, 3729.01, EPS2);
//   ck_assert_double_eq_tol(total_deposit_sum, 108729.01, EPS2);
//   ck_assert_double_eq_tol(tax_sum, 0, EPS2);
// }
// END_TEST

// START_TEST(test_case_58) {
//   double deposit_sum = 100000;
//   int deposit_term = 6;
//   float deposit_percent = 7;
//   float tax_percent = 0;
//   int type_cap = 1;
//   int type_pay = 1;
//   double add_sum[6] = {5000, 0, 0, -1000000, 0, 0};
//   double interest_income;
//   double total_deposit_sum;
//   double tax_sum;
//   int ex_code;
//   ex_code = deposit_calc_fn(deposit_sum, deposit_term, deposit_percent,
//                             tax_percent, type_cap, type_pay, add_sum,
//                             &interest_income, &total_deposit_sum, &tax_sum);
//   ck_assert_int_eq(ex_code, 1);
// }
// END_TEST

// START_TEST(test_case_59) {
//   double deposit_sum = 100000;
//   int deposit_term = 6;
//   float deposit_percent = 7;
//   float tax_percent = 0;
//   int type_cap = 2;
//   int type_pay = 1;
//   double add_sum[6] = {5000, 0, -150000, 0, 0, 0};
//   double interest_income;
//   double total_deposit_sum;
//   double tax_sum;
//   int ex_code;
//   ex_code = deposit_calc_fn(deposit_sum, deposit_term, deposit_percent,
//                             tax_percent, type_cap, type_pay, add_sum,
//                             &interest_income, &total_deposit_sum, &tax_sum);
//   ck_assert_int_eq(ex_code, 1);
// }
// END_TEST

// START_TEST(test_case_60) {
//   double deposit_sum = 100000;
//   int deposit_term = 6;
//   float deposit_percent = 7;
//   float tax_percent = 0;
//   int type_cap = 1;
//   int type_pay = 2;
//   double add_sum[6] = {5000, -150000, 0, 0, 0, 0};
//   double interest_income;
//   double total_deposit_sum;
//   double tax_sum;
//   int ex_code;
//   ex_code = deposit_calc_fn(deposit_sum, deposit_term, deposit_percent,
//                             tax_percent, type_cap, type_pay, add_sum,
//                             &interest_income, &total_deposit_sum, &tax_sum);
//   ck_assert_int_eq(ex_code, 1);
// }
// END_TEST

}  // namespace

// GCOVR_EXCL_STOP