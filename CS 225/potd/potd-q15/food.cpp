#include <iostream>
#include <string>
using namespace std;

#include "food.h"

Food::Food() {
  name = "food";
  quantity = 0;
}

void Food::setName(string newName) {
  name = newName;
}

void Food::setQuantity(int newQuantity) {
  quantity = newQuantity;
}

string Food::getName() {
  return name;
}

bool Food::operator>(Food &a){
 if(this->getQuantity()>a.getQuantity()) return true;
 else return false;
}

template <class T>
T Food::more(T &a, T &b){
if(a>b) return a;
else return b;
}
template Food Food::more<Food>(Food &a,Food &b);  

int Food::getQuantity() const {
  return quantity;
}

void Food::increaseQuantity(Food * food) {
    (*food).setQuantity((*food).getQuantity() + 1);
}
