#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include <string>
#include <vector>

namespace s21 {

namespace Protocol {

struct DepositParameters;
struct DepositResult;
struct GraphParameters;
struct GraphResult;
struct CreditParameters;
struct CreditResult;

}  // namespace Protocol

/**
 * @brief Mediator between view and model.
 * Transfers data from view to model
 * Transfers data from model to view
 * Makes view independent on model
 */
class Controller {
 public:
 public:
  Controller(class Model *model);

  int Calculate(const std::string &input_str, double *result, double x_value);
  bool CalculateDeposit(const Protocol::DepositParameters &dp,
                        Protocol::DepositResult &dr);
  int CalculateGraph(const Protocol::GraphParameters &gp,
                     Protocol::GraphResult &gr);
  bool CalculateCredit(const Protocol::CreditParameters &cp,
                       Protocol::CreditResult &cr);

 private:
  Model *model_;
};

}  //  namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H