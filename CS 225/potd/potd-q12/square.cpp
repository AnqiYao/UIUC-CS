#include <iostream>
#include <string>
using namespace std;

#include "square.h"

Square::Square() {
    name = "mysquare";
    lengthptr = new double;
    *lengthptr = 2.0;
}

void Square::setName(string newName) {
  name = newName;
}

void Square::setLength(double newVal) {
  *lengthptr = newVal;
}

string Square::getName() const {
  return name;
}

double Square::getLength() const {
  return *lengthptr;
}

Square::Square(const Square & other) {
    cout << "I am copying!" << endl;
    name = other.getName();
    lengthptr = new double;
    *lengthptr = other.getLength();
}

Square::~Square() {
    delete lengthptr;
}

void Square:: operator=(Square const&other){
     cout<<"11"<<endl;
     name=other.getName();
     delete lengthptr;
     lengthptr  = new double;
    *lengthptr = other.getLength();
}

Square Square::operator+ (Square const&other){
      Square a= Square();
      a.name= name + other.getName();
      a.setLength(a.getLength()+other.getLength());
      return a;

}
