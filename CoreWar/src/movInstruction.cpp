#ifndef MOV_INSTRUCTION__CPP
#define MOV_INSTRUCTION__CPP

#include <instruction.hpp>
#include <core.hpp>
#include <factory.hpp>
#include <executionContext.hpp>

class MOV_Instruction: public Instruction, public ExecutionContext {
public:
    MOV_Instruction(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode): Instruction(std::string("MOV"),a,b,modifier_,Amode,Bmode) {}
    ~MOV_Instruction()override{}
    void execute(Core &core, int PC)override{
        setCoreRegister(core);
        switch (getModifier(getIR(core).get())){
            case A:
                setA( core, PC + getWPB(core), getA(getIRA(core).get()));
                break;
            case B:
                setB( core, PC + getWPB(core), getB(getIRA(core).get())  );
                break;
            case AB:
                setB( core, PC + getWPB(core), getA(getIRA(core).get())  );
                break;
            case BA:
                setA( core, PC + getWPB(core), getB(getIRA(core).get())  );
                break;
            case F:
                setA( core, PC + getWPB(core), getA(getIRA(core).get())  );
                setB( core, PC + getWPB(core), getB(getIRA(core).get())  );
                break;
            case X:
                setA( core, PC + getWPB(core), getB(getIRA(core).get())  );
                setB( core, PC + getWPB(core), getA(getIRA(core).get())  );
                break;
            case I:
                setCoreInstruction(core, PC + getWPB(core), std::shared_ptr<Instruction>(getIRA(core)->clone()));      
                break;
            default:
                return;
        }
        setThreadPtr(core, this->PC(core)+1 );
        return;
    }
};
Instruction * createMOV(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode){
    return new MOV_Instruction(a, b, modifier_, Amode, Bmode);
}
namespace{
    bool b = ::Factory::get_instance()->regist3r("MOV",createMOV);
}

#endif