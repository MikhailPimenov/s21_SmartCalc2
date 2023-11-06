#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

#include "../model/model.h"
#include "../protocol/protocol.h"
#include "../model/creditCalculator.h"

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

std::ostream &operator<<(std::ostream &out, const Protocol::CreditResult &cr) {
  out << "CreditResult:\n";
  out << cr.monthlyPayment_ << '\n';
  out << cr.overpayment_ << '\n';
  out << cr.totalSum_ << '\n';
  out << "Monthly payment by months:\n";
  for (double value : cr.monthlyPaymentList_) out << value << '\n';

  return out;
}

}  // namespace Protocol

}  // namespace s21

namespace {

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

  s21::Model::CreditCalculator creditCalculator(cp);
  creditCalculator.Run();
  const std::optional<s21::Protocol::CreditResult> actual = creditCalculator.Get();
  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value())
    return;

  EXPECT_EQ(expected, actual.value());
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

  s21::Model::CreditCalculator creditCalculator(cp);
  creditCalculator.Run();
  const std::optional<s21::Protocol::CreditResult> actual = creditCalculator.Get();
  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value())
    return;

  EXPECT_EQ(expected, actual.value());
}

TEST(Credit, T0CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = -700000.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Model::CreditCalculator creditCalculator(cp);
  const bool status = creditCalculator.Run();
  const std::optional<s21::Protocol::CreditResult> actual = creditCalculator.Get();
  EXPECT_FALSE(status);
  EXPECT_FALSE(actual.has_value());
}

TEST(Credit, T1CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 700000.0;
  cp.creditTerm_ = 60000;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Model::CreditCalculator creditCalculator(cp);
  const bool status = creditCalculator.Run();
  const std::optional<s21::Protocol::CreditResult> actual = creditCalculator.Get();
  EXPECT_FALSE(status);
  EXPECT_FALSE(actual.has_value());
}

TEST(Credit, T2CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 700000.0;
  cp.creditTerm_ = -60;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Model::CreditCalculator creditCalculator(cp);
  const bool status = creditCalculator.Run();
  const std::optional<s21::Protocol::CreditResult> actual = creditCalculator.Get();
  EXPECT_FALSE(status);
  EXPECT_FALSE(actual.has_value());
}

TEST(Credit, T3CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 700000.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = -10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Model::CreditCalculator creditCalculator(cp);
  const bool status = creditCalculator.Run();
  const std::optional<s21::Protocol::CreditResult> actual = creditCalculator.Get();
  EXPECT_FALSE(status);
  EXPECT_FALSE(actual.has_value());
}

TEST(Credit, T4CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 700000.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Undefined;

  s21::Model::CreditCalculator creditCalculator(cp);
  const bool status = creditCalculator.Run();
  const std::optional<s21::Protocol::CreditResult> actual = creditCalculator.Get();
  EXPECT_FALSE(status);
  EXPECT_FALSE(actual.has_value());
}

TEST(Credit, T5CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 100.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Model::CreditCalculator creditCalculator(cp);
  const bool status = creditCalculator.Run();
  const std::optional<s21::Protocol::CreditResult> actual = creditCalculator.Get();
  EXPECT_FALSE(status);
  EXPECT_FALSE(actual.has_value());
}

TEST(Credit, T6CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 20000000000.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = 10.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Model::CreditCalculator creditCalculator(cp);
  const bool status = creditCalculator.Run();
  const std::optional<s21::Protocol::CreditResult> actual = creditCalculator.Get();
  EXPECT_FALSE(status);
  EXPECT_FALSE(actual.has_value());
}

TEST(Credit, T7CreditIncorrectInput) {
  s21::Protocol::CreditParameters cp;
  cp.creditSum_ = 700000.0;
  cp.creditTerm_ = 60;
  cp.creditPercent_ = 999.0;
  cp.order_ = s21::Protocol::CreditParameters::RepainmentOrder::Annuity;

  s21::Model::CreditCalculator creditCalculator(cp);
  const bool status = creditCalculator.Run();
  const std::optional<s21::Protocol::CreditResult> actual = creditCalculator.Get();
  EXPECT_FALSE(status);
  EXPECT_FALSE(actual.has_value());
}

}  // namespace

// GCOVR_EXCL_STOP