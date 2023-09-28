#include <gtest/gtest.h>

#include "../model/model.h"

#define EPS 1e-7
#define EPS2 1e-2

// GCOVR_EXCL_START

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



TEST(ExpressionComputation, T1Pows)  {
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


// START_TEST(test_case_53) {
//   double credit_sum = 100000;
//   int credit_term = 6;
//   float credit_percent = 15;
//   int type = 1;
//   double monthlty_payment;
//   double overpayment;
//   double total_sum;
//   int ex_code;
//   ex_code = credit_calc_fn(credit_sum, credit_term, credit_percent, type,
//                            &monthlty_payment, &overpayment, &total_sum);
//   ck_assert_int_eq(ex_code, 0);
//   ck_assert_double_eq_tol(monthlty_payment, 17403.38, EPS2);
//   ck_assert_double_eq_tol(overpayment, 4420.29, EPS2);
//   ck_assert_double_eq_tol(total_sum, 104420.29, EPS2);
// }
// END_TEST

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



} // namespace

// GCOVR_EXCL_STOP