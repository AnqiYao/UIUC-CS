// animal.cpp

#include "animal.h"
#include <iostream>
#include <string>
#include <cstddef>

using namespace std;




animal::animal(){
type="cat";
food="fish";
}


animal::animal(string t,string f)
{     type=t;
      food=f;
}
  


string animal::getType()
{
  return type;
}
 



string animal::getFood()
{
  return food;
}



void animal::setType(string otherType){
 type=otherType;
}


void animal::setFood(string otherFood){
 food = otherFood;
}


void animal::print(){
cout<< "I am a "<<type<<endl;
}

