#include "stack.h"	
#include <cstddef>
#include <iostream>

using namespace std;

// `int size()` - returns the number of elements in the stack (0 if empty)

Stack::Stack(){
   value = 0;
   next  = NULL;
}

Stack::Stack(int a){
  value = a;
  next = NULL;
}

int Stack::size() const {
  return length;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Stack::isEmpty() const {
   if(size() == 0)
     return true;
   else 
     return false;
}

// `void push(int val)` - pushes an item to the stack in O(1) time
void Stack::push(int value) {
     Stack* temp = new Stack(value); 
    if(size() == 0) {
       head =  temp;
       tail =  temp;
        } 
     else { 
        tail->next = temp; 
        tail = tail-> next;
       }
      length++;
 }

// `int pop()` - removes an item off the stack and returns the value in O(1) time
int Stack::pop() {
     int temp = head ->value;
     head = head ->next;    
     length--;
     return temp;
     }
