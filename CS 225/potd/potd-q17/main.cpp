#include <iostream>
using namespace std;

struct node {
  int val;
  node *next;
};

void printList(node *head) {
  if (head == NULL) {
    cout << "Empty list" << endl;
    return;
  }

  node *temp = head;
  int count = 0;
  while(temp != NULL) {
    cout << "Node " << count << ": " << temp ->val << endl;
    count++;
    temp = temp->next;
  }
}

void insertSorted(node **head, node *insert) {
   if(*head==NULL){ *head = insert;}
   else {
      if( (*head)->val > insert->val) {insert->next = *head; *head = insert;}
      else {  
       head = &((*head)->next);  
       insertSorted(head,insert);
            
        }
    }
    // your code here
}


int main() {
  // Empty List:
  node *head = NULL;
  printList(head);

  // Add 3 to list:
  node three;
  three.val = 3;
  three.next = NULL;
  insertSorted(&head, &three);
  printList(head);

  // Add 9 to list:
  node nine;
  nine.val = 9;
  nine.next = NULL;
  insertSorted(&head, &nine);
  printList(head);

  // Add 1 to list:
  node one;
  one.val = 1;
  one.next = NULL;
  insertSorted(&head, &one);
  printList(head);

  // Add 5 to list:
  node five;
  five.val = 5;
  five.next = NULL;
  insertSorted(&head, &five);
  printList(head);
  
  return 0;
}
