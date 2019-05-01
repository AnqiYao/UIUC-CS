// square.h
#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include "square.h"

using namespace std; 
class square{
public:
square();
square(const square &other);
~square();

private:
double* length;
string name;


};

#endif
