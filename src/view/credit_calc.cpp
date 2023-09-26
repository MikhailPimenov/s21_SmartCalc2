#include "credit_calc.h"

#include <QTableWidgetItem>

#include "QtWidgets/qtableview.h"
#include "ui_credit_calc.h"
#include "../controller/controller.h"

credit_calc::credit_calc(QWidget *parent, Controller* controller_)
    : QDialog(parent), ui(new Ui::credit_calc) {
  ui->setupUi(this);
}

credit_calc::~credit_calc() { delete ui; }

void credit_calc::on_make_calc_clicked() {
  ui->label_error->setText("");
  ui->monthly_payment->setText("");
  ui->overpayment->setText("");
  ui->total_sum->setText("");

  Controller::CreditParameters cp;

  cp.credit_sum_ = ui->credit_sum->text().toDouble();
  cp.credit_term_ = ui->credit_term->text().toInt();
  cp.credit_percent_ = ui->credit_percent->text().toFloat();

  if (ui->radioButton->isChecked()) {
    cp.order_ = Controller::CreditParameters::RepainmentOrder::Annuity;
  } else if (ui->radioButton_2->isChecked()) {
    cp.order_= Controller::CreditParameters::RepainmentOrder::Differentiated;
  }

  Controller::CreditResult cr;

  // if (type == 0 || credit_sum < 10000 || credit_sum > 100000000 ||
  //     credit_term < 1 || credit_term > 600 || credit_percent < 0.01 ||
  //     credit_percent > 100) {
  if (!Controller::CalculateCredit(cp, cr)) {
    ui->label_error->setText("Incorrect input");
    return;
  } 
    double overpayment;
    double total_sum;

    // controller_->credit_calc_fn(credit_sum, credit_term, credit_percent, type,
    //                &monthly_payment, &overpayment, &total_sum);

    QString mon_pay = QString::number(cr.monthlty_payment_, 'f', 2);
    ui->monthly_payment->setText(mon_pay);
    QString overpay = QString::number(cr.overpayment_, 'f', 2);
    ui->overpayment->setText(overpay);
    QString tot_sum = QString::number(cr.total_sum_, 'f', 2);
    ui->total_sum->setText(tot_sum);
  
  ui->tableWidget->setRowCount(cp.credit_term_);
  ui->tableWidget->setColumnCount(1);

  // if (type == 1) {
     for (int i = 0; i < cp.credit_term_; i++) {
      QTableWidgetItem *itm =
          new QTableWidgetItem(QString::number(cr.list_.at(i)));
      ui->tableWidget->setItem(i, 0, itm);
    }
  // } else if (type == 2) {
  //   for (int i = 0; i < credit_term; i++) {
  //     double month_pay_count = credit_sum / credit_term +
  //         (credit_sum - monthly_payment * i) * credit_percent / 1200;
  //     QTableWidgetItem *itm =
  //         new QTableWidgetItem(QString::number(month_pay_count));
  //     ui->tableWidget->setItem(i, 0, itm);
  //   }
  // }
}

// void credit_calc::on_make_table_clicked() {
//   ui->tableWidget->setRowCount(credit_term);
//   ui->tableWidget->setColumnCount(1);

//   if (type == 1) {
//     for (int i = 0; i < credit_term; i++) {
//       QTableWidgetItem *itm =
//           new QTableWidgetItem(QString::number(monthly_payment));
//       ui->tableWidget->setItem(i, 0, itm);
//     }
//   } else if (type == 2) {
//     for (int i = 0; i < credit_term; i++) {
//       double month_pay_count = credit_sum / credit_term +
//           (credit_sum - monthly_payment * i) * credit_percent / 1200;
//       QTableWidgetItem *itm =
//           new QTableWidgetItem(QString::number(month_pay_count));
//       ui->tableWidget->setItem(i, 0, itm);
//     }
//   }
// }
