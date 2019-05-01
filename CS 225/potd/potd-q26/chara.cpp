#include "chara.h"
#include <iostream>
using namespace std;

string Chara::getStatus(){
if(size==0) return "Empty";
else if(size<=3) return "Light";
else if(size<=6) return "Moderate";
else return "Heavy";
}

void Chara::addToQueue(string name){
if(size==0){
node* temp = new node;
temp ->name = name;
temp -> next =NULL;
head = temp;
current = temp;
}
else {
node* temp =new node;
temp-> name = name;
temp->next = NULL;
current ->next = temp;
current = current -> next;}
size ++;
if(size == 2) head ->next = current;
}

string Chara::popFromQueue(){
size --;
string a = head-> name ;
node* temp = head;
head = head->next;
delete temp;
return a;
}



