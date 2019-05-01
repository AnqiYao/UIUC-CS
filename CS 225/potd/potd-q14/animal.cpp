#include <iostream>
using namespace std;

#include "animal.h"

string animal::getType() {
  return type;
}

void animal::setType(string s) {
  type = s;
}


string animal::getFood() {
  return food;
}

void animal::setFood(string s) {
  food = s;
}


void animal::print() {
  cout<<"I am a "<<type<<"."<<endl;
}

animal::animal() : type("cat"), food("fish") { }

animal::animal(string type, string food) : type(type), food(food) { }
