#include "renderarea.h"
#include <iostream>
#include <math.h>

RenderArea::RenderArea(QWidget * parent, int numberCells = 0):
                       QWidget(parent),
                       numberCells_(numberCells)
{
  cellsInHeight_ = 100;
  cellsInWidth_ =  (numberCells/cellsInHeight_ +1 );
  for ( int i = 0; i <numberCells; ++i ){
    cells_.push_back(0);
  }
  setWidth(100);
  setHeight(100);
}

void RenderArea::setWidth(unsigned width){
  setFixedWidth(width);
}
void RenderArea::setHeight(unsigned height){
  setFixedHeight(height);
}

void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(&p);
    paintCells(&p);
}

void RenderArea::paintGrid(QPainter *p)
{
    QRect borders(0, 0, width()-1, height()-1); // borders of the universe
    p->setPen(gridColor);
    double cellWidth = (double)width()/cellsInWidth_; // width of the widget / number of cells at one row
    for(double k = cellWidth; k <= width(); k += cellWidth)
        p->drawLine(k, 0, k, width());
    double cellHeight = (double)height()/cellsInHeight_; // height of the widget / number of cells at one row
    for(double k = cellHeight; k <= height(); k += cellHeight)
        p->drawLine(0, k, height(), k);
    p->drawRect(borders);
}

void RenderArea::paintCells(QPainter *p)
{
    double cellWidth =  (double)width()/cellsInWidth_;
    double cellHeight = (double)height()/cellsInHeight_;

    for( unsigned cell = 0; cell<numberCells_; ++cell ){
        unsigned w = cell%cellsInWidth_;
        unsigned h = cell/cellsInWidth_;

        qreal left = (qreal)(cellWidth*(w)); // margin from left
        qreal top  = (qreal)(cellHeight*(h)); // margin from top
        QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
        p->fillRect(r, QBrush(warriors[cells_[cell]])); // fill cell with brush
    }
}
void RenderArea::setCell(int cellNumber, int warriorNumber){
  std::cout<<cellNumber<<" "<<warriorNumber<<std::endl;
  cells_[cellNumber] = warriorNumber;
  update();
}
void RenderArea:: wheelEvent( QWheelEvent * wheel){
    float scope;
    if( wheel->delta() > 0 ){
      scope = 1.15;
    }
    else {
      scope = 0.75;
    }
    if( width()*scope > maxSize || height()*scope > maxSize ||
        width()*scope < minSize || height()*scope < minSize){
       return;
    }
    this->setFixedSize(width()*scope, height()*scope);
}

void RenderArea::mouseDoubleClickEvent(QMouseEvent *mv){

   int x;
   int y;
   int cellWidth = width() /cellsInWidth_;
   int cellHeight = height() /cellsInHeight_;

   x = (mv->x())/cellWidth;
   y = (mv->y())/cellHeight;

   std::cout << x<<" "<<y<<std::endl;

   emit askCell( y*cellsInWidth_ + x );               //TODO: mb wrong but x andy correct
}

void RenderArea::cellInfo(QString){

}
