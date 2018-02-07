#include "scalearea.h"
#include "ui_scalearea.h"

ScaleArea::ScaleArea(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ScaleArea)
{
  ui->setupUi(this);
  ui->scrollArea;
}

ScaleArea::~ScaleArea()
{
  delete ui;
}

void ScaleArea::setMaxH(unsigned maxH){
  maxH_ = maxH;
}

void ScaleArea::setMaxW(unsigned maxW){
  maxW_ = maxW;
}

void ScaleArea::setMinH(unsigned minH){
  minH_ = minH;
}

void ScaleArea::setMinW(unsigned minW){
  minW_ = minW;
}

void ScaleArea::mouseMoveEvent(QMouseEvent *event){
  static int lastX = event->x();
  static int lastY = event->y();

  //int dx = (lastX - event->x() > 10 || lastX - event->x() < -10)?(lastX - event->x()):(0);
  //int dy = (lastY - event->y() > 10 || lastY - event->y() < -10)?(lastY - event->y()):(0);



  int dx = lastX - event->x();
  int dy = lastY - event->y();

  lastX = event->x();
  lastY  = event->y();

  ui->scrollArea->verticalScrollBar()->setValue( ui->scrollArea->verticalScrollBar()->value() + dy );
  ui->scrollArea->horizontalScrollBar()->setValue( ui->scrollArea->horizontalScrollBar()->value() + dx );
  update();
}

void ScaleArea::wheelEvent(QWheelEvent *wheel){
  wheel->ignore();
}

void ScaleArea::setSize(unsigned w, unsigned h){
  height_ = ( h<maxH_ && h>minH_)?(h):(item_->height());
  width_ = ( w<maxW_  && w>minW_)?(w):(item_->width());


  item_->setFixedHeight(height_);
  item_->setFixedWidth(width_);
}


QWidget* ScaleArea::widget(){
  return item_;
}
void ScaleArea::setWidget(QWidget *widget){
  item_ = widget;
  item_->setFixedHeight(height_);
  item_->setFixedWidth(width_);
  ui->scrollArea->setWidget(item_);
}
