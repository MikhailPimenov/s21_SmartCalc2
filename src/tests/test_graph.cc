#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <string>

#include "../model/model.h"
#include "../protocol/protocol.h"
#include "../model/graphCalculator.h"
#include "../model/parcer.h"

#define EPS 1e-7
#define EPS2 1e-2

// GCOVR_EXCL_START

namespace s21 {

namespace Protocol {

static constexpr double tolerance = 1e-3;
static constexpr double tolerance2 = 1e-2;

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
  const std::string input_string = "x + 1";
  
  s21::Parcer parcer(input_string);
  const std::optional<std::vector<s21::Model::Token>> tokens = parcer.Run();


  s21::Protocol::GraphResult actual;
  // const int status = s21::Model::CalculateGraph(gp, actual);
  s21::GraphCalculator graphCalculator()
  const std::optional<s21::Protocol::GraphResult>

  EXPECT_EQ(status, 1);
}

}  // namespace

// GCOVR_EXCL_STOP