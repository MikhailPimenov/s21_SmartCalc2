#include <QApplication>
#include <iostream>
#include <string>

#include "mainwindow.h"
#include "../controller/controller.h"

namespace s21 {

int main_view(int argc, char *argv[], Controller* controller) {
  QApplication a(argc, argv);
  MainWindow w(nullptr, controller);
  w.show();
  return a.exec();
}

} // namespace s21