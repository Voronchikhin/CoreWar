#include <fstream>
#include "controller.h"
#include <parser.hpp>
#include "model.h"


CoreWarController::CoreWarController(QWidget * parent, ScaleArea* scAr, RenderArea* rAr,SettingPage* sP):
                                     timer_(new QTimer(this)),
                                     model_(nullptr),
                                     setPage_(sP),
                                     view_(rAr),
                                     scArea_(scAr),
                                     message_(new QMessageBox(this)),
                                     interval_(10),
                                     warriorsCount(2),
                                     coreSize_(8192)
{
  timer_->start();
  timer_->setInterval(interval_);
  connect( timer_, SIGNAL(timeout()), this, SLOT(iterate()) );
  connect( this, SIGNAL(cellsChanged(int,int)), view_, SLOT(setCell(int,int)) );
  connect( this, SIGNAL(comandTag(QString)), view_, SLOT(cellInfo(QString)) );
  connect( view_, SIGNAL(askCell(uint)), this, SLOT(getComandTag(uint)));
  connect( setPage_, SIGNAL(fileChanged(int,QString)), this, SLOT(fileChanged(int,QString)));
  connect( setPage_, SIGNAL(numberWarriors(int)), this, SLOT(numberWarriors(int)) );
  connect( setPage_, SIGNAL(startButton()), this, SLOT(startButton()) );
  connect( setPage_, SIGNAL(tagChanged(int,QString)), this, SLOT(tagChanged(int,QString)) );

  scArea_->setWidget(view_);
  scArea_->hide();
  setPage_->hide();
  QWarrior tie(std::string("qwerty.txt"),std::string("AZINO 777"),QColor("grey"));
  for( int i = 0; i <= 4; ++i ){
    warriors.push_back(tie);
  }
}

void CoreWarController::iterate(){
  if( !model_ ){
    return;
  }
  IterateResult res;
  if( model_->isEnded() ){
      winner( QString::fromStdString(warriors[model_->winner()].tag_) );
      timer_->stop();
  }
  res = model_->iterate();
  int warN = res.warriorNumber;
  int cellN = res.cellNumber;
  emit cellsChanged(cellN, warN);
}

void CoreWarController::fileChanged(int warriorIndex, QString fileName){
  warriors[warriorIndex].fileName_ = fileName.toStdString();
}

void CoreWarController::tagChanged(int warriorsIndex, QString tag){
  warriors[warriorsIndex].tag_ = tag.toStdString();
}

void CoreWarController::numberWarriors(int numberWarriors){
  warriorsCount = numberWarriors;
}

void CoreWarController::startButton(){
  if ( isValid() ){
    std::vector<std::string> wars;
    for( int i = 1; i <=warriorsCount; ++i ){
      wars.push_back( warriors[i].fileName_ );
    }
    model_ = new CoreWarModel(wars,coreSize_, warriorsCount);
    model_->start();
    setPage_->hide();
    scArea_->show();
  }
  else{
    message_->setText(QString("wrong file"));
    message_->show();
  }
}
void CoreWarController::getComandTag(unsigned cellNumber){
  std::cout<<model_->getCellInfo(cellNumber).opcode_<<std::endl;
  message_->setText(QString::fromStdString(model_->getCellInfo(cellNumber).opcode_));
  message_->show();
  emit comandTag( QString::fromStdString(model_->getCellInfo(cellNumber).opcode_) );
}

CoreWarController::~CoreWarController(){
  delete message_;
}

bool CoreWarController::isValid(){

  for( int i = 1; i <=warriorsCount; ++i){
      std::ifstream in(warriors[i].fileName_);
      Parser pars(in, coreSize_);
      if ( pars.getWarrior().empty() ){
        return false;
      }
  }
  return true;
}
void CoreWarController::winner(QString winnerInfo){
  message_->setText(winnerInfo);
  message_->setWindowTitle(QString("game end"));
  message_->show();
}


























