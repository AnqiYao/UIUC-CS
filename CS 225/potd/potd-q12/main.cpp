#include <iostream>
#include <string>

#include "square.h"
using namespace std;

int main(){
    Square a;
    Square b = a;
    Square c(a);
    Square d;
    cout<<d.getLength()<<endl;
    cout<<b.getLength()<<endl;
    cout<<c.getLength()<<endl;
    d=b+c;
    cout<<d.getLength()<<endl;
    cout<<d.getName()<<endl;
    return 0;
}
