#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QColor>
#include <vector>
#include <QTimer>

class RenderArea: public QWidget
{
  Q_OBJECT
public:
  RenderArea( QWidget * parent, int numberCells);
signals:
  void askCell( unsigned cellNumber);
public slots:
  void paintEvent(QPaintEvent *);
  void setCell(int cellNumber, int warriorNumber );
private slots:
  void cellInfo( QString );
  void paintGrid(QPainter *);
  void paintCells( QPainter *);
  void wheelEvent(QWheelEvent *);
  void mouseDoubleClickEvent(QMouseEvent *);
private:
  unsigned cellsInWidth_ = 25;
  unsigned cellsInHeight_ = 25;
  static const unsigned maxSize = 10000;
  static const unsigned minSize = 100;
  unsigned numberCells_;
  std::vector < QColor > warriors = { "grey", "green", "red", "blue", "yellow"};
  std::vector < int > cells_;

  QColor gridColor = QColor("black");

  void setWidth(unsigned width);
  void setHeight(unsigned height);
};

#endif // RENDERAREA_H
