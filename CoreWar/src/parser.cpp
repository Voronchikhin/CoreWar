#include <parser.hpp>

void Parser::skipSpace() {
  while (in.peek() == ' ' || in.peek() == '\n')
    (in.get());
}
Instruction *Parser::getInstruction() {
  Modifier modifier_;
  Mode Amode, Bmode;
  int a = 0, b = 0;
  char c = '#';
  std::string opcode;
  std::string number;
  skipSpace();
  if (in.peek() == EOF) {
    return nullptr;
  }
  for (int i = 0; i < 3; i++) {
    opcode += in.get();
  } // get opcode
  if ( opcode == std::string("ORG") ){
      skipSpace();
      in>>number;
      shift = stoi(number);
      return nullptr;
  }
  if (in.get() == '.') {
    switch (in.get()) {
    case 'F':
      modifier_ = F;
      break;
    case 'A':
      modifier_ = (in.get() == 'B') ? (AB) : (A);
      break;
    case 'B':
      modifier_ = (in.get() == 'A') ? (BA) : (B);
      break;
    case 'X':
      modifier_ = X;
      break;
    case 'I':
      modifier_ = I;
      break;
    default:
      modifier_ = I;
      break;
    }
  }
  skipSpace();
  in.get(c);

  if (!(c == '@' || c == '#' || c == '$' || c == '<' || c == '>' || c == '{' ||
        c == '}' || c == '*')) {
    throw std::invalid_argument("wrong modifier");
  }
  Amode = static_cast<Mode>(c);
  in >> number;
  a = stoi(number);
  number.clear();
  while (a < 0) {
    a += coreSize;
  }
  a %= coreSize;
  skipSpace();
  in.get(c);
  if (!(c == '@' || c == '#' || c == '$' || c == '<' || c == '>' || c == '{' ||
        c == '}')) {
    throw std::invalid_argument("wrong modifier");
  }
  Bmode = static_cast<Mode>(c);
  in >> number;
  b = stoi(number);
  while (b < 0) {
    b += coreSize;
  }
  b %= coreSize;
  return Factory::get_instance()->create(opcode, modifier_, Amode, Bmode, a, b);
}

std::vector<std::shared_ptr <Instruction>> Parser::getWarrior() {
  std::vector<std::shared_ptr <Instruction>> warrior;
  skipSpace();

  Instruction *tmp = nullptr;
  std::string buf;
  while (in.peek() != EOF) {
    skipSpace();
    if (in.peek() != ';') {
      try {
        tmp = getInstruction();
        if (tmp != nullptr) {
          warrior.push_back(std::shared_ptr <Instruction>(tmp));
        }
      } catch (std::invalid_argument exc) {
          std::cout<<exc.what();
      }
    } else {
      std::getline(in, buf);
      buf.clear();
    }
  }
  return warrior;
}
