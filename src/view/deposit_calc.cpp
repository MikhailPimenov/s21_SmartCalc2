#include "deposit_calc.h"
#include "ui_deposit_calc.h"
#include "../controller/controller.h"


DepositWindow::DepositWindow(QWidget *parent, Controller* controller_)
    : QDialog(parent), ui(new Ui::deposit_calc) {
  ui->setupUi(this);
}

DepositWindow::~DepositWindow() { delete ui; }


void DepositWindow::on_pushButton_clicked() {
  ui->interest_income->setText("");
  ui->total_deposit_sum->setText("");
  ui->tax_sum->setText("");
  ui->error_label->setText("");

  Controller::DepositParameters dp;
  dp.amount_ = ui->deposit_sum->text().toDouble();
  dp.interest_ = ui->deposit_percent->text().toFloat();
  dp.tax_ = ui->tax_percent->text().toFloat();
  dp.period_ = ui->deposit_term->text().toInt();

  if (ui->radioB_mon_cap->isChecked()) {
    dp.capitalization_ = Controller::DepositParameters::Capitalization::Monthly;
  } else if (ui->radioB_end_cap->isChecked()) {
    dp.capitalization_ = Controller::DepositParameters::Capitalization::Total;
  }

  if (ui->radioB_mon_pay->isChecked()) {
    dp.frequency_ = Controller::DepositParameters::PaymentFrequency::Monthly;
  } else if (ui->radioB_end_pay->isChecked()) {
    dp.frequency_ = Controller::DepositParameters::PaymentFrequency::Total;
  }

  Controller::DepositResult dr;
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

  ui->tableWidget->setRowCount(dr.list_.size());
  ui->tableWidget->setColumnCount(1);

  for (int i = 0; i < static_cast<signed>(dr.list_.size()); ++i) {
    QTableWidgetItem *itm = new QTableWidgetItem(QString::number(dr.list_.at(i)));
    ui->tableWidget->setItem(i, 0, itm);
  }
}
