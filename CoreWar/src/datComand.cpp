#ifndef DAT_INSTRUCTION__CPP
#define DAT_INSTRUCTION__CPP

#include <core.hpp>
#include <factory.hpp>
#include <executionContext.hpp>

class DAT_Instruction: public Instruction, public ExecutionContext {
public:
    DAT_Instruction(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode): Instruction(std::string("DAT"), a,b,modifier_,Amode,Bmode) {}
    ~DAT_Instruction()override{}
    void execute(Core &core, int PC)override{
        setCoreRegister(core);
        eraseThread(core);
        return;
    }
};
Instruction * createDAT(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode){
    return new DAT_Instruction(a, b, modifier_, Amode, Bmode);
}
namespace{
    bool b = Factory::get_instance()->regist3r("DAT",createDAT);
}

#endif