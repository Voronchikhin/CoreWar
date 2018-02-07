#include <instruction.hpp>
#include <factory.hpp>
#include <executionContext.hpp>

Instruction::  Instruction()
      :  opcode_("INST") {}
Instruction:: Instruction(std::string opcode, int a, int b, Modifier modifier_,
              Mode Amode, Mode Bmode)
      : aAddress(a), bAddress(b), modifier(modifier_), aMode(Amode),
        opcode_(opcode), bMode(Bmode) {}
void Instruction :: execute(Core &core, int PC) {}
Instruction :: ~Instruction() {}

Instruction *Instruction::clone() {
  return Factory::get_instance()->create(opcode_, modifier, aMode, bMode,
                                         aAddress, bAddress);
}

std::string& Instruction:: opcode() {
    return opcode_; 
}

std::string Instruction::toString(){  
  std::string os;
    os = os + opcode_
       + " "
       + static_cast<char> ( aMode)
       + std::to_string (aAddress)
       + " "
       + static_cast<char> (bMode)
       + std::to_string (bAddress)
       + '\n'; 
    return os;  
}  

