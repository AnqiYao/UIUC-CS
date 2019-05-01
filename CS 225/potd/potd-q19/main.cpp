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

void mergeList(node *first, node *second) {
  // your code here
  node* temp1; 
  node* temp;
  if(first->val < second->val){temp1=first;first=first->next;}
  else { temp1 = second; second = second->next;}
  temp = temp1;
  while( first!=NULL && second !=NULL){
      if(first->val < second->val)
        {   temp->next=first;
            first=first->next;}
       else { 
          temp->next = second;
          second=second->next;}
       temp=temp->next;
     }
  if(second !=NULL){
     while(second!=NULL)
      {  temp->next=second;
         second=second->next;
         temp=temp->next;}
        }
  else if (first!=NULL){ 
       while(first!=NULL){
         temp->next= first;
         first=first->next;
         temp=temp->next;
       }
     }
   first = temp1;
   second = NULL;  
}

int main() {
  // Example #1
  node n0, n2, n4, n11, n33, n55;
  n0.val = 0;
  n2.val = 2;
  n4.val = 11;
  n11.val = 4;
  n33.val = 33;
  n55.val = 55;

  n0.next = &n2;
  n2.next = &n4;
  n4.next = NULL;

  n11.next = &n33;
  n33.next = &n55;
  n55.next = NULL;

  cout<<"First List:"<<endl;
  printList(&n0);
  cout<<"Second List:"<<endl;
  printList(&n11);

  mergeList(&n0, &n11);

  cout<<"Merged List:"<<endl;
  printList(&n0);
  cout<<endl;

  // Example #2
  node p0, p2, p11, p33, p33_2, p44;
  p0.val = 0;
  p2.val = 2;
  p11.val = 11;
  p33.val = 33;
  p33_2.val = 33;
  p44.val = 44;

  p0.next = &p2;
  p2.next = NULL;

  p11.next = &p33;
  p33.next = &p33_2;
  p33_2.next = &p44;
  p44.next = NULL;

  cout<<"First List:"<<endl;
  printList(&p0);
  cout<<"Second List:"<<endl;
  printList(&p11);

  mergeList(&p0, &p11);

  cout<<"Merged List:"<<endl;
  printList(&p0);

  return 0;
}
