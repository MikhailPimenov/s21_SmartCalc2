#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

#include "../model/deposit/depositCalculator.h"
#include "../protocol/protocol.h"

#define EPS 1e-7
#define EPS2 1e-2

// GCOVR_EXCL_START

namespace s21 {

namespace Protocol {

static constexpr double tolerance = 1e-3;
static constexpr double tolerance2 = 1e-2;

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

}  // namespace Protocol

}  // namespace s21

namespace {

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

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_TRUE(success);
  if (!success) return;
  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value()) return;

  EXPECT_EQ(expected, actual.value());
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

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_TRUE(success);
  if (!success) return;
  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value()) return;

  EXPECT_EQ(expected, actual.value());
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

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_TRUE(success);
  if (!success) return;
  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value()) return;

  EXPECT_EQ(expected, actual.value());
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

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_TRUE(success);
  if (!success) return;
  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value()) return;

  EXPECT_EQ(expected, actual.value());
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

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_TRUE(success);
  if (!success) return;
  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value()) return;

  EXPECT_EQ(expected, actual.value());
}

TEST(Deposit, T0DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = -700000.0;
  dp.period_ = 12;
  dp.interest_ = 10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_FALSE(success);
  EXPECT_FALSE(actual.has_value());
}

TEST(Deposit, T1DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 699;
  dp.interest_ = 10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_FALSE(success);
  EXPECT_FALSE(actual.has_value());
}

TEST(Deposit, T2DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = -12;
  dp.interest_ = 10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_FALSE(success);
  EXPECT_FALSE(actual.has_value());
}

TEST(Deposit, T3DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = -10.0;
  dp.tax_ = 0.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_FALSE(success);
  EXPECT_FALSE(actual.has_value());
}

TEST(Deposit, T4DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = 100.0;
  dp.tax_ = 0.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_FALSE(success);
  EXPECT_FALSE(actual.has_value());
}

TEST(Deposit, T5DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = 10.0;
  dp.tax_ = -10.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_FALSE(success);
  EXPECT_FALSE(actual.has_value());
}

TEST(Deposit, T6DepositIncorrectInput) {
  s21::Protocol::DepositParameters dp;
  dp.amount_ = 700000.0;
  dp.period_ = 12;
  dp.interest_ = 10.0;
  dp.tax_ = 100.0;
  dp.capitalization_ = s21::Protocol::DepositParameters::Capitalization::Total;
  dp.frequency_ = s21::Protocol::DepositParameters::PaymentFrequency::Monthly;

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_FALSE(success);
  EXPECT_FALSE(actual.has_value());
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

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_FALSE(success);
  EXPECT_FALSE(actual.has_value());
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

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_FALSE(success);
  EXPECT_FALSE(actual.has_value());
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

  s21::Model::DepositCalculator depositCalculator(dp);
  const bool success = depositCalculator.Run();
  const std::optional<s21::Protocol::DepositResult> actual =
      depositCalculator.Get();
  EXPECT_FALSE(success);
  EXPECT_FALSE(actual.has_value());
}

}  // namespace

// GCOVR_EXCL_STOP