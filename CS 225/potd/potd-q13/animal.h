// animal.h
#ifndef ANIMAL_H
#define ANIMAL_H

#include "animal.h"
#include <string>

using namespace std;


class animal{
public:
animal();
animal(string t,string f);
string getType();
string getFood();
void setType(string otherType);
void setFood(string otherFood);
void print();

protected:
string type;
string food;
};

#endif
