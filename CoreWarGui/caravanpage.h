#ifndef CARAVANPAGE_H
#define CARAVANPAGE_H

#include <QWidget>
#include <QGraphicsView>

#include "scalearea.h"
#include "renderarea.h"

namespace Ui {
  class CaravanPage;
}

class CaravanPage : public QWidget
{
  Q_OBJECT

public:
  explicit CaravanPage(QWidget *parent = 0);
  ~CaravanPage();

private slots:
  void on_checkBox_stateChanged(int arg1);

  void on_checkBox_2_stateChanged(int arg1);

  void on_checkBox_3_stateChanged(int arg1);

  void on_easterEGG_clicked();

private:
  Ui::CaravanPage *ui;
  int sum = 0;
  int realSum = 5;
  ScaleArea * sc;
};

#endif // CARAVANPAGE_H
