// main.cpp
#include "animal.h"
#include "pet.h"
#include <iostream>

using namespace std;

int main(){
pet a;
a.setName("Garfield");
a.animal::print();
a.print();

return 1;
}
