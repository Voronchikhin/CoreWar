#ifndef MY_MARS_CORE_HPP
#define MY_MARS_CORE_HPP

#include <instruction.hpp>
#include <factory.hpp>
#include <iostream>
#include <memory>
#include <vector>


class Warrior {
public:
  Warrior(int id, int ptr) : ID(id), ptr(ptr) {}
  explicit Warrior(const Warrior &war) : ID(war.ID), ptr(war.ptr) {}
  int ID;
  int ptr;
};



class Core {
public:
  Core();
  explicit Core(int size);
  Core(int size, int Limit);
  Core(int size, int Limit, const std::string &init);
  void insert_warrior(std::vector<std::shared_ptr<Instruction>> &war, int shift,
                      int warrior);
  void setInitialInstruction(Instruction* sample);
  void setInitialInstruction(const std::string & opcode);
  void initCore();
  void tick();
  int getID();
  int getPtr();
  std::string getOpcode(unsigned cell);
private:
  const static int min_distance = 300;
  const static int defaultCoreSize = 8000;
  const unsigned int coreSize   = defaultCoreSize;
  const unsigned int readLimit  = coreSize;
  const unsigned int writeLimit = coreSize;
  std::shared_ptr<Instruction> initInstruction;

  int live_warriors = 0;  // number of live warriors(not a threads!!)
  int warrior_number = 0; // number of active tasks
  int task_ptr = 0;       // address of running instruction
  int warrior_id = 0;     // ID of warrior whose ptr is running
  int task_number = 0;    // number of task which is running

  std::vector<std::shared_ptr<Instruction>> memoryRing;
  std::vector<Warrior> taskList;

  friend class ::ExecutionContext;
  /* registers */
  std::shared_ptr<Instruction> IR;
  std::shared_ptr<Instruction> IRA;
  std::shared_ptr<Instruction> IRB;

  int RPA = coreSize; //
  int WPA = coreSize; //
  int RPB = coreSize; //
  int WPB = coreSize; //
  int PIP = coreSize; //
};

#endif
