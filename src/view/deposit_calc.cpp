#include "deposit_calc.h"
#include "ui_deposit_calc.h"
#include "../controller/controller.h"
#include <array>

deposit_calc::deposit_calc(QWidget *parent, Controller* controller_)
    : QDialog(parent), ui(new Ui::deposit_calc) {
  ui->setupUi(this);
}

deposit_calc::~deposit_calc() { delete ui; }



struct DepositResult {
  double accruedTotal_;
  double taxTotal_;
  double amountTotal_;

  std::vector<double> list_;
};

struct DepositParameters {
  double amount_ = 0.0;
  int period_ = 0;
  double interest_ = 0.0;
  double tax_ = 0.0;

  enum class Capitalization {
    Undefined,
    Total,
    Monthly,
  };
  enum class PaymentFrequency {
    Undefined,
    Total,
    Monthly,
  };

  Capitalization capitalization_ = Capitalization::Undefined;
  PaymentFrequency frequency_ = PaymentFrequency::Undefined;
};

bool CalculateDeposit(const DepositParameters& parameters, DepositResult& result) {
  static constexpr std::array<int, 12> daysPerMonth { 
    31, // jan 
    28, // feb
    31, // mar
    30, // apr
    31, // may
    30, // jun 
    31, // jul
    31, // aug
    30, // sep
    31, // oct
    30, // nov
    31, // dec
  };
  static constexpr int months = 12;
  static constexpr int days = 365;

  if (parameters.capitalization_ == DepositParameters::Capitalization::Undefined)
    return false;
  if (parameters.frequency_ == DepositParameters::PaymentFrequency::Undefined)
    return false;
  if (parameters.amount_ < 0.01)
    return false;
  if (parameters.interest_ < 0.0)
    return false;
  if (parameters.interest_ > 100.0)
    return false;
  if (parameters.tax_ < 0.0)
    return false;
  if (parameters.tax_ > 100.0)
    return false;
  if (parameters.period_ < 1)
    return false;
  if (parameters.period_ > 600)
    return false;
  
  double sum = parameters.amount_;
  result.amountTotal_ = parameters.amount_;
  result.taxTotal_ = 0.0;
  result.accruedTotal_ = 0.0;

  if (parameters.frequency_ == DepositParameters::PaymentFrequency::Monthly)
    result.list_.reserve(parameters.period_);
  
  for (int i = 0; i < parameters.period_; ++i) {
    const int daysDelta = daysPerMonth[i % months];
    const double deltaInterest = sum / 100.0 * parameters.interest_ / days * daysDelta;
    const double deltaTax = deltaInterest / 100.0 * parameters.tax_;
    const double deltaSum = deltaInterest - deltaTax;

    if (parameters.capitalization_ == DepositParameters::Capitalization::Monthly)
      sum += deltaSum;

    result.amountTotal_ += deltaSum;
    result.taxTotal_ += deltaTax;
    result.accruedTotal_ += deltaInterest;

    if (parameters.frequency_ == DepositParameters::PaymentFrequency::Monthly)
      result.list_.push_back(deltaSum);
  }

  if (parameters.frequency_ == DepositParameters::PaymentFrequency::Total)
    result.list_.push_back(result.amountTotal_ - parameters.amount_);

  return true;
}


void deposit_calc::on_pushButton_clicked() {
  DepositParameters dp;
  // double deposit_sum = 0.0;
  // float deposit_percent = 0.0f;
  // float tax_percent = 0.0f;
  // int type_cap = 0;
  // int type_pay = 0;

  ui->interest_income->setText("");
  ui->total_deposit_sum->setText("");
  ui->tax_sum->setText("");
  ui->error_label->setText("");

  // deposit_sum = ui->deposit_sum->text().toDouble();
  dp.amount_ = ui->deposit_sum->text().toDouble();
  // deposit_percent = ui->deposit_percent->text().toFloat();
  dp.interest_ = ui->deposit_percent->text().toFloat();
  // tax_percent = ui->tax_percent->text().toFloat();
  dp.tax_ = ui->tax_percent->text().toFloat();
  // deposit_term = ui->deposit_term->text().toInt();
  dp.period_ = ui->deposit_term->text().toInt();

  if (ui->radioB_mon_cap->isChecked()) {
    // type_cap = 1;
    dp.capitalization_ = DepositParameters::Capitalization::Monthly;
  } else if (ui->radioB_end_cap->isChecked()) {
    // type_cap = 2;
    dp.capitalization_ = DepositParameters::Capitalization::Total;
  }

  if (ui->radioB_mon_pay->isChecked()) {
    // type_pay = 1;
    dp.frequency_ = DepositParameters::PaymentFrequency::Monthly;
  } else if (ui->radioB_end_pay->isChecked()) {
    // type_pay = 2;
    dp.frequency_ = DepositParameters::PaymentFrequency::Total;
  }

  DepositResult dr;
  // if (type_cap == 0 || type_pay == 0 || deposit_sum < 0.01 ||
  //     deposit_percent < 0 || deposit_percent > 100 || tax_percent < 0 ||
  //     tax_percent > 100 || deposit_term < 1 || deposit_term > 600) {
  if (!CalculateDeposit(dp, dr)) {
    ui->error_label->setText("INCORRECT INPUT");
    return;
  }
  // } else {
    // double add_sum[deposit_term];

    // if (ui->checkBox_add->isChecked()) {
    //   for (int i = 0; i < deposit_term; i++) {
    //     QTableWidgetItem *itm = ui->tableWidget->item(i, 0);
    //     if (itm != NULL) {
    //       add_sum[i] = itm->text().toDouble();
    //     } else {
    //       add_sum[i] = 0;
    //     }
    //   }
    // }

    // double interest_income = 0;
    // double total_deposit_sum = 0;
    // double tax_sum = 0;
    // int ex_code = 0;

    // ex_code = controller_->deposit_calc_fn(deposit_sum, deposit_term, deposit_percent,
    //                           tax_percent, type_cap, type_pay, add_sum,
    //                           &interest_income, &total_deposit_sum, &tax_sum);
    // if (interest_income >= 0 && total_deposit_sum >= 0 && ex_code == 0) {
      // QString int_income = QString::number(interest_income, 'f', 2);
      QString int_income = QString::number(dr.accruedTotal_, 'f', 2);
      ui->interest_income->setText(int_income);
      // QString total_dep_sum = QString::number(total_deposit_sum, 'f', 2);
      QString total_dep_sum = QString::number(dr.amountTotal_, 'f', 2);
      ui->total_deposit_sum->setText(total_dep_sum);
      // QString total_tax_sum = QString::number(tax_sum, 'f', 2);
      QString total_tax_sum = QString::number(dr.taxTotal_, 'f', 2);
      ui->tax_sum->setText(total_tax_sum);
    // } else {
      // ui->error_label->setText("INCORRECT INPUT");
    // }
  



  ui->tableWidget->setRowCount(dr.list_.size());
  ui->tableWidget->setColumnCount(1);



  // double initial_sum = deposit_sum;
  // double final_sum = deposit_sum;
  // int days = 0;
    // for (int i = 0; i < deposit_term; i++) {
    for (int i = 0; i < static_cast<signed>(dr.list_.size()); ++i) {
      // days += daysPerMonth[i % 12];
      // const int daysDelta = daysPerMonth[i % 12];

      // const double deltaSum = deposit_sum / 100.0 * (deposit_percent - tax_percent) / 365.0 * daysDelta;
      // deposit_sum += deltaSum;
      // final_sum += deltaSum;
      // QTableWidgetItem *itm = new QTableWidgetItem(QString::number(deltaSum));
      QTableWidgetItem *itm = new QTableWidgetItem(QString::number(dr.list_.at(i)));
      ui->tableWidget->setItem(i, 0, itm);
    }
    

}

void deposit_calc::on_checkBox_add_stateChanged(int arg1) {
  if (ui->checkBox_add->isChecked()) {
    deposit_term = ui->deposit_term->text().toInt();
    ui->tableWidget->setRowCount(deposit_term);
    ui->tableWidget->setColumnCount(1);
  } else {
    ui->tableWidget->clear();
  }
}
