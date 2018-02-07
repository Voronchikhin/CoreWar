#ifndef SPL_NOP_INSTRUCTION__CPP
#define SPL_NOP_INSTRUCTION__CPP

#include <core.hpp>
#include <factory.hpp>
#include <executionContext.hpp>

class SPL_Instruction: public Instruction, public ExecutionContext {
public:
    SPL_Instruction(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode): Instruction(std::string("SPL"), a,b,modifier_,Amode,Bmode) {}
    ~SPL_Instruction()override{}
    void execute(Core &core, int PC)override{
        setCoreRegister(core);
        setThreadPtr(core, PC + 1);
        addThread( core, PC + getRPA(core) );
        return;
    }
};
class NOP_Instruction: public Instruction, public ExecutionContext {
public:
    NOP_Instruction(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode): Instruction(std::string("NOP"),a,b,modifier_,Amode,Bmode) {}
    ~NOP_Instruction()override{}
    void execute(Core &core, int PC)override{
        setCoreRegister(core);
        setThreadPtr(core, PC + 1);
        return;
    }
};
Instruction * createSPL(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode){
    return new SPL_Instruction(a, b, modifier_, Amode, Bmode);
}
Instruction * createNOP(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode){
    return new NOP_Instruction(a, b, modifier_, Amode, Bmode);
}
namespace{
    bool b = Factory::get_instance()->regist3r("SPL",createSPL);
    bool c = Factory::get_instance()->regist3r("NOP",createNOP);
}

#endif