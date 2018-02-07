#include "mainwindow.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  CoreWarController contr( nullptr, w.getScArea(),w.rArea(),w.sPAge() );
  w.show();
  return a.exec();
}
