#include "mainwindow.h"

#include <cmath>
#include <iostream>
#include <vector>

#include "../controller/controller.h"
#include "../protocol/protocol.h"
#include "./ui_mainwindow.h"
#include "credit_calc.h"
#include "deposit_calc.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(push_button()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(push_button()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(push_button()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(push_button()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(push_button()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(push_button()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(push_button()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(push_button()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(push_button()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(push_button()));

  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(push_dot_button()));

  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(push_x_button()));

  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(push_button_open_bracket()));
  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(push_button_close_bracket()));

  connect(ui->pushButton_power, SIGNAL(clicked()), this,
          SLOT(push_button_operation()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(push_button_operation()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(push_button_operation()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(push_button_operation()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(push_button_operation_un()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(push_button_operation_un()));

  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(push_button_operation_fn()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(push_button_operation_fn()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(push_button_operation_fn()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(push_button_operation_fn()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(push_button_operation_fn()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(push_button_operation_fn()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(push_button_operation_fn()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(push_button_operation_fn()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(push_button_operation_fn()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::push_button() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());
  if (string_.isEmpty() == 0) {
    if (string_.back() != ')' || string_.back() != 'x') {
      string_ = (ui->label->text() + button->text());
    }
  } else {
    string_ = (ui->label->text() + button->text());
  }
  ui->label->setText(string_);
}

void MainWindow::push_dot_button() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());
  if (string_.isEmpty() == 0) {
    if (string_.back() >= '0' && string_.back() <= '9') {
      string_ = (ui->label->text() + button->text());
    }
  }
  ui->label->setText(string_);
}

void MainWindow::push_x_button() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());
  if (string_.isEmpty() == 0) {
    if (string_.back() == ')' || string_.back() == 'x' ||
        (string_.back() >= '0' && string_.back() <= '9') || string_ == '.') {
    } else {
      string_ = (ui->label->text() + button->text());
    }
  } else {
    string_ = (ui->label->text() + button->text());
  }
  ui->label->setText(string_);
}

void MainWindow::push_button_operation() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());
  if (string_.isEmpty() == 0) {
    if ((string_.back() >= '0' && string_.back() <= '9') ||
        string_.back() == ')' || string_.back() == 'x') {
      string_ = (ui->label->text() + button->text());
      ui->label->setText(string_);
    }
  }
}

void MainWindow::push_button_operation_un() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());
  if (string_.isEmpty() == 0) {
    if ((string_.back() >= '0' && string_.back() <= '9') ||
        string_.back() == ')' || string_.back() == '(' ||
        string_.back() == 'x') {
      string_ = (ui->label->text() + button->text());
    }
  } else {
    string_ = (ui->label->text() + button->text());
  }
  ui->label->setText(string_);
}

void MainWindow::push_button_close_bracket() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());
  if (string_.isEmpty() == 0) {
    if ((string_.back() >= '0' && string_.back() <= '9') ||
        string_.back() == ')' || string_.back() == 'x') {
      string_ = (ui->label->text() + button->text());
    }
  }
  ui->label->setText(string_);
}

void MainWindow::push_button_open_bracket() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());
  if (string_.isEmpty() == 0) {
    if (!(string_.back() >= '0' && string_.back() <= '9' ||
          string_.back() == '.' || string_.back() == 'x')) {
      string_ = (ui->label->text() + button->text());
    }
  } else {
    string_ = (ui->label->text() + button->text());
  }
  ui->label->setText(string_);
}

void MainWindow::push_button_operation_fn() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());
  if (string_.isEmpty() == 0) {
    if (string_.back() == '+' || string_.back() == '-' ||
        string_.back() == '(' || string_.back() == '*' ||
        string_.back() == '/' || string_.back() == 'd' ||
        string_.back() == '^') {
      string_ = (ui->label->text() + button->text());
    }
  } else {
    string_ = (ui->label->text() + button->text());
  }
  ui->label->setText(string_);
}

void MainWindow::on_pushButton_equal_clicked() {
  const int len = static_cast<int>(string_.size());
  if (len < 256) {
    double x_value = ui->x_value->text().toDouble();
    // int ex_code =
        // controller_->Calculate(string_.toStdString(), &result, x_value);
    Controller::Calculator calculator(string_.toStdString(), x_value);
    std::optional<double> result = calculator.Run();
    
    string_.clear();
    ui->label->clear();

    if (result.has_value()) {
      QString str_res = QString::number(result.value(), 'g', 7);
      ui->label->setText(str_res);
    } else {
      ui->label->setText("INCORRECT INPUT");
    }
  } else {
    ui->label->setText("Too long string");
  }
}

void MainWindow::on_pushButton_all_clean_clicked() {
  string_.clear();
  ui->label->clear();
  ui->widget->clearGraphs();
}

void MainWindow::on_pushButton_clean_clicked() {
  if (string_.isEmpty() == 0) {
    if (string_.back() == 'd' || string_.back() == 'g') {
      string_.chop(3);
    } else if (string_.back() == 't') {
      string_.chop(4);
    } else if (string_.back() == 's') {
      string_.chop(3);
      if (string_.isEmpty() == 0 && string_.back() == 'a') {
        string_.chop(1);
      }
    } else if (string_.back() == 'n') {
      string_.chop(2);
      if (string_.isEmpty() == 0 &&
          (string_.back() == 's' || string_.back() == 't')) {
        string_.chop(1);
        if (string_.isEmpty() == 0 && string_.back() == 'a') {
          string_.chop(1);
        }
      }
    } else {
      string_.chop(1);
    }
    ui->label->setText(string_);
  }
}

void MainWindow::on_pushButton_graph_clicked() {
  ui->widget->clearGraphs();
  Protocol::GraphParameters gp;
  gp.x_max = ui->input_xmax->text().toDouble();
  gp.x_min = ui->input_xmin->text().toDouble();
  gp.input_string = string_.toStdString();
  const double y_max = ui->input_ymax->text().toDouble();
  const double y_min = ui->input_ymin->text().toDouble();

  Protocol::GraphResult gr;

  // const int ex_code = controller_->CalculateGraph(gp, gr);
  Controller::GraphCalculator calculator(gp);
  const std::optional<Protocol::GraphResult> result = calculator.Run();
  if (!result.has_value()) return;

  const QVector<double> x(result->x.begin(), result->x.end()),
      y(result->y.begin(), result->y.end());

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);

  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");

  ui->widget->xAxis->setRange(gp.x_min, gp.x_max);
  ui->widget->yAxis->setRange(y_min, y_max);

  ui->widget->replot();
}

void MainWindow::on_credit_calc_clicked() {
  CreditWindow window(nullptr);
  window.setModal(true);
  window.exec();
}

void MainWindow::on_deposit_calc_clicked() {
  DepositWindow window(nullptr);
  window.setModal(true);
  window.exec();
}

}  // namespace s21