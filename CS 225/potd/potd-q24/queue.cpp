#include "queue.h"
#include <iostream>
#include <cstddef>
using namespace std;

// `int size()` - returns the number of elements in the stack (0 if empty)
int Queue::size() const {
  return a.length;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Queue::isEmpty() const {
  return a.length == 0;
}

// `void enqueue()`- puts an item to the queue in O(1) time
void Queue::enqueue(int value) {
      if(this->isEmpty()) {
         a.head->val  = value;
         a.tail->val  = value;
         a.tail->next = NULL;
       }
      else {
         a.tail->next = new node;
         a.tail->next -> val = value;
         a.tail = a.tail->next;
         if(size() == 1) a.head->next = a.tail;
         a.tail ->next = NULL;
       }
       a.length++;
       cout<< a.length<< endl;
}

// `int dequeue()` - removes an item off the queue and returns the value in O(1) time
int Queue::dequeue() {
   if(this->isEmpty()) return -1;
   else {
      node* c = a.head;
      
      int b  = a.head->val;
      
      a.head = a.head->next ;
      
      delete c;
      a.length--;
      return b;
    }
        
}
