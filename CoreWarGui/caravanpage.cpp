#include "caravanpage.h"
#include "ui_caravanpage.h"

CaravanPage::CaravanPage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CaravanPage)
{
  ui->setupUi(this);
  ui->widget_2->hide();
  ui->easterEGG->hide();
  sc = ui->widget_2;
  ui->graphicsView->hide();
}

CaravanPage::~CaravanPage()
{
  delete ui;
}

void CaravanPage::on_checkBox_stateChanged(int arg1)
{
  if( !arg1 ){
      sum--;
      return;
  }
  if( sum == 2 ){
    realSum++;
    ui->checkBox_3->click();
    if(realSum >= 25){
        ui->checkBox_3->click();
        return;
    }
  }
  ui->easterEGG->show();
  sum++;
}

void CaravanPage::on_checkBox_2_stateChanged(int arg1)
{
  if( !arg1 ){
      sum--;
      return;
  }
  if( sum == 2 ){
    realSum++;
    ui->checkBox->click();
    if(realSum >= 19){
        ui->checkBox->click();
        return;
    }
  }
  ui->easterEGG->show();
  sum++;
}

void CaravanPage::on_checkBox_3_stateChanged(int arg1)
{
  if( !arg1 ){
      sum--;
      return;
  }
  if( sum == 2 ){
    realSum++;
    ui->checkBox_2->click();
    if(realSum >=19){
        ui->checkBox_2->click();
        return;
    }
  }
  ui->easterEGG->show();
  sum++;
}

void CaravanPage::on_easterEGG_clicked()
{
    if( ui->checkBox->isChecked() &&
        ui->checkBox_2->isChecked()&&
        ui->checkBox_3->isChecked() ) {
        QGraphicsScene *scene = new QGraphicsScene;
        scene->addPixmap(QPixmap("../test.jpeg"));
        scene->addText("test");
        ui->graphicsView->setScene(scene);
        sc->setWidget(ui->graphicsView);
    }
    sc->show();
}
