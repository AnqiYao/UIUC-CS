#ifndef _QUEUE_H
#define _QUEUE_H
#include <cstddef>
class Queue {
public:
struct node{
 int val = 0 ;
 node* next ;
};
struct listNode {
  node* head = new node;
  node* tail = new node;
  int length = 0;
};
  int size() const;
  bool isEmpty() const;
  void enqueue(int value);
  int dequeue();
private:
  listNode a;
};

#endif
