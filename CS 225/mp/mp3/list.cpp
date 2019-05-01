#include <iostream>

using namespace std;
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{   clear();   
    /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{  if(head!=NULL){  
     ListNode* temp= this->head;
      while(temp->next!=NULL){
         temp=head->next;
         delete head;
         head = temp;     
         }
      delete head;  
  }
     /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{  ListNode* a = new ListNode(ndata);
   if(length==0)
    { head=a;
      tail=a;
      length++;}
   else 
    { a->next = head;
      head->prev=a;
      a->prev= NULL;
      head = a ;
      length++;
     }   
    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
   ListNode* a = new ListNode(ndata);
   if(length==0)
    { head=a;
      tail=a;
      length++;}
   else {
          tail->next=a;
          a->prev = tail;
          a->next = NULL;  
          tail = a;
          length++;
           }
     }    
      /// @todo Graded in MP3.1


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{       
       if(length == 0) return;
       reverse(head, tail);
       cout<<head->data<<" "<<tail->data<<endl;
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */

template <class T>
void List<T>::reverse ( ListNode *& startPoint, ListNode *& endPoint ) 
{      
     
     if(length>1&&startPoint!=NULL&&endPoint!=NULL){
          ListNode* current = startPoint;
          ListNode* startPoint1=startPoint;
          ListNode* start = startPoint->prev;
          ListNode* end = endPoint->next;
          while(current!= endPoint){
           current->prev = current->next;
           current= current -> prev;}
           endPoint->prev = start;
           if(start!=NULL)
             start->next= endPoint;
           current = startPoint;
           while ( current!=endPoint){
            current->prev->next=current;
            current= current->prev;
            }
            startPoint->next = end;
          if(end!= NULL)
             end->prev = startPoint;
          if(startPoint==head){
		head=endPoint;}

	  if(endPoint==tail){
		tail=startPoint1;}


                   
      }                
          
   } 
           /// @todo Graded in MP3.1

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
     
    
     if(length<=0) 
       return;
     else if(n>=length)
      {  reverse(head,tail);
             return;}
        ListNode* current=head;
        ListNode* startPoint = head;
        ListNode* temp1=NULL; 

        for( int i=0;i<length/n;i++){
           for ( int k=0;k<n-1;k++)
              { current=current->next;}
             temp1=current->next;

            reverse ( startPoint, current); 
                   
            startPoint = temp1;
           
            current = temp1; 
          }
              
       if(length> n *(length/n)){     
            temp1 = current; 
         for( int i=n*(length/n);i<length-1;i++){
               current=current->next;}
        
            reverse(temp1,current);}          

   
      
         
     /// @todo Graded in MP3.1
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
  if(length<=2)
      return;

  ListNode* current = head->next;
  ListNode* temp = current->next; 
  while ( current != tail  &&  current != NULL){
    current->prev->next = current->next;
    current->next->prev = current -> prev;
    tail->next = current ;  
    current -> prev = tail;
    tail = current ;
    current -> next = NULL; 
    current = temp->next;
    temp=current->next;
    }
    return;
     /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{   
    while(splitPoint>0){
        start=start->next;
        splitPoint--;
        }

    start->prev->next = NULL;
    start->prev  = NULL; 



      return start;
    // @todo Graded in MP3.2
     // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    ListNode* temp = NULL;
    if(first->data<second->data) { temp = first; first = first->next; }
    else     { temp = second; second = second->next; }
    ListNode* temp1 = temp;
    while ( first!= NULL && second !=NULL){
       if(first->data<second->data) { temp->next = first; first->prev = temp; first = first->next;}
       else { temp->next = second; second -> prev =temp; second = second ->next;}
       temp = temp->next;}
    
    if( first==NULL && second !=NULL){ 
      while(second !=NULL){
         temp->next = second; 
         second -> prev =temp; 
         second = second ->next;
         temp= temp->next; } 
      }  
   
    else if( first!=NULL && second ==NULL){ 
      while(first !=NULL){
         temp->next = first; 
         first -> prev =temp; 
         first = first ->next;
         temp= temp->next; } 
      }  
       
      return temp1;

 
    /// @todo Graded in MP3.2
    // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    if( chainLength==1) return start;
    ListNode* temp= start;
    int newLength=chainLength/2;
    while(newLength>0){
      temp=temp->next;
      newLength--;}
    temp->prev->next=NULL;
    temp->prev=NULL;
    newLength = chainLength/2;
    ListNode* temp1 = mergesort(start,newLength);
    ListNode* temp2 = mergesort(temp, chainLength-newLength); 
    
    return merge(temp1, temp2);
    
   
    






    /// @todo Graded in MP3.2
    // change me!
}
