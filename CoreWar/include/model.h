#ifndef MODEL_H
#define MODEL_H

#include <QWidget>
#include <mars.hpp>
#include <fstream>
#include <string>

struct IterateResult{
    int warriorNumber;
    int cellNumber;
};
struct CellInfo{
  std::string opcode_;
};


struct Model
{
  virtual ~Model(){}
  virtual IterateResult iterate(){}
  virtual bool isEnded(){}
  virtual int winner(){}
  virtual void addPlayer(std::string player){}
  virtual CellInfo getCellInfo(int cellNumber){}
  virtual void start(){}
  virtual bool isSettingsValid(){}
};

class CoreWarModel: public Model
{
public:
  CoreWarModel(std::vector<std::string> warriors, int size, int numberWarriors_);
  IterateResult iterate() override;
  int winner() override;
  void addPlayer(std::string player) override;
  CellInfo getCellInfo(int cellNumber) override;
  ~CoreWarModel() override;
  bool isSettingsValid()override;
  bool isEnded()override;
  void start()override;
private:
  MARS *mars_;

  std::vector<char> cells_;   // -1 is unowned
  std::vector<std::string> warriors_;
  const int coreSize_;
  const int iterationLimit_;
  const static int defaultIterationLimit = 3000;
  int iteration_;
  int numberWarriors_;
};


#endif // MODEL_H
