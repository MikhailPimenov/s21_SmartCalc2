#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include <QDialog>

namespace Ui {
class credit_calc;
}

namespace s21 {

/**
 * @brief Class for credit window
 *
 */
class CreditWindow : public QDialog {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr,
                        class Controller *controller = nullptr);
  ~CreditWindow();

 private slots:
  /**
   * @brief Called when push button is clicked - runs credit calculation
   *
   * @return ** void
   */
  void on_make_calc_clicked();

 private:
  Ui::credit_calc *ui;
  Controller *controller_ = nullptr;
};

}  //  namespace s21

#endif  // CREDIT_CALC_H
