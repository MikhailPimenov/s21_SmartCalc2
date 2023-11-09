#include <QApplication>
#include <string>

#include "../controller/controller.h"
#include "mainwindow.h"

namespace s21 {

/**
 * @brief Starts view. Creates application and shows window
 *
 * @param argc
 * @param argv
 * @param controller Controller which is called to call model methods after
 * @return ** int error code. 0 if success, others if failed
 */
int main_view(int argc, 
              char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}

}  // namespace s21