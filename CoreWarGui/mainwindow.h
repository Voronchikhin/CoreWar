#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"
#include "renderarea.h"
#include <QMouseEvent>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ScaleArea* getScArea();
  RenderArea* rArea();
  SettingPage* sPAge();

  ~MainWindow();

private slots:

  void on_nextButton_clicked();

  void on_CoreWar_clicked();

  void on_bonus_clicked();
private slots:
  void mousePressEvent(QMouseEvent *);

private:
  Ui::MainWindow *ui;
  QWidget* nextPage;
  ScaleArea* scArea;
  RenderArea* rArea_;
  SettingPage* setPage;
};

#endif // MAINWINDOW_H
