#include <iostream>
#include <cstddef>
using namespace std;

struct node {
    int val;
    node *next;
};

void printList(node *head) {
   if(head == NULL)
       cout<<"nothing"<<endl;
   else{
     int count = 0;
     node* temp = head;
     while ( temp!=NULL){
      cout<<"Node " <<count<< ": "<< temp->val<<endl;
      temp = temp->next;
      count ++;}
    }
  // printList function
}

int main() {
  // Test 1: An empty list
  node * head = NULL;
  printList(head);
  
  // Test 2: A list with exactly one node
  node * a = NULL;
  node t ;
  t.val=300;
  t.next = NULL;
  a = &t;
  printList(a);
  // Test 3: A list with more than one node
  node* c = NULL ;
  node* b = NULL ;
  node e;
  node f;
  e.val=200;
  f.val =100;
  b = &f;
  c = &e;
  f.next = c;
  e. next = a ;
  printList(b);
  return 0;
}
