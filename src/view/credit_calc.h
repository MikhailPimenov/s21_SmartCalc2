#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include <QDialog>


namespace Ui {
class credit_calc;
}

class CreditWindow : public QDialog {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr, class Controller* controller = nullptr);
  ~CreditWindow();


 private slots:
  void on_make_calc_clicked();

 private:
  Ui::credit_calc *ui;
  Controller* controller_ = nullptr;
};

#endif  // CREDIT_CALC_H
