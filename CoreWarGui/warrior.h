#ifndef WARRIOR_H
#define WARRIOR_H
#include <QColor>
#include <string>

struct QWarrior
{
  QWarrior ( std::string fileName, std::string tag, QColor color );
  std::string tag_;
  std::string fileName_;
  QColor color_;
};

#endif // WARRIOR_H
