#include <QApplication>
#include <iostream>
#include <string>

#include "mainwindow.h"
#include "../controller/controller.h"

namespace s21 {


/**
 * @brief Starts view. Creates application and shows window
 * 
 * @param argc 
 * @param argv 
 * @param controller Controller which is called to call model methods after
 * @return ** int error code. 0 if success, others if failed
 */
int main_view(int argc, char *argv[], Controller* controller) {
  QApplication a(argc, argv);
  MainWindow w(nullptr, controller);
  w.show();
  return a.exec();
}

} // namespace s21