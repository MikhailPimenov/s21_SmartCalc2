#include "credit_calc.h"

#include <QTableWidgetItem>

#include "QtWidgets/qtableview.h"
#include "ui_credit_calc.h"
#include "../controller/controller.h"

namespace s21 {


CreditWindow::CreditWindow(QWidget *parent, Controller* controller_)
    : QDialog(parent), ui(new Ui::credit_calc) {
  ui->setupUi(this);
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::on_make_calc_clicked() {
  ui->label_error->setText("");
  ui->monthly_payment->setText("");
  ui->overpayment->setText("");
  ui->total_sum->setText("");

  Controller::CreditParameters cp;

  cp.creditSum_ = ui->credit_sum->text().toDouble();
  cp.creditTerm_ = ui->credit_term->text().toInt();
  cp.creditPercent_ = ui->credit_percent->text().toFloat();

  if (ui->radioButton->isChecked()) {
    cp.order_ = Controller::CreditParameters::RepainmentOrder::Annuity;
  } else if (ui->radioButton_2->isChecked()) {
    cp.order_= Controller::CreditParameters::RepainmentOrder::Differentiated;
  }

  Controller::CreditResult cr;

  if (!controller_->CalculateCredit(cp, cr)) {
    ui->label_error->setText("Incorrect input");
    return;
  } 

  QString mon_pay = QString::number(cr.monthlyPayment_, 'f', 2);
  ui->monthly_payment->setText(mon_pay);
  QString overpay = QString::number(cr.overpayment_, 'f', 2);
  ui->overpayment->setText(overpay);
  QString tot_sum = QString::number(cr.totalSum_, 'f', 2);
  ui->total_sum->setText(tot_sum);
  
  ui->tableWidget->setRowCount(cp.creditTerm_);
  ui->tableWidget->setColumnCount(1);

  for (int i = 0; i < cp.creditTerm_; i++) {
    QTableWidgetItem *itm =
        new QTableWidgetItem(QString::number(cr.list_.at(i)));
    ui->tableWidget->setItem(i, 0, itm);
  }
}

} //  namespace s21