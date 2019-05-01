#ifndef _ANIMAL_H
#define _ANIMAL_H
#include "animal.h"
#include <iostream>

using namespace std;


class animal
{
private:
  string type, food;

public:
  string getType();
  void setType(string s);

  string getFood();
  void setFood(string s);

  virtual void print();

  animal();
  animal(string type, string food);
};

#endif
