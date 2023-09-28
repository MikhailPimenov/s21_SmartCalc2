#include "controller.h"
#include "../model/model.h"

Controller::Controller() {}

int Controller::Calculate(const std::string& input_str, double *result, double x_value) {
    return Model::Calculate(input_str, result, x_value);
}
int Controller::CalculateGraph(const GraphParameters& gp, GraphResult& gr) {
    Model::GraphParameters mgp;
    mgp.x_max = gp.x_max;
    mgp.x_min = gp.x_min;
    mgp.input_string = gp.input_string;

    Model::GraphResult mgr;

    const int ex_code = Model::CalculateGraph(mgp, mgr);
    gr.x = std::move(mgr.x); 
    gr.y = std::move(mgr.y); 

    return ex_code;
};

bool Controller::CalculateCredit(const CreditParameters& cp, CreditResult& cr) {
    Model::CreditParameters mcp;
    mcp.creditSum_ = cp.creditSum_;
    mcp.creditTerm_ = cp.creditTerm_;
    mcp.creditPercent_= cp.creditPercent_;
    mcp.order_ = static_cast<Model::CreditParameters::RepainmentOrder>(cp.order_);

    Model::CreditResult mcr;
    const bool result = Model::CalculateCredit(mcp, mcr);

    cr.monthltyPayment_  = mcr.monthltyPayment_ ;
    cr.overpayment_ = mcr.overpayment_;
    cr.list_ = std::move(mcr.list_);
    cr.totalSum_ = mcr.totalSum_;

    return result;
}

bool Controller::CalculateDeposit(const DepositParameters& dp, DepositResult& dr) {
    Model::DepositParameters mdp;
    mdp.amount_ = dp.amount_;
    mdp.interest_ = dp.interest_;
    mdp.tax_ = dp.tax_;
    mdp.period_ = dp.period_;
    mdp.capitalization_ = static_cast<Model::DepositParameters::Capitalization>(dp.capitalization_);
    mdp.frequency_ = static_cast<Model::DepositParameters::PaymentFrequency>(dp.frequency_);

    Model::DepositResult mdr;
    const bool result = Model::CalculateDeposit(mdp, mdr);

    dr.accruedTotal_ = mdr.accruedTotal_;
    dr.amountTotal_ = mdr.amountTotal_;
    dr.list_ = std::move(mdr.list_);
    dr.taxTotal_ = mdr.taxTotal_;

    return result;
}

