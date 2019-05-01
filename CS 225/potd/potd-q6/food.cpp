// Your code here
#include "food.h"
#include <iostream>
#include <string>

using namespace std;

food::food(){}

food::food(string a, int b):name(a),quantity(b){}

void food::setName(string a)
{this->name = a;}

void food::setQuantity(int q)
{this->quantity=q;}

string food::getName(){
return name;
}

int food::getQuantity(){
return quantity;
}





