// square.cpp

#include <iostream>
#include "square.h"
#include <cstddef>
#include <cstring>

using namespace std;

square::square()
{ 
  name="mysquare";
  length=new double(2.0); }

square::~square(){
delete length;
length=NULL;
}

square::square(const square &other){
cout<< "I am copying!"<<endl;
name=other.name;
length=new double(*other.length);

}
