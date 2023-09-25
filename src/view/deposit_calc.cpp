#include "deposit_calc.h"
#include "ui_deposit_calc.h"
#include "../controller/controller.h"
#include <array>

deposit_calc::deposit_calc(QWidget *parent, Controller* controller_)
    : QDialog(parent), ui(new Ui::deposit_calc) {
  ui->setupUi(this);
}

deposit_calc::~deposit_calc() { delete ui; }

void deposit_calc::on_pushButton_clicked() {
  double deposit_sum = 0.0;
  float deposit_percent = 0.0f;
  float tax_percent = 0.0f;
  int type_cap = 0;
  int type_pay = 0;

  ui->interest_income->setText("");
  ui->total_deposit_sum->setText("");
  ui->tax_sum->setText("");
  ui->error_label->setText("");

  deposit_sum = ui->deposit_sum->text().toDouble();
  deposit_percent = ui->deposit_percent->text().toFloat();
  tax_percent = ui->tax_percent->text().toFloat();
  deposit_term = ui->deposit_term->text().toInt();

  if (ui->radioB_mon_cap->isChecked()) {
    type_cap = 1;
  } else if (ui->radioB_end_cap->isChecked()) {
    type_cap = 2;
  }

  if (ui->radioB_mon_pay->isChecked()) {
    type_pay = 1;
  } else if (ui->radioB_end_pay->isChecked()) {
    type_pay = 2;
  }

  if (type_cap == 0 || type_pay == 0 || deposit_sum < 0.01 ||
      deposit_percent < 0 || deposit_percent > 100 || tax_percent < 0 ||
      tax_percent > 100 || deposit_term < 1 || deposit_term > 600) {
    ui->error_label->setText("INCORRECT INPUT");
  } else {
    double add_sum[deposit_term];

    if (ui->checkBox_add->isChecked()) {
      for (int i = 0; i < deposit_term; i++) {
        QTableWidgetItem *itm = ui->tableWidget->item(i, 0);
        if (itm != NULL) {
          add_sum[i] = itm->text().toDouble();
        } else {
          add_sum[i] = 0;
        }
      }
    }

    double interest_income = 0;
    double total_deposit_sum = 0;
    double tax_sum = 0;
    int ex_code = 0;

    ex_code = controller_->deposit_calc_fn(deposit_sum, deposit_term, deposit_percent,
                              tax_percent, type_cap, type_pay, add_sum,
                              &interest_income, &total_deposit_sum, &tax_sum);
    if (interest_income >= 0 && total_deposit_sum >= 0 && ex_code == 0) {
      QString int_income = QString::number(interest_income, 'f', 2);
      ui->interest_income->setText(int_income);
      QString total_dep_sum = QString::number(total_deposit_sum, 'f', 2);
      ui->total_deposit_sum->setText(total_dep_sum);
      QString total_tax_sum = QString::number(tax_sum, 'f', 2);
      ui->tax_sum->setText(total_tax_sum);
    } else {
      ui->error_label->setText("INCORRECT INPUT");
    }
  }



  ui->tableWidget->setRowCount(deposit_term);
  ui->tableWidget->setColumnCount(1);
  std::array<int, 12> daysPerMonth { 
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

// Общая формула: доход по вкладу 
// = сумма вклада / 100% * % ставку / количество дней в году * количество дней действия вклада.

// Доход по вкладу = 100 000 / 100 * 4 = 4 000 (рублей) — потенциальный доход за 12 месяцев.
double initial_sum = deposit_sum;
int days = 0;
  // if (type == 1) {
    // for (int i = 0; i < credit_term; i++) {
    for (int i = 0; i < deposit_term; i++) {
      days += daysPerMonth[i % 12];
      const int daysDelta = daysPerMonth[i % 12];
      // initial_sum = deposit_sum / 100.0 * (deposit_percent - tax_percent) / 365.0 * days;

      const double deltaSum = deposit_sum / 100.0 * (deposit_percent - tax_percent) / 365.0 * daysDelta;
      deposit_sum += deltaSum;
      QTableWidgetItem *itm =
          // new QTableWidgetItem(QString::number(monthly_payment));
          new QTableWidgetItem(QString::number(deltaSum));
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

void deposit_calc::on_make_table_clicked() {
  // ui->tableWidget->setRowCount(credit_term);
  ui->tableWidget->setRowCount(3);
  ui->tableWidget->setColumnCount(1);

  // if (type == 1) {
    // for (int i = 0; i < credit_term; i++) {
    for (int i = 0; i < 3; i++) {
      QTableWidgetItem *itm =
          // new QTableWidgetItem(QString::number(monthly_payment));
          new QTableWidgetItem(QString::number(100 * i + 13));
      ui->tableWidget->setItem(i, 0, itm);
    }
  // } else if (type == 2) {
    // for (int i = 0; i < credit_term; i++) {
      // double month_pay_count = credit_sum / credit_term +
          // (credit_sum - monthly_payment * i) * credit_percent / 1200;
      // QTableWidgetItem *itm =
          // new QTableWidgetItem(QString::number(month_pay_count));
      // ui->tableWidget->setItem(i, 0, itm);
    // }
  // }
}
