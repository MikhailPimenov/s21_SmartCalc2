#include "credit_calc.h"

#include <QTableWidgetItem>

#include "../controller/controller.h"
#include "../protocol/protocol.h"
#include "QtWidgets/qtableview.h"
#include "ui_credit_calc.h"

namespace s21 {

CreditWindow::CreditWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::credit_calc) {
  ui->setupUi(this);
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::on_make_calc_clicked() {
  ui->label_error->setText("");
  ui->monthly_payment->setText("");
  ui->overpayment->setText("");
  ui->total_sum->setText("");

  Protocol::CreditParameters parameters;

  parameters.creditSum_ = ui->credit_sum->text().toDouble();
  parameters.creditTerm_ = ui->credit_term->text().toInt();
  parameters.creditPercent_ = ui->credit_percent->text().toFloat();

  if (ui->radioButton->isChecked()) {
    parameters.order_ = Protocol::CreditParameters::RepainmentOrder::Annuity;
  } else if (ui->radioButton_2->isChecked()) {
    parameters.order_ =
        Protocol::CreditParameters::RepainmentOrder::Differentiated;
  }

  Controller::CreditCalculator calculator(parameters);
  calculator.Run();
  const std::optional<Protocol::CreditResult> result = calculator.Get();
  if (!result.has_value()) {
    ui->label_error->setText("Incorrect input");
    return;
  }

  QString mon_pay = QString::number(result->monthlyPayment_, 'f', 2);
  ui->monthly_payment->setText(mon_pay);
  QString overpay = QString::number(result->overpayment_, 'f', 2);
  ui->overpayment->setText(overpay);
  QString tot_sum = QString::number(result->totalSum_, 'f', 2);
  ui->total_sum->setText(tot_sum);

  ui->tableWidget->setRowCount(parameters.creditTerm_);
  ui->tableWidget->setColumnCount(1);

  for (int i = 0; i < parameters.creditTerm_; i++) {
    QTableWidgetItem *itm = new QTableWidgetItem(
        QString::number(result->monthlyPaymentList_.at(i)));
    ui->tableWidget->setItem(i, 0, itm);
  }
}

}  //  namespace s21