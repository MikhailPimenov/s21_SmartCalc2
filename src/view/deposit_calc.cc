#include "deposit_calc.h"

#include "../controller/controller.h"
#include "../protocol/protocol.h"
#include "ui_deposit_calc.h"

namespace s21 {

DepositWindow::DepositWindow(QWidget *parent, Controller *controller_)
    : QDialog(parent), ui(new Ui::deposit_calc) {
  ui->setupUi(this);
}

DepositWindow::~DepositWindow() { delete ui; }

void DepositWindow::on_pushButton_clicked() {
  ui->interest_income->setText("");
  ui->total_deposit_sum->setText("");
  ui->tax_sum->setText("");
  ui->error_label->setText("");

  Protocol::DepositParameters dp;
  dp.amount_ = ui->deposit_sum->text().toDouble();
  dp.interest_ = ui->deposit_percent->text().toFloat();
  dp.tax_ = ui->tax_percent->text().toFloat();
  dp.period_ = ui->deposit_term->text().toInt();

  ui->tableWidget->setHorizontalHeaderLabels({
      {"+/-"},
      {"Added as %"},
      {"Total"},
  });
  ui->tableWidget->setRowCount(dp.period_);
  ui->tableWidget->setColumnCount(3);

  if (ui->checkBox_add->isChecked()) {
    dp.depositOrWithdrawal_.reserve(dp.period_);
    for (int i = 0; i < dp.period_; ++i) {
      if (ui->tableWidget->item(i, 0))
        dp.depositOrWithdrawal_.push_back(
            ui->tableWidget->item(i, 0)->text().toDouble());
      else
        dp.depositOrWithdrawal_.push_back(0.0);
    }
  }

  if (ui->radioB_mon_cap->isChecked()) {
    dp.capitalization_ = Protocol::DepositParameters::Capitalization::Monthly;
  } else if (ui->radioB_end_cap->isChecked()) {
    dp.capitalization_ = Protocol::DepositParameters::Capitalization::Total;
  }

  if (ui->radioB_mon_pay->isChecked()) {
    dp.frequency_ = Protocol::DepositParameters::PaymentFrequency::Monthly;
  } else if (ui->radioB_end_pay->isChecked()) {
    dp.frequency_ = Protocol::DepositParameters::PaymentFrequency::Total;
  }

  Protocol::DepositResult dr;
  if (!controller_->CalculateDeposit(dp, dr)) {
    ui->error_label->setText("INCORRECT INPUT");
    return;
  }

  QString int_income = QString::number(dr.accruedTotal_, 'f', 2);
  ui->interest_income->setText(int_income);
  QString total_dep_sum = QString::number(dr.amountTotal_, 'f', 2);
  ui->total_deposit_sum->setText(total_dep_sum);
  QString total_tax_sum = QString::number(dr.taxTotal_, 'f', 2);
  ui->tax_sum->setText(total_tax_sum);

  if (!ui->checkBox_add->isChecked()) return;

  for (int i = 0; i < static_cast<signed>(dr.percentMonthly_.size()); ++i) {
    QTableWidgetItem *itm =
        new QTableWidgetItem(QString::number(dr.percentMonthly_.at(i)));
    ui->tableWidget->setItem(i, 1, itm);
  }
  for (int i = 0; i < static_cast<signed>(dr.accruedMonthly_.size()); ++i) {
    QTableWidgetItem *itm =
        new QTableWidgetItem(QString::number(dr.accruedMonthly_.at(i)));
    ui->tableWidget->setItem(i, 2, itm);
  }
}

void DepositWindow::on_checkBox_add_stateChanged(int arg1) {
  if (ui->checkBox_add->isChecked()) {
    ui->tableWidget->setHorizontalHeaderLabels({
        {"+/-"},
        {"Added as %"},
        {"Total"},
    });
    const int deposit_term = ui->deposit_term->text().toInt();
    ui->tableWidget->setRowCount(deposit_term);
    ui->tableWidget->setColumnCount(3);
  } else {
    ui->tableWidget->clear();
  }
}

}  //  namespace s21
