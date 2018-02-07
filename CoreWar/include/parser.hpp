#ifndef RED_CODE_PARSER_
#define RED_CODE_PARSER_

#include <core.hpp>
#include <exception>
#include <factory.hpp>
#include <fstream>

/* Parser::getInstruction is w8ing for string like 

DAT.I #3 $1   
                   or
DAT @23 #1

where DAT is opcode, 
      .I  is modifier (optional)
      before all address need moifier is in {    '@', '#', '$',  '<',  '>',  '{',  '}'     }
*/

class Parser {
public:
  Parser(std::ifstream &input, const int coreSize)
      : in(input), coreSize(coreSize) {}
  ~Parser() {}
  Instruction *getInstruction();
  std::vector<std::shared_ptr <Instruction> > getWarrior();
  int getShift(){ return shift; }
private:
  std::ifstream &in;
  inline void skipSpace();
  const int coreSize;
  int shift = 0;
};


#endif
