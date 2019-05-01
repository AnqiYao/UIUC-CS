#include <iostream>
#include <string>
using namespace std;

#include "food.h"

//
// Write a templated function `more` which takes in two variables of the same
// type and returns whichever variable is greater than (`>`) the other.
//
template <class T>
T more(T &a, T &b){
if (a>b) return a;
else return b;
}


int main() {
    Food apples, oranges, greater;
    apples.setName("apples");
    apples.setQuantity(5);
    oranges.setName("oranges");
    oranges.setQuantity(3);
    greater = more<Food>(apples, oranges);
    cout << "We have more " << greater.getName() << "." << endl;
    return 0;
}
