#include <core.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <exception>

Core::Core(){
  memoryRing.reserve(coreSize);
  setInitialInstruction(std::string("DAT"));
  initCore();
}

Core::Core(int size) : readLimit(size), writeLimit(size), coreSize(size) {
  memoryRing.reserve(coreSize);
  setInitialInstruction(std::string("DAT"));
  initCore();
}

Core::Core(int size, int Limit)
    : readLimit(Limit), writeLimit(Limit), coreSize(size) {
  memoryRing.reserve(coreSize);
  setInitialInstruction(std::string("DAT"));
  initCore();
}
Core::Core(int size, int Limit, const std::string &init)
: readLimit(Limit), writeLimit(Limit), coreSize(size) {
  memoryRing.reserve(coreSize);
  setInitialInstruction(init);
  initCore();
}
int Core::getID(){
  return warrior_id;
}
int Core::getPtr(){
  return task_ptr;
}
std::string Core::getOpcode(unsigned cell){
  return memoryRing[cell%coreSize].get()->opcode();
}

void Core::insert_warrior(std::vector<std::shared_ptr<Instruction>> &war,
                          int shift, int warrior) {
  live_warriors++;
  warrior_number++;
  static int last_pos = 0;
  int startPos = (last_pos + (min_distance + rand()) % coreSize) % coreSize;
  int i = startPos;
  for (int j = 0; war.begin() + j != war.end(); j++) {
    memoryRing[i % coreSize] = std::move(war[j]);
    i++;
  }
  last_pos = i % coreSize;
  taskList.push_back(Warrior(live_warriors, startPos + shift));
}
void Core::initCore() {
  for (unsigned i = 0; i < coreSize; ++i) {
    memoryRing.push_back( std::shared_ptr<Instruction>( initInstruction->clone() ) );
  }
}

void Core::setInitialInstruction( Instruction * sample ){
  initInstruction.reset(sample);
}
void Core::setInitialInstruction( const std::string &opcode ){
  Instruction *tmp = ::Factory::get_instance()->create( opcode, I, IMMEDIATE, IMMEDIATE, 0, 0 );
  initInstruction.reset(tmp);
}
void Core::tick() {
  task_ptr = taskList[task_number].ptr;
  warrior_id = taskList[task_number].ID;

  memoryRing[task_ptr].get()->execute(*this, task_ptr);
  std::cout<<memoryRing[task_ptr].get()->opcode()<<std::endl;
  if (task_number >= warrior_number - 1) {
    task_number = 0;
  } else {
    task_number++;
  }
}


