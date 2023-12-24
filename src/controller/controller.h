#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include <string>
#include <vector>

#include "../model/calculator/calculator.h"
#include "../model/credit/creditCalculator.h"
#include "../model/deposit/depositCalculator.h"
#include "../model/graph/graphCalculator.h"

namespace s21 {

namespace Protocol {
struct GraphParameters;
struct GraphResult;
struct CreditParameters;
struct CreditResult;
}  // namespace Protocol

namespace Controller {

/**
 * @brief Mediator between view and model.
 * Transfers data from view to model
 * Transfers data from model to view
 * Makes view independent on model
 */

class Calculator {
 private:
  Model::Calculator model_;

 public:
  Calculator(const std::string& input, double x);
  std::optional<double> Run();
};

/**
 * @brief Plots a Graph
 * Plots a graph of a function
 * Drawing by dots to provide more accurate result
 */

class GraphCalculator {
 private:
  Model::GraphCalculator model_;

 public:
  GraphCalculator(const Protocol::GraphParameters& gp);
  std::optional<Protocol::GraphResult> Run();
};

/**
 * @brief Calculates a credit
 *
 * Shows calculated result of monthly payment,
 * overpayment on credit, total payment
 *
 */

class CreditCalculator {
 private:
  Model::CreditCalculator model_;

 public:
  CreditCalculator(const Protocol::CreditParameters& cp);
  bool Run();
  std::optional<Protocol::CreditResult> Get() const;
};

/**
 * @brief Provide a special mode
 *
 * Shows calculated result of accrued interest, tax amount,
 * deposit amount by the end of the term
 *
 */

class DepositCalculator {
 private:
  Model::DepositCalculator model_;

 public:
  DepositCalculator(const Protocol::DepositParameters& cp);
  bool Run();
  std::optional<Protocol::DepositResult> Get() const;
};

}  //  namespace Controller

}  //  namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H