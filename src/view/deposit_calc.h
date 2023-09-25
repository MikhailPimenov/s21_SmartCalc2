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
  int deposit_term;

 private slots:
  void on_pushButton_clicked();
  void on_checkBox_add_stateChanged(int arg1);
  void on_make_table_clicked();

 private:
  Ui::deposit_calc *ui;
  Controller* controller_ = nullptr;
};

#endif  // DEPOSIT_CALC_H
