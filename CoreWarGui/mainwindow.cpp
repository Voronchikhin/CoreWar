#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <qbuttongroup.h>
#include "settingpage.h"
#include "scalearea.h"
#include "renderarea.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  nextPage(nullptr)
{
  ui->setupUi(this); 
  scArea = ui->scaleArea;
  rArea_ = new RenderArea(this, 8192);
  setPage = ui->settingPage;
  ui->settingPage->hide();
  ui->caravanPage->hide();
  ui->bonus->hide();
  scArea->hide();
}

MainWindow::~MainWindow()
{
  delete ui;
  delete rArea_;
}

ScaleArea* MainWindow::getScArea(){
  return scArea;
}

RenderArea* MainWindow::rArea(){
  return rArea_;
}

SettingPage* MainWindow::sPAge(){
  return setPage;
}

void MainWindow::on_nextButton_clicked()
{
  if( nextPage ){
    ui->bonus->hide();
    ui->nextButton->hide();
    ui->CoreWar->hide();
    nextPage->show();
  }
}

void MainWindow::on_CoreWar_clicked()
{
  nextPage = ui->settingPage;
}

void MainWindow::on_bonus_clicked()
{
  nextPage = ui->caravanPage;
}
void MainWindow::mousePressEvent(QMouseEvent *event){
  static int counter = 0;
  counter++;
  if(counter >= 7 && !nextPage){
    ui->bonus->show();
  }
}
