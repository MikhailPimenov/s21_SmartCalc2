#ifndef DEPOSIT_CALC_H
#define DEPOSIT_CALC_H

#include <QDialog>

namespace Ui {
class deposit_calc;
}

namespace s21 {

/**
 * @brief Class for deposit window
 *
 */
class DepositWindow : public QDialog {
  Q_OBJECT

 public:
  // explicit DepositWindow(QWidget *parent = nullptr,
  //                        class Controller *controller = nullptr);
  explicit DepositWindow(QWidget *parent = nullptr);
  ~DepositWindow();

 private slots:
  /**
   * @brief Called when button is clicked - runs deposit calculation
   *
   * @return ** void
   */
  void on_pushButton_clicked();
  /**
   * @brief Called when button for list input is clicked
   * Allows to input monthly addition to deposit or take from deposit
   * Show detailes on each month
   * @return ** void
   */
  void on_checkBox_add_stateChanged(int);

 private:
  Ui::deposit_calc *ui;
  // Controller *controller_ = nullptr;
};

}  // namespace s21

#endif  // DEPOSIT_CALC_H
