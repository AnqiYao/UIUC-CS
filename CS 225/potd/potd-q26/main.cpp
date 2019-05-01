#include <iostream>
#include "chara.h"
using namespace std;


int main() {
  Chara* a= new Chara;
  a->addToQueue("Ray");
  cout << a->getStatus()<<endl;
  a->addToQueue("Siri"); 
  cout << a->getStatus() << endl;
  a->addToQueue("Judy");
  cout << a->getStatus() << endl;
  cout<<a->popFromQueue()<<endl;
  cout<<a->getStatus()<<endl;
  cout<<a->popFromQueue()<<endl;
  cout<<a->getStatus()<<endl;
  cout<<a->popFromQueue()<<endl;
  cout<<a->getStatus()<<endl;

  
  return 0;
}
