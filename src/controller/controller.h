#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include <string>
#include <vector>

#include "../model/calculator.h"
#include "../model/graphCalculator.h"
#include "../model/creditCalculator.h"
#include "../model/depositCalculator.h"

namespace s21 {

namespace Protocol {
  struct GraphParameters;
  struct GraphResult;
  struct CreditParameters;
  struct CreditResult;
}

namespace Controller {

class Calculator {
private:
  Model::SingleCalculator model_;
public:
  Calculator(const std::string& input, double x);
  std::optional<double> Run();

};


class GraphCalculator {
private:
  Model::MultiCalculator model_;
public:
  GraphCalculator(const Protocol::GraphParameters& gp);
  std::optional<Protocol::GraphResult> Run();
};

class CreditCalculator {
private:
  Model::CreditCalculator model_;
public:
  CreditCalculator(const Protocol::CreditParameters& cp);
  bool Run();
  std::optional<Protocol::CreditResult> Get() const;

};

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