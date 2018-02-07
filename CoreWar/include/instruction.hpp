#ifndef INSTRUCTION_HPP_CORE_WAR
#define INSTRUCTION_HPP_CORE_WAR

#include <string>
#include <iostream>

class Instruction;
class ExecutionContext;

class Core;
enum Modifier { A, B, AB, BA, F, X, I };

enum Mode {
  IMMEDIATE = '#',
  DIRECT = '$',
  A_INDIRECT = '*',
  B_INDIRECT = '@',
  A_DECREMENT = '{',
  B_DECREMENT = '<',
  A_INCREMENT = '}',
  B_INCREMENT = '>'
};

class Instruction {
public:
  Instruction();
  Instruction(std::string opcode, int a, int b, Modifier modifier_,
              Mode Amode, Mode Bmode);
  virtual void execute(Core &core, int PC);
  virtual ~Instruction();
  virtual Instruction* clone();
  std::string& opcode();
  std::string toString();
protected:
    const static Modifier defMod = A;
  const static Mode defMode = IMMEDIATE;
  std::string opcode_;
  Modifier modifier = defMod;
  Mode aMode = defMode, bMode = defMode;

  int aAddress = 0;
  int bAddress = 0;
  friend class ::ExecutionContext;
};




#endif