#include <QApplication>
#include <iostream>
#include <string>

#include "mainwindow.h"

int main_view(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}


