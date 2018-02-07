#ifndef INSTRUCTION_FACTORY_HPP_
#define INSTRUCTION_FACTORY_HPP_
#include <unordered_map>
#include <string>

class Factory {
public:
    typedef Instruction* (*creator_t)(int a, int b, Modifier modifier_,
     Mode Amode, Mode Bmode);
    static Factory * get_instance(){
        static Factory f;
        return &f;
    }
    Instruction* create( const std::string &id, Modifier modifier_,
     Mode Amode, Mode Bmode, 
     int a, int b  ){
        return creator_z[id](a, b, modifier_, Amode, Bmode);
    }
    bool regist3r( const std::string& id, creator_t creator ){
        creator_z[id] = creator;
        return true;
    }
private:
    std::unordered_map<std::string, creator_t> creator_z;
};
#endif