#ifndef _STACK_H
#define _STACK_H

class Stack {
public:
  Stack(); 
  Stack(int value);
  int size() const;
  bool isEmpty() const;
  void push(int value);
  int pop();
private:
 
  int length;
  int value; 
  Stack* head;
  Stack* tail;
  Stack* next;

};

#endif
