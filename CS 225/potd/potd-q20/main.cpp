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
     node* temp;
       if(first->val < second->val){temp=first;first=first->next;}
         else { temp = second; second = second->next;}
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
                                                                                                                                                                      first = temp;
                                                                                                                                                                         second = NULL;
                                                                                                                                                                         }
                                                                                                                                                                         
node *listUnion(node *first, node *second) {
   node* newList = new node;
   mergeList (first,second);
   newList = first;
   node* temp = newList;
   while(temp->next!=NULL){
     if(temp->val==(temp->next)->val){
         temp->next=(temp->next)->next;
        }
     else  temp = temp->next;
   }
     return newList;



  // your code here
}

int main() {
  // Example #1
  node n_0, n_1, n_2, n_22, n_3, n_4;
  n_0.val = 0;
  n_1.val = 1;
  n_2.val = 2;
  n_22.val = 2;
  n_3.val = 3;
  n_4.val = 4;

  n_0.next = &n_1;
  n_1.next = &n_2;
  n_2.next = NULL;

  n_22.next = &n_3;
  n_3.next = &n_4;
  n_4.next = NULL;

  cout<<"First List:"<<endl;
  printList(&n_0);
  cout<<"Second List:"<<endl;
  printList(&n_22);

  node *union1 = listUnion(&n_0, &n_22);
  cout<<"Union:"<<endl;
  printList(union1);
  cout<<endl;


  // Example #2
  node p00, p01, p02, p03, p10, p11, p12, p13;

  // List 1: 0 2 2 2
  p00.val = 0; p00.next = &p01;
  p01.val = 2; p01.next = &p02;
  p02.val = 2; p02.next = &p03;
  p03.val = 2; p03.next = NULL;

  // List 2: 0 0 0 4
  p10.val = 0; p10.next = &p11;
  p11.val = 0; p11.next = &p12;
  p12.val = 0; p12.next = &p13;
  p13.val = 4; p13.next = NULL;

  cout<<"First List:"<<endl;
  printList(&p00);
  cout<<"Second List:"<<endl;
  printList(&p10);

  node *union2 = listUnion(&p00, &p10);
  cout<<"Union:"<<endl;
  printList(union2);
  cout<<endl;

  return 0;
}
