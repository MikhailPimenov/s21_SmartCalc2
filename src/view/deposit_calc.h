#ifndef DEPOSIT_CALC_H
#define DEPOSIT_CALC_H

#include <QDialog>


namespace Ui {
class deposit_calc;
}

class deposit_calc : public QDialog {
  Q_OBJECT

 public:
  explicit deposit_calc(QWidget *parent = nullptr, class Controller* controller = nullptr);
  ~deposit_calc();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::deposit_calc *ui;
  Controller* controller_ = nullptr;
};

#endif  // DEPOSIT_CALC_H
