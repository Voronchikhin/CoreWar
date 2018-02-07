#ifndef EXECUTION_CONTEXT_CORE_WAR
#define EXECUTION_CONTEXT_CORE_WAR

#include <core.hpp>



class ExecutionContext {
protected:
  void setCoreRegister(Core &core);
  int getRPA(Core &core);
  int getWPA(Core &core);
  int getRPB(Core &core);
  int getWPB(Core &core);
  int getPIP(Core &core);

  const std::shared_ptr<Instruction> getIRA(Core &core);
  const std::shared_ptr<Instruction> getIR(Core &core);
  const std::shared_ptr<Instruction> getIRB(Core &core);
  void setCoreInstruction(Core &core, int dst,
                          std::shared_ptr<Instruction> src);
  void setA(Core &core, int dst, int a);
  void setB(Core &core, int dst, int b);
  void setA(Instruction *inst, int a);
  void setB(Instruction *inst, int b);
  const int coreSize(Core &core);
  const int getA(Core &core, int src);
  const int getB(Core &core, int src);
  const int getA(Instruction *inst);
  const int getB(Instruction *inst);
  const Modifier getModifier(Instruction *inst);
  const Mode getAMode(Instruction *inst);
  const Mode getBMode(Instruction *inst);
  const Modifier getModifier(Core &core, int src);
  void addThread(Core &core, int ptr);
  void eraseThread(Core &core);
  const int PC(Core &core);
  const void setThreadPtr(Core &core, int ptr_);
  bool isEnded(Core & core);
  int winner( Core &  core);
  void iterate (Core &core);

};


#endif
