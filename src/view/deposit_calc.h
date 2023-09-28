#ifndef DEPOSIT_CALC_H
#define DEPOSIT_CALC_H

#include <QDialog>


namespace Ui {
class deposit_calc;
}

class DepositWindow : public QDialog {
  Q_OBJECT

 public:
  explicit DepositWindow(QWidget *parent = nullptr, class Controller* controller = nullptr);
  ~DepositWindow();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::deposit_calc *ui;
  Controller* controller_ = nullptr;
};

#endif  // DEPOSIT_CALC_H
