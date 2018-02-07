#ifndef ARITHEMTIC_INSTRUCTION_CPP
#define ARITHEMTIC_INSTRUCTION_CPP

#include <core.hpp>
#include <factory.hpp>
#include <executionContext.hpp>
template <class P> class Arith : public Instruction, public ExecutionContext {
public:
  Arith(int (*op_)(int, int), int a, int b, Modifier modifier_,
        Mode Amode, Mode Bmode, std::string opcode)
      : op(op_), ::Instruction(opcode,a, b, modifier_, Amode, Bmode) {}
  ~Arith() override {}
  void execute(Core &core, int PC) override {
    setCoreRegister(core);
    int IRAA = getA(getIRA(core).get());
    int IRBA = getA(getIRB(core).get());
    int IRAB = getB(getIRA(core).get());
    int IRBB = getB(getIRB(core).get());
    int core_Size = coreSize(core);
    switch (getModifier(getIR(core).get())) {
    case A:
      if (P()(getA(getIRA(core).get()))) {
        setA(core, (PC + getWPB(core)) % core_Size, op(IRBA, IRAA) % core_Size);
        break;
      } else {
        eraseThread(core);
      }
    case B:
      if (P()(getB(getIRA(core).get()))) {
        setB(core, (PC + getWPB(core)) % core_Size, op(IRBB, IRAB) % core_Size);
        break;
      } else {
        eraseThread(core);
      }
    case AB:
      if (P()(getA(getIRA(core).get()))) {
        setB(core, (PC + getWPB(core)) % core_Size, op(IRBA, IRAB) % core_Size);
      } else {
        eraseThread(core);
      }
      break;
    case BA:
      if (P()(getB(getIRA(core).get()))) {
        setA(core, (PC + getWPB(core)) % core_Size, op(IRBB, IRAA) % core_Size);
      } else {
        eraseThread(core);
      }
      break;
    case F:
    case I:
      if (P()(getA(getIRA(core).get())))
        setA(core, (PC + getWPB(core)) % core_Size, op(IRBA, IRAA) % core_Size);
      if (P()(getA(getIRA(core).get())))
        setB(core, (PC + getWPB(core)) % core_Size, op(IRBB, IRAB) % core_Size);
      if (!P()(getA(getIRA(core).get())) || !P()(getB(getIRA(core).get()))) {
        eraseThread(core);
      }
      break;
    case X:
      if (P()(getA(getIRA(core).get())))
        setB(core, (PC + getWPB(core)) % core_Size, op(IRBA, IRAB) % core_Size);
      if (P()(getB(getIRA(core).get())))
        setA(core, (PC + getWPB(core)) % core_Size, op(IRBB, IRAA) % core_Size);
      if (!P()(getA(getIRA(core).get())) || !P()(getB(getIRA(core).get()))) {
        eraseThread(core);
      }
      break;
    default:
      return;
    }
    setThreadPtr(core, PC + 1);
    return;
  }

private:
  int (*op)(int a, int b);
};
class True{
public:
  bool operator()(int a){return true;}
};
class notZero{
public:
  bool operator() (int a){ return a!=0; }
};
Instruction *createADD(int a, int b, Modifier modifier_, Mode Amode,
                       Mode Bmode) {
  return new Arith <True> ([](int a, int b) -> int { return a + b; }, a, b, modifier_,
                   Amode, Bmode, std::string("ADD"));
}
Instruction *createSUB(int a, int b, Modifier modifier_, Mode Amode,
                       Mode Bmode) {
  return new Arith <True> ([](int a, int b) -> int { return a - b; }, a, b, modifier_,
                   Amode, Bmode, std::string("SUB"));
}
Instruction *createMUL (int a, int b, Modifier modifier_, Mode Amode,
                       Mode Bmode) {
  return new Arith<True> ([](int a, int b) -> int { return a * b; }, a, b, modifier_,
                   Amode, Bmode, std::string("MUL"));
}
Instruction *createDIV (int a, int b, Modifier modifier_, Mode Amode,
                       Mode Bmode) {
  return new Arith<notZero> ([](int a, int b) -> int { return a / b; }, a, b, modifier_,
                   Amode, Bmode, std::string("DIV"));
}
Instruction *createMOD (int a, int b, Modifier modifier_, Mode Amode,
                       Mode Bmode) {
  return new Arith<notZero> ([](int a, int b) -> int { return a % b; }, a, b, modifier_,
                   Amode, Bmode, std::string("MOD"));
}
namespace {
bool b = Factory::get_instance()->regist3r("ADD", createADD);
bool c = Factory::get_instance()->regist3r("SUB", createSUB);
bool d = Factory::get_instance()->regist3r("MUL", createMUL);
bool e = Factory::get_instance()->regist3r("DIV", createDIV);
bool f = Factory::get_instance()->regist3r("MOD", createMOD);
}

#endif
