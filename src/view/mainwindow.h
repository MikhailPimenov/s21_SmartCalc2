#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

/**
 * @brief Class of main window of interface
 *
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  // MainWindow(QWidget *parent = nullptr, class Controller *controller = nullptr);
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  // Controller *controller_ = nullptr;
  QString string_;

 private slots:
  /**
   * @brief Adds digit to input string
   *
   * @return ** void
   */
  void push_button();
  /**
   * @brief Adds dot to input line to add fractional part of the number
   *
   * @return ** void
   */
  void push_dot_button();
  /**
   * @brief Adds x - placeholder for variable to input string when plotting
   * graph
   *
   * @return ** void
   */
  void push_x_button();
  /**
   * @brief Adds standart operation to input line
   *
   * @return ** void
   */
  void push_button_operation();
  /**
   * @brief Adds unary minus to input line
   *
   * @return ** void
   */
  void push_button_operation_un();
  /**
   * @brief Adds trigonometric or other function to input line
   *
   * @return ** void
   */
  void push_button_operation_fn();
  /**
   * @brief Adds closing bracket to input string
   *
   * @return ** void
   */
  void push_button_close_bracket();
  /**
   * @brief Adds opening bracket to input string
   *
   * @return ** void
   */
  void push_button_open_bracket();

  /**
   * @brief Computes result of input string
   *
   * @return ** void
   */
  void on_pushButton_equal_clicked();

  /**
   * @brief Adds 'e' as EXP to input string for numbers in scientific notation
   *
   * @return ** void
   */
  void on_pushButton_exp_clicked();

  /**
   * @brief Removes last symbol in input line
   *
   * @return ** void
   */
  void on_pushButton_clean_clicked();

  /**
   * @brief Cleans input line
   *
   * @return ** void
   */
  void on_pushButton_all_clean_clicked();

  /**
   * @brief Plots graph
   *
   * @return ** void
   */
  void on_pushButton_graph_clicked();

  /**
   * @brief Creates window for credit
   *
   * @return ** void
   */
  void on_credit_calc_clicked();

  /**
   * @brief Creates window for deposit
   *
   * @return ** void
   */
  void on_deposit_calc_clicked();
};

}  // namespace s21

#endif  // MAINWINDOW_H
