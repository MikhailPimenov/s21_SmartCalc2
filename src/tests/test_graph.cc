#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <string>

#include "../model/graph/graphCalculator.h"
#include "../model/parcer/parcer.h"
#include "../model/parcer/unaryReplacer.h"
#include "../model/parcer/validator.h"
#include "../model/rpn/flipStack.h"
#include "../model/rpn/shuntingYard.h"
#include "../protocol/protocol.h"

#define EPS 1e-7
#define EPS2 1e-2

// GCOVR_EXCL_START

namespace s21 {

namespace Protocol {

// static constexpr double tolerance = 1e-3;
// static constexpr double tolerance2 = 1e-2;

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

TEST(Graph, T0Simple) {
  const std::string input_string = "x";

  const double x_max = 30.0;
  const double x_min = -30.0;
  static constexpr int x_range = 10000;
  const double x_step = abs(x_max - x_min) / static_cast<double>(x_range);

  s21::Protocol::GraphResult expected;
  expected.x.resize(x_range);
  expected.y.resize(x_range);
  for (int i = 0; i < x_range; ++i) {
    expected.x[i] = x_min + x_step * static_cast<double>(i);
    expected.y[i] = expected.x[i];
  }

  s21::Model::GraphCalculator graphCalculator(input_string, x_min, x_max,
                                              x_range);
  std::optional<s21::Protocol::GraphResult> actual = graphCalculator.Run();

  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value()) return;
  EXPECT_EQ(expected, actual.value());
}

TEST(Graph, T1Simple) {
  const std::string input_string = "2*x";

  const double x_max = 30.0;
  const double x_min = -30.0;
  static constexpr int x_range = 10000;
  const double x_step = abs(x_max - x_min) / static_cast<double>(x_range);

  s21::Protocol::GraphResult expected;
  expected.x.resize(x_range);
  expected.y.resize(x_range);
  for (int i = 0; i < x_range; ++i) {
    expected.x[i] = x_min + x_step * static_cast<double>(i);
    expected.y[i] = 2.0 * expected.x[i];
  }

  s21::Model::GraphCalculator graphCalculator(input_string, x_min, x_max,
                                              x_range);
  std::optional<s21::Protocol::GraphResult> actual = graphCalculator.Run();

  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value()) return;
  EXPECT_EQ(expected, actual.value());
}

TEST(Graph, T2Simple) {
  const std::string input_string = "2*x+1";

  const double x_max = 30.0;
  const double x_min = -30.0;
  static constexpr int x_range = 10000;
  const double x_step = abs(x_max - x_min) / static_cast<double>(x_range);

  s21::Protocol::GraphResult expected;
  expected.x.resize(x_range);
  expected.y.resize(x_range);
  for (int i = 0; i < x_range; ++i) {
    expected.x[i] = x_min + x_step * static_cast<double>(i);
    expected.y[i] = 2.0 * expected.x[i] + 1.0;
  }

  s21::Model::GraphCalculator graphCalculator(input_string, x_min, x_max,
                                              x_range);
  std::optional<s21::Protocol::GraphResult> actual = graphCalculator.Run();

  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value()) return;
  EXPECT_EQ(expected, actual.value());
}

TEST(Graph, T3Simple) {
  const std::string input_string = "-x";

  const double x_max = 30.0;
  const double x_min = -30.0;
  static constexpr int x_range = 10000;
  const double x_step = abs(x_max - x_min) / static_cast<double>(x_range);

  s21::Protocol::GraphResult expected;
  expected.x.resize(x_range);
  expected.y.resize(x_range);
  for (int i = 0; i < x_range; ++i) {
    expected.x[i] = x_min + x_step * static_cast<double>(i);
    expected.y[i] = -1.0 * expected.x[i];
  }

  s21::Model::GraphCalculator graphCalculator(input_string, x_min, x_max,
                                              x_range);
  std::optional<s21::Protocol::GraphResult> actual = graphCalculator.Run();

  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value()) return;
  EXPECT_EQ(expected, actual.value());
}

TEST(Graph, T4Simple) {
  s21::Protocol::GraphParameters gp;
  gp.input_string = "-x";

  gp.x_max = 30.0;
  gp.x_min = -30.0;
  static constexpr int x_range = 10000;
  gp.steps = 10000;
  const double x_step = abs(gp.x_max - gp.x_min) / static_cast<double>(x_range);

  s21::Protocol::GraphResult expected;
  expected.x.resize(x_range);
  expected.y.resize(x_range);
  for (int i = 0; i < x_range; ++i) {
    expected.x[i] = gp.x_min + x_step * static_cast<double>(i);
    expected.y[i] = -1.0 * expected.x[i];
  }

  s21::Model::GraphCalculator graphCalculator(gp);
  std::optional<s21::Protocol::GraphResult> actual = graphCalculator.Run();

  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value()) return;
  EXPECT_EQ(expected, actual.value());
}

TEST(Graph, T0Complex) {
  const std::string input_string = "2*(x+1)*sin(4-x)*x";

  const double x_max = 30.0;
  const double x_min = -30.0;
  static constexpr int x_range = 10000;
  const double x_step = abs(x_max - x_min) / static_cast<double>(x_range);

  s21::Protocol::GraphResult expected;
  expected.x.resize(x_range);
  expected.y.resize(x_range);
  for (int i = 0; i < x_range; ++i) {
    expected.x[i] = x_min + x_step * static_cast<double>(i);
    expected.y[i] = 2.0 * (expected.x[i] + 1.0) *
                    std::sin(4.0 - expected.x[i]) * expected.x[i];
  }

  s21::Model::GraphCalculator graphCalculator(input_string, x_min, x_max,
                                              x_range);
  std::optional<s21::Protocol::GraphResult> actual = graphCalculator.Run();

  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value()) return;
  EXPECT_EQ(expected, actual.value());
}

}  // namespace

// GCOVR_EXCL_STOP