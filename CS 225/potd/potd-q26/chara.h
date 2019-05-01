#ifndef _CHARA_H
#define _CHARA_H

#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Chara {
public:
struct node{
string name;
node* next;
};
  string getStatus();
  void addToQueue(string name);
  string popFromQueue();
private:
int size;
node* current;
node* head; 
};

#endif
