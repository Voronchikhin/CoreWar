#ifndef MARS_COREWAR_HPP
#define MARS_COREWAR_HPP

#include <core.hpp>
#include <executionContext.hpp>
#include <parser.hpp>

class MARS : public ExecutionContext{
public:
  explicit MARS(const std::vector<std::string> &war);
  MARS(const std::vector<std::string> &war, const int size);
  MARS(const std::vector<std::string> &war, const int size, const int Limit);
  MARS(const std::vector<std::string> &war, const int size, const int Limit, const int iterationLimit);
  void iterate();
  std::string getOpcode(unsigned cell);
  bool isEnded();
  int winner();
  int task_ptr();
  int warriorId();
private:
  const static unsigned int defaultIL = 10000;
  const static unsigned int defaultCoreSize = 8192;
  const int unsigned coreSize = defaultCoreSize;
  const int unsigned iterationLimit = defaultIL;

  Core core;
  unsigned int iteration_ = 0;

};


#endif
