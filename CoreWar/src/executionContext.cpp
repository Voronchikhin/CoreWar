#include <executionContext.hpp>

static int Fold(int address, int limit, int size) {
  int result = address % limit;
  if (result > (limit / 2)) {
    result = address += size - limit;
  }
  return result % size;
}
void ExecutionContext::setCoreRegister(Core &core) {
  int Size = core.coreSize;
  core.IR.reset(core.memoryRing[core.task_ptr].get()->clone());
  if (core.IR.get()->aMode == IMMEDIATE) {
    core.RPA = core.WPA = 0;
  } else {
    core.RPA = Fold(getA(getIR(core).get()), core.readLimit, Size);
    core.WPA = Fold(getA(getIR(core).get()), core.writeLimit, Size);
    if ((core.IR.get())->aMode == A_INDIRECT ||
        (core.IR.get())->aMode == A_DECREMENT ||
        (core.IR.get())->aMode == A_INCREMENT) {
      if ((core.IR.get())->aMode == A_DECREMENT) {
        setA(core, (core.task_ptr + core.WPA) % Size,
             getA(core, (core.task_ptr + core.WPA) % Size) + Size - 1);
      }
      if (core.IR.get()->aMode == A_INCREMENT) {
        core.PIP = (core.task_ptr + core.WPA) % Size;
      }
      core.RPA = Fold(core.RPA + getA(core, (core.task_ptr + core.RPA) % Size),
                      core.readLimit, Size);
      core.WPA = Fold(core.WPA + getA(core, (core.task_ptr + core.WPA) % Size),
                      core.writeLimit, Size);
    }
    if (core.IR.get()->aMode == B_INDIRECT ||
        core.IR.get()->aMode == B_DECREMENT ||
        core.IR.get()->aMode == B_INCREMENT) {
      if (core.IR.get()->aMode == B_DECREMENT) {
        setB(core, core.task_ptr + core.WPA,
             (getB(core, (core.task_ptr + core.WPA) % Size) + Size - 1) % Size);
      };
      if (core.IR.get()->aMode == B_INCREMENT) {
        core.PIP = (core.task_ptr + core.WPA) % Size;
      };
      core.RPA = Fold(core.RPA + getB(core, (core.task_ptr + core.RPA) % Size),
                      core.readLimit, Size);
      core.WPA = Fold(core.WPA + getB(core, (core.task_ptr + core.WPA) % Size),
                      core.writeLimit, Size);
    };
  };
  core.IRA.reset(
      core.memoryRing[(core.task_ptr + core.RPA) % Size].get()->clone());
  if (core.IR.get()->aMode == A_INCREMENT) {
    core.memoryRing[core.PIP].get()->aAddress =
        (core.memoryRing[core.PIP].get()->aAddress + 1) % Size;
  } else if (core.IR.get()->aMode == B_INCREMENT) {
    core.memoryRing[core.PIP].get()->bAddress =
        (core.memoryRing[core.PIP].get()->bAddress + 1) % Size;
  }
  if (core.IR.get()->bMode == IMMEDIATE) {
    core.RPB = core.WPB = 0;
  } else {
    core.RPB = Fold(getB(getIR(core).get()), core.readLimit, Size);
    core.WPB = Fold(getB(getIR(core).get()), core.writeLimit, Size);
    if (core.IR.get()->bMode == A_INDIRECT ||
        core.IR.get()->bMode == A_DECREMENT ||
        core.IR.get()->bMode == A_INCREMENT) {
      if (core.IR.get()->bMode == A_DECREMENT) {
        setA(core, (core.task_ptr + core.WPB) % Size,
             getA(core, (core.task_ptr + core.WPB + Size - 1) % Size));
      } else if (core.IR.get()->bMode == A_INCREMENT) {
        core.PIP = (core.task_ptr + core.WPB) % Size;
      }
      core.RPB = Fold(core.RPB + getA(core, (core.task_ptr + core.RPB) % Size),
                      core.readLimit, Size);
      core.WPB = Fold(core.WPB + getA(core, (core.task_ptr + core.WPB) % Size),
                      core.writeLimit, Size);
    };
    if (core.IR.get()->bMode == B_INDIRECT ||
        core.IR.get()->bMode == B_DECREMENT ||
        core.IR.get()->bMode == B_INCREMENT) {
      if (core.IR.get()->bMode == B_DECREMENT) {
        setB(core, core.task_ptr + core.WPB,
             (getB(core, (core.task_ptr + core.WPB) % Size) + Size - 1) % Size);
      } else if (core.IR.get()->bMode == B_INCREMENT) {
        core.PIP = (core.task_ptr + core.WPB) % Size;
      };
      core.RPB = Fold(core.RPB + getB(core, (core.task_ptr + core.RPA) % Size),
                      core.readLimit, Size);
      core.WPB = Fold(core.WPB + getB(core, (core.task_ptr + core.WPA) % Size),
                      core.writeLimit, Size);
    };
  };
  core.IRB.reset(
      core.memoryRing[(core.task_ptr + core.RPB) % Size].get()->clone());
  if (core.IR.get()->bMode == A_INCREMENT) {
    setA(core, core.PIP, getA(core, core.PIP) + 1);
  } else if (core.IR.get()->bMode == B_INCREMENT) {
    setB(core, core.PIP, getB(core, core.PIP) + 1);
  };
}

void ExecutionContext::setCoreInstruction(Core &core, int dst,
                                          std::shared_ptr<Instruction> src) {
  core.memoryRing[dst % core.coreSize] = src;
  return;
}

void ExecutionContext::addThread(Core &core, int ptr) {
  core.taskList.push_back(Warrior(core.warrior_id, ptr % coreSize(core)));
  core.warrior_number++;
}
void ExecutionContext::eraseThread(Core &core) {
  int id = core.warrior_id;
  core.taskList.erase(core.taskList.begin() + core.task_number);
  for (auto &it : core.taskList) {
    if (it.ID == id) {
      core.warrior_number--;
      core.task_number--;
      return;
    }
  }
  core.warrior_number--;
  core.live_warriors--;
}
int ExecutionContext::getRPA(Core &core) { return core.RPA; }
int ExecutionContext::getWPA(Core &core) { return core.WPA; }
int ExecutionContext::getRPB(Core &core) { return core.RPB; }
int ExecutionContext::getWPB(Core &core) { return core.WPB; }
int ExecutionContext::getPIP(Core &core) { return core.PIP; }
const std::shared_ptr<Instruction> ExecutionContext::getIRA(Core &core) {
  return core.IRA;
}
const std::shared_ptr<Instruction> ExecutionContext::getIR(Core &core) {
  return core.IR;
}
const std::shared_ptr<Instruction> ExecutionContext::getIRB(Core &core) {
  return core.IRB;
}
void ExecutionContext::setA(Core &core, int dst, int a) {
  core.memoryRing[dst % core.coreSize].get()->aAddress = a % core.coreSize;
}
void ExecutionContext::setB(Core &core, int dst, int b) {
  core.memoryRing[dst % core.coreSize].get()->bAddress = b % core.coreSize;
}
void ExecutionContext::setA(Instruction *inst, int a) { inst->aAddress = a; }
void ExecutionContext::setB(Instruction *inst, int b) { inst->bAddress = b; }
const int ExecutionContext::coreSize(Core &core) { return core.coreSize; }
const int ExecutionContext::getA(Core &core, int src) {
  return core.memoryRing[src % core.coreSize].get()->aAddress;
}
const int ExecutionContext::getB(Core &core, int src) {
  return core.memoryRing[src % core.coreSize].get()->bAddress;
}
const int ExecutionContext::getA(Instruction *inst) { return inst->aAddress; }
const int ExecutionContext::getB(Instruction *inst) { return inst->bAddress; }
const Modifier ExecutionContext::getModifier(Instruction *inst) {
  return inst->modifier;
}
const Mode ExecutionContext::getAMode(Instruction *inst) { return inst->aMode; }
const Mode ExecutionContext::getBMode(Instruction *inst) { return inst->bMode; }
const Modifier ExecutionContext::getModifier(Core &core, int src) {
  return core.memoryRing[src % core.coreSize]->modifier;
}
void ExecutionContext::addThread(Core &core, int ptr);
void ExecutionContext::eraseThread(Core &core);
const int ExecutionContext::PC(Core &core) { return core.task_ptr; }
const void ExecutionContext::setThreadPtr(Core &core, int ptr_) {
  core.taskList[core.task_number].ptr = ptr_ % core.coreSize;
}

void ExecutionContext :: iterate(Core &core) {

}
bool ExecutionContext :: isEnded ( Core & core ){
   return ( core.live_warriors <= 1 );
}

int ExecutionContext :: winner ( Core & core ){
  if ( isEnded(core) ){
    return core.taskList.begin()->ID;
  }
  return 0;
}
