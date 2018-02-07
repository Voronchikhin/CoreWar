#ifndef SCALEAREA_H
#define SCALEAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QScrollBar>

namespace Ui {
  class ScaleArea;
}

class ScaleArea : public QWidget
{
  Q_OBJECT

public:
  ScaleArea(QWidget *parent = 0);
  ~ScaleArea();
  QWidget* widget();
public slots:
  void setWidget(QWidget* widget);

  void setMaxH(unsigned maxH);
  void setMaxW(unsigned maxW);
  void setMinH(unsigned minH);
  void setMinW(unsigned minW);

  void setSize(unsigned w, unsigned h);
private slots:
  void mouseMoveEvent(QMouseEvent *);
  void wheelEvent(QWheelEvent *);
private:
  Ui::ScaleArea *ui;
  QWidget * item_;
  unsigned width_ = 500;
  unsigned height_ = 500;
  unsigned maxH_ = 6000;
  unsigned maxW_ = 6000;
  unsigned minH_ = 15;
  unsigned minW_ = 15;
  float scopeFactor_ = 1.15;
};

#endif // SCALEAREA_H
