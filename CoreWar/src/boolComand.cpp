#ifndef CMP_COMAND_CPP_COREWAR
#define CMP_COMAND_CPP_COREWAR

#include <core.hpp>
#include <factory.hpp>
#include <executionContext.hpp>


class CMP_Instruction: public Instruction, public ExecutionContext{
public:
    CMP_Instruction(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode, std::string opcode): Instruction(opcode,a,b,modifier_,Amode,Bmode) {}
    ~CMP_Instruction()override{}
    void execute(Core &core, int PC)override{
        setCoreRegister(core);
        switch (getModifier(getIR(core).get())){
            case A:
                if ( getA( getIRA(core).get() )==getA( getIRB(core).get() ) ){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case B:
                if ( getB( getIRA(core).get() )==getB( getIRB(core).get() ) ){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case AB:
                if ( getA( getIRA(core).get() )==getB( getIRB(core).get() ) ){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case BA:
                if ( getB( getIRA(core).get() )==getA( getIRB(core).get() ) ){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case F:
                if ( (getA( getIRA(core).get() )==getA( getIRB(core).get() )) &&
                     (getB( getIRA(core).get() )==getB( getIRB(core).get() ) )){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case X:
                if ( (getA( getIRA(core).get() )==getB( getIRB(core).get() )) &&
                     (getB( getIRA(core).get() )==getB( getIRB(core).get() ) )){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
            case I:
                if ( (getA( getIRA(core).get() )==getA( getIRB(core).get() )) &&
                     (getB( getIRA(core).get() )==getB( getIRB(core).get() ) )&&
                     (getModifier( getIRA(core).get() )==getModifier( getIRB(core).get() )) &&
                     (getBMode( getIRA(core).get() )==getBMode( getIRB(core).get() ) )&&
                     (getAMode( getIRA(core).get() )==getAMode( getIRB(core).get() ) )&&
                      getIRA(core).get()->opcode()==getIRB(core).get()->opcode()){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
            default:
                return;
        }
    }

};

class SNE_Instruction: public Instruction, public ExecutionContext{
public:
    SNE_Instruction(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode, std::string opcode): Instruction(opcode,a,b,modifier_,Amode,Bmode) {}
    ~SNE_Instruction()override{}
    void execute(Core &core, int PC)override{
        setCoreRegister(core);
        switch (getModifier(getIR(core).get())){
            case A:
                if ( getA( getIRA(core).get() )!=getA( getIRB(core).get() ) ){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case B:
                if ( getB( getIRA(core).get() )!=getB( getIRB(core).get() ) ){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case AB:
                if ( getA( getIRA(core).get() )!=getB( getIRB(core).get() ) ){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case BA:
                if ( getB( getIRA(core).get() )!=getA( getIRB(core).get() ) ){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case F:
                if ( (getA( getIRA(core).get() )!=getA( getIRB(core).get() )) ||
                     (getB( getIRA(core).get() )!=getB( getIRB(core).get() ) )){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case X:
                if ( (getA( getIRA(core).get() )!=getB( getIRB(core).get() )) ||
                     (getB( getIRA(core).get() )!=getB( getIRB(core).get() ) )){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
            case I:
                if ( (getA( getIRA(core).get() )!=getA( getIRB(core).get() )) ||
                     (getB( getIRA(core).get() )!=getB( getIRB(core).get() ) )||
                     (getModifier( getIRA(core).get() )!=getModifier( getIRB(core).get() )) ||
                     (getBMode( getIRA(core).get() )!=getBMode( getIRB(core).get() ) )||
                     (getAMode( getIRA(core).get() )!=getAMode( getIRB(core).get() ) ) ||
                     getIRA(core).get()->opcode()!=getIRB(core).get()->opcode()){
                    setThreadPtr( core, PC+2 ); 
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
            default:
                return;
        }
    }

};
class SLT_Instruction: public Instruction, public ExecutionContext{
public:
    SLT_Instruction(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode, std::string opcode): Instruction(opcode,a,b,modifier_,Amode,Bmode) {}
    ~SLT_Instruction()override{}
    void execute(Core &core, int PC)override{
        setCoreRegister(core);
        switch (getModifier(getIR(core).get())){
            case A:
                if ( getA( getIRA(core).get() )<getA( getIRB(core).get() ) ){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case B:
                if ( getB( getIRA(core).get() )<getB( getIRB(core).get() ) ){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case AB:
                if ( getA( getIRA(core).get() )<getB( getIRB(core).get() ) ){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case BA:
                if ( getB( getIRA(core).get() )<getA( getIRB(core).get() ) ){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
                return;
            case F:
            case I:
                if ( (getA( getIRA(core).get() )<getA( getIRB(core).get() )) &&
                     (getB( getIRA(core).get() )<getB( getIRB(core).get() ) )){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
            default:
                return;
            case X:
                if ( (getA( getIRA(core).get() )<getB( getIRB(core).get() )) &&
                     (getB( getIRA(core).get() )<getB( getIRB(core).get() ) )){
                    setThreadPtr( core, PC+2 );
                }
                else {
                    setThreadPtr( core, PC+1 );
                }
        }
    }

};

Instruction * createCMP(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode){
    return new CMP_Instruction(a, b, modifier_, Amode, Bmode, std::string("CMP"));
}
Instruction * createSNE(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode){
    return new CMP_Instruction(a, b, modifier_, Amode, Bmode, std::string("SNE"));
}
Instruction * createSLT(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode){
    return new SLT_Instruction(a, b, modifier_, Amode, Bmode, std::string("SLT"));
}
namespace{
    bool b = Factory::get_instance()->regist3r("CMP",createCMP);
    bool c = Factory::get_instance()->regist3r("SNE",createSNE);
    bool d = Factory::get_instance()->regist3r("SLT",createSLT);
}

#endif