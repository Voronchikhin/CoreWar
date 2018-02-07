#ifndef JMP_INSTRUCTION__CPP
#define JMP_INSTRUCTION__CPP

#include <core.hpp>
#include <factory.hpp>
#include <executionContext.hpp>

class JMP_Instruction : public Instruction, public ExecutionContext {
public:
  JMP_Instruction(int a, int b, Modifier modifier_, Mode Amode,
                  Mode Bmode)
      : Instruction(std::string("JMP"), a, b, modifier_, Amode, Bmode) {}
  ~JMP_Instruction() override {}
  void execute(Core &core, int PC) override {
    setCoreRegister(core);
    setThreadPtr(core, PC + getRPA(core));
    return;
  }
};
class JMZ_Instruction : public Instruction, public ExecutionContext {
public:
  JMZ_Instruction(int a, int b, Modifier modifier_, Mode Amode,
                  Mode Bmode)
      : Instruction(std::string("JMZ"),a, b, modifier_, Amode, Bmode) {}
  ~JMZ_Instruction() override {}
  void execute(Core &core, int PC) override {
    setCoreRegister(core);
    switch (getModifier(getIR(core).get())) {
    case A:
    case BA:
      if (getA(getIRB(core).get()) == 0) {
        setThreadPtr(core, PC + getRPA(core));
      } else {
        setThreadPtr(core, this->PC(core) + 1);
      }
      return;
    case B:
    case AB:
      if (getB(getIRB(core).get()) == 0) {
        setThreadPtr(core, PC + getRPA(core));
      } else {
        setThreadPtr(core, this->PC(core) + 1);
      }
    case F:
    case X:
    case I:
      if ((getA(getIRB(core).get()) == 0) && (getB(getIRB(core).get()) == 0)) {
        setThreadPtr(core, PC + getRPA(core));
      } else {
        setThreadPtr(core, this->PC(core) + 1);
      }
    }
    setThreadPtr(core, PC + getRPA(core));
    return;
  }
};
class JMN_Instruction : public Instruction, public ExecutionContext {
public:
  JMN_Instruction(int a, int b, Modifier modifier_, Mode Amode,
                   Mode Bmode)
      : Instruction(std::string("JMN"),a, b, modifier_, Amode, Bmode) {}
  ~JMN_Instruction() override {}
  void execute(Core &core, int PC) override {
    setCoreRegister(core);
    switch (getModifier(getIR(core).get())) {
    case A:
    case BA:
      if (getA(getIRB(core).get()) != 0) {
        setThreadPtr(core, PC + getRPA(core));
      } else {
        setThreadPtr(core, this->PC(core) + 1);
      }
      return;
    case B:
    case AB:
      if (getB(getIRB(core).get()) != 0) {
        setThreadPtr(core, PC + getRPA(core));
      } else {
        setThreadPtr(core, this->PC(core) + 1);
      }
    case F:
    case X:
    case I:
      if ((getA(getIRB(core).get()) != 0) && (getB(getIRB(core).get()) != 0)) {
        setThreadPtr(core, PC + getRPA(core));
      } else {
        setThreadPtr(core, this->PC(core) + 1);
      }
    }
    setThreadPtr(core, PC + getRPA(core));
    return;
  }
};
class DJN_Instruction : public Instruction, public ExecutionContext {
public:  
    DJN_Instruction(int a, int b, Modifier modifier_, Mode Amode,
                   Mode Bmode)
      : Instruction(std::string("DJN"),a, b, modifier_, Amode, Bmode) {}
  ~DJN_Instruction() override {}
  void execute(Core &core, int PC) override {
    setCoreRegister(core);
    int pc = ExecutionContext:: PC(core);
    switch (getModifier(getIR(core).get())) {
    case A:
    case BA:
        setA ( core, pc + getWPB(core), getA( core, pc + getWPB(core) ) + coreSize(core)-1);
        setA ( getIRB(core).get(), getA( getIRB(core).get() ) + coreSize(core)-1);
      if (getA(getIRB(core).get()) != 0) {
        setThreadPtr(core, getRPA(core));
      } else {
        setThreadPtr(core, this->PC(core) + 1);
      }
      return;
    case B:
    case AB:
        setB ( core, pc + getWPB(core), getB( core, pc + getWPB(core) ) + coreSize(core)-1);
        setB ( getIRB(core).get(), getB( getIRB(core).get() ) + coreSize(core)-1);
      if (getB(getIRB(core).get()) != 0) {
        setThreadPtr(core, getRPA(core));
      } else {
        setThreadPtr(core, this->PC(core) + 1);
      }
    case F:
    case X:
    case I:
    setA ( core, pc + getWPB(core), getA( core, pc + getWPB(core) ) + coreSize(core)-1);
    setA ( getIRB(core).get(), getA( getIRB(core).get() ) + coreSize(core)-1);
    setB ( core, pc + getWPB(core), getB( core, pc + getWPB(core) ) + coreSize(core)-1);
    setB ( getIRB(core).get(), getB( getIRB(core).get() ) + coreSize(core)-1);
      if ((getA(getIRB(core).get()) != 0) && (getB(getIRB(core).get()) != 0)) {
        setThreadPtr(core, getRPA(core));
      } else {
        setThreadPtr(core, this->PC(core) + 1);
      }
    }
    setThreadPtr(core, getRPA(core));
    return;
  }
};



Instruction *createJMP(int a, int b, Modifier modifier_, Mode Amode,
                       Mode Bmode) {
  return new JMP_Instruction(a, b, modifier_, Amode, Bmode);
}
Instruction *createJMZ(int a, int b, Modifier modifier_, Mode Amode,
                       Mode Bmode) {
  return new JMZ_Instruction(a, b, modifier_, Amode, Bmode);
}
Instruction *createJMN(int a, int b, Modifier modifier_, Mode Amode,
                       Mode Bmode) {
  return new JMN_Instruction(a, b, modifier_, Amode, Bmode);
}
Instruction *createDJN(int a, int b, Modifier modifier_, Mode Amode,
                       Mode Bmode) {
  return new DJN_Instruction(a, b, modifier_, Amode, Bmode);
}
namespace {
bool b = Factory::get_instance()->regist3r("JMP", createJMP);
bool c = Factory::get_instance()->regist3r("JMZ", createJMZ);
bool d = Factory::get_instance()->regist3r("JMN", createJMN);
bool e = Factory::get_instance()->regist3r("DJN", createDJN);
}

#endif