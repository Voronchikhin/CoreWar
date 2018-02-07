#include "model.h"
#include <string>
CoreWarModel::CoreWarModel(std::vector<std::string> warriors, int size, int numberWarriors):
                           coreSize_(size),
                           iterationLimit_(defaultIterationLimit),
                           iteration_(0),
                           numberWarriors_(numberWarriors),
                           mars_ (new MARS(warriors,size))
                           {
    for(int i = 0; i < coreSize_; ++i){
      cells_.push_back(-1);
    }
}

IterateResult CoreWarModel::iterate(){
    if( iteration_ < iterationLimit_ ){
      iteration_++;
      mars_->iterate();
      return { mars_->warriorId(), mars_->task_ptr()};
    }
    return {0, 0};
}

bool CoreWarModel::isEnded(){
    if( iteration_>=iterationLimit_ ){
        return true;
      }
    return mars_->isEnded();
}

int CoreWarModel::winner(){
    return mars_->winner();
}

void CoreWarModel::addPlayer(std::string player){
   std::ifstream input(player);
   Parser parser(input, coreSize_);
   if ( parser.getWarrior().empty()  ){
     return;
   }
   warriors_.push_back(player);
}

CellInfo CoreWarModel::getCellInfo(int cellNumber){
      return {mars_->getOpcode(cellNumber)};
}
CoreWarModel::~CoreWarModel(){
    if(mars_)
        delete mars_;
}
bool CoreWarModel::isSettingsValid(){
    return ( warriors_.size() == numberWarriors_ );
}
void CoreWarModel::start(){
    if ( isSettingsValid() && mars_!=nullptr ){
        mars_ = new MARS(warriors_, coreSize_, iterationLimit_);
    }
}
