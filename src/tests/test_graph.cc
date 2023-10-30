#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <string>

#include "../model/model.h"
#include "../protocol/protocol.h"
#include "../model/graphCalculator.h"
#include "../model/parcer.h"
#include "../model/validator.h"
#include "../model/unaryReplacer.h"
#include "../model/shuntingYard.h"
#include "../model/flipStack.h"

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
  const std::string input_string = "x";
  s21::Parcer parcer(input_string);
  const auto parced = parcer.Run();
  EXPECT_TRUE(parced.has_value());
  if (!parced.has_value())
    return;
  
  s21::Validator validator(parced.value());
  const bool isValid = validator.Run();
  EXPECT_TRUE(isValid);
  if (!isValid)
    return;

  s21::UnaryReplacer unaryReplacer(parced.value());
  const auto replaced = unaryReplacer.Run();

  std::stack<s21::Model::Token> head;
  for (auto it = replaced.crbegin(); it != replaced.crend(); ++it)
    head.push(*it);

  s21::ShuntingYard shuntingYard(head);
  std::stack<s21::Model::Token> pn = shuntingYard.Run();

  s21::FlipStack flipStack(pn);
  std::stack<s21::Model::Token> rpn = flipStack.Run();

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

  s21::GraphCalculator graphCalculator(rpn, x_min, x_max, x_range);
  std::optional<s21::Protocol::GraphResult> actual = graphCalculator.Run();
  
  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value())
    return;
  EXPECT_EQ(expected, actual.value());
}

TEST(Graph, T1Simple) {
  const std::string input_string = "2*x";
  s21::Parcer parcer(input_string);
  const auto parced = parcer.Run();
  EXPECT_TRUE(parced.has_value());
  if (!parced.has_value())
    return;
  
  s21::Validator validator(parced.value());
  const bool isValid = validator.Run();
  EXPECT_TRUE(isValid);
  if (!isValid)
    return;

  s21::UnaryReplacer unaryReplacer(parced.value());
  const auto replaced = unaryReplacer.Run();

  std::stack<s21::Model::Token> head;
  for (auto it = replaced.crbegin(); it != replaced.crend(); ++it)
    head.push(*it);

  s21::ShuntingYard shuntingYard(head);
  std::stack<s21::Model::Token> pn = shuntingYard.Run();

  s21::FlipStack flipStack(pn);
  std::stack<s21::Model::Token> rpn = flipStack.Run();

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

  s21::GraphCalculator graphCalculator(rpn, x_min, x_max, x_range);
  std::optional<s21::Protocol::GraphResult> actual = graphCalculator.Run();
  
  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value())
    return;
  EXPECT_EQ(expected, actual.value());
}

TEST(Graph, T2Simple) {
  const std::string input_string = "2*x+1";
  s21::Parcer parcer(input_string);
  const auto parced = parcer.Run();
  EXPECT_TRUE(parced.has_value());
  if (!parced.has_value())
    return;
  
  s21::Validator validator(parced.value());
  const bool isValid = validator.Run();
  EXPECT_TRUE(isValid);
  if (!isValid)
    return;

  s21::UnaryReplacer unaryReplacer(parced.value());
  const auto replaced = unaryReplacer.Run();

  std::stack<s21::Model::Token> head;
  for (auto it = replaced.crbegin(); it != replaced.crend(); ++it)
    head.push(*it);

  s21::ShuntingYard shuntingYard(head);
  std::stack<s21::Model::Token> pn = shuntingYard.Run();

  s21::FlipStack flipStack(pn);
  std::stack<s21::Model::Token> rpn = flipStack.Run();

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

  s21::GraphCalculator graphCalculator(rpn, x_min, x_max, x_range);
  std::optional<s21::Protocol::GraphResult> actual = graphCalculator.Run();
  
  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value())
    return;
  EXPECT_EQ(expected, actual.value());
}

TEST(Graph, T3Simple) {
  const std::string input_string = "-x";
  s21::Parcer parcer(input_string);
  const auto parced = parcer.Run();
  EXPECT_TRUE(parced.has_value());
  if (!parced.has_value())
    return;
  
  s21::Validator validator(parced.value());
  const bool isValid = validator.Run();
  EXPECT_TRUE(isValid);
  if (!isValid)
    return;

  s21::UnaryReplacer unaryReplacer(parced.value());
  const auto replaced = unaryReplacer.Run();

  std::stack<s21::Model::Token> head;
  for (auto it = replaced.crbegin(); it != replaced.crend(); ++it)
    head.push(*it);

  s21::ShuntingYard shuntingYard(head);
  std::stack<s21::Model::Token> pn = shuntingYard.Run();

  s21::FlipStack flipStack(pn);
  std::stack<s21::Model::Token> rpn = flipStack.Run();

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

  s21::GraphCalculator graphCalculator(rpn, x_min, x_max, x_range);
  std::optional<s21::Protocol::GraphResult> actual = graphCalculator.Run();
  

  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value())
    return;
  EXPECT_EQ(expected, actual.value());
}

TEST(Graph, T0Complex) {
  const std::string input_string = "2*(x+1)*sin(4-x)*x";
  s21::Parcer parcer(input_string);
  const auto parced = parcer.Run();
  EXPECT_TRUE(parced.has_value());
  if (!parced.has_value())
    return;
  
  s21::Validator validator(parced.value());
  const bool isValid = validator.Run();
  EXPECT_TRUE(isValid);
  if (!isValid)
    return;

  s21::UnaryReplacer unaryReplacer(parced.value());
  const auto replaced = unaryReplacer.Run();

  std::stack<s21::Model::Token> head;
  for (auto it = replaced.crbegin(); it != replaced.crend(); ++it)
    head.push(*it);

  s21::ShuntingYard shuntingYard(head);
  std::stack<s21::Model::Token> pn = shuntingYard.Run();

  s21::FlipStack flipStack(pn);
  std::stack<s21::Model::Token> rpn = flipStack.Run();

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

  s21::GraphCalculator graphCalculator(rpn, x_min, x_max, x_range);
  std::optional<s21::Protocol::GraphResult> actual = graphCalculator.Run();
  
  EXPECT_TRUE(actual.has_value());
  if (!actual.has_value())
    return;
  EXPECT_EQ(expected, actual.value());
}

}  // namespace

// GCOVR_EXCL_STOP