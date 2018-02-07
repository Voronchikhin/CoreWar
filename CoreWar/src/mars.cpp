#include <mars.hpp>

MARS :: MARS (const std::vector<std::string> &war):core(defaultCoreSize) {
    core.setInitialInstruction("DAT");

  for (unsigned i = 0; i < war.size(); ++i) {
    std::cout<<"load warrior"<<war[i]<<std::endl;
    std::ifstream in(war[i]);
    Parser parser(in, coreSize);
    std::vector<std::shared_ptr<Instruction>> warior = parser.getWarrior();
    unsigned shift = parser.getShift();
    core.insert_warrior(warior,shift, i);
    in.close();
  }
}

MARS :: MARS (const std::vector<std::string> &war, const int size):core(size) {
    core.setInitialInstruction("DAT");

  for (unsigned i = 0; i < war.size(); ++i) {
    std::ifstream in(war[i]);
    Parser parser(in, coreSize);
    std::vector<std::shared_ptr<Instruction>> warior = parser.getWarrior();
    unsigned shift = parser.getShift();
    core.insert_warrior(warior,shift, i);
    in.close();
  }
}

MARS :: MARS (const std::vector<std::string> &war, const int size, const int Limit):core(size),
                  iterationLimit(Limit){
    core.setInitialInstruction("DAT");

  for (unsigned i = 0; i < war.size(); ++i) {
    std::ifstream in(war[i]);
    Parser parser(in, coreSize);
    std::vector<std::shared_ptr<Instruction>> warior = parser.getWarrior();
    unsigned shift = parser.getShift();
    core.insert_warrior(warior,shift, i);
    in.close();
  }
}

void MARS::iterate(){
  core.tick();
}

int MARS::task_ptr(){
  return core.getPtr();
}

int MARS::warriorId(){
  return core.getID();
}

std::string MARS::getOpcode(unsigned cell){
  return core.getOpcode(cell);
}

int MARS::winner(){
  return ExecutionContext::winner(core);
}
bool MARS::isEnded(){
  return ExecutionContext::isEnded(core);
}
