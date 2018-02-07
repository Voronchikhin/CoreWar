#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QString>
#include <QTimer>
#include <QColor>
#include <QMessageBox>

#include "scalearea.h"
#include "settingpage.h"
#include "warrior.h"
#include "renderarea.h"
#include <model.h>

class CoreWarController: public QWidget
{
  Q_OBJECT
public:
  CoreWarController(QWidget * parent, ScaleArea* scAr, RenderArea* rAr,SettingPage* sP);
  ~CoreWarController();
signals:
  void cellsChanged( int cellNumber, int warriorNumber);

  void errorManage(QString error);
  void comandTag(QString tag);


public slots:
  void iterate();

  void fileChanged(int warriorIndex, QString fileName);
  void tagChanged(int warriorsIndex, QString tag );

  void numberWarriors(int numberWarriors);
  void startButton();

  void getComandTag(unsigned cellNumber);

private:

  QTimer* timer_;
  const static int minInterval = 50;
  const static int maxInterval = 2000;
  unsigned interval_;                 // msec between iterations

  Model * model_;
  unsigned warriorsCount;
  unsigned coreSize_;
  bool isValid();
  void winner(QString winnerInfo);

  std::vector<QWarrior> warriors;

  SettingPage* setPage_;
  RenderArea* view_;
  QMessageBox* message_;
  ScaleArea* scArea_;
};

#endif // CONTROLLER_H
