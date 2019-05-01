// Your code here
#include "food.h"
#include <iostream>

using namespace std;

void increaseQuantity(food* other){
other->setQuantity(other->getQuantity() + 1);
}


int main(){
food* a=new food("apples", 5);
cout<<"You have "<<a->getQuantity()<<" "<<a->getName()<<endl;
increaseQuantity(a);
cout<<"You have "<<a->getQuantity()<<" "<<a->getName()<<endl;
return 0;
}
 
