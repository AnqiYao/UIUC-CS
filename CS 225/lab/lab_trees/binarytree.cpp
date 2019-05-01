/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
     
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;
       
    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
   mirror(root);
   // your code here
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{    
   //base case 
    if(subRoot == NULL) return;
    
    else { 
      Node* temp = subRoot -> right;
      Node* temp1 = subRoot->left;
     if(subRoot->right != NULL)
        mirror(subRoot->right);
     if(subRoot -> left != NULL)
        mirror(subRoot->left);
     subRoot -> right = temp1;
     subRoot -> left = temp;
     } 
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{   
/*
    bool a,b;
    if(root-> left != NULL) a= (root->elem > isOrdered2(root->left));
    if(root-> right != NULL) b= (root-> elem  < isOrdered1(root->right));
    // your code here
    return isOrdered(root) && (a && b);
*/
return isOrdered(root);
     
}

template <typename T>
const typename BinaryTree<T>::Node* BinaryTree<T>::isOrdered1(const Node* subRoot) const{
/*if(subRoot->left == NULL)
         return true;
  else {
     if ( subRoot->left->elem > subRoot ->elem )  
     return  false;
     else 
     return isOrdered1(subRoot -> left);
      }
*/ 
   
        
  while(subRoot->left !=NULL)
    
     subRoot = subRoot->left;
     return subRoot;
  
}

template <typename T>
const typename BinaryTree<T>::Node* BinaryTree<T>::isOrdered2(const Node* subRoot) const {
  /*if(subRoot->right == NULL)
         return true;
  else {
     if ( subRoot->right->elem < subRoot ->elem )  
     return  false;
     else 
     return isOrdered2(subRoot -> right);
    }
*/
      
  while(subRoot->right !=NULL)
    
     subRoot = subRoot->right;
     return subRoot;
}

template <typename T>
bool BinaryTree<T>::isOrdered(Node* subRoot) const
{
       //base case
if(subRoot==NULL) return true;
       if (subRoot ->right == NULL && subRoot->left == NULL)
            return true;
       else { 
            bool a,b,c,d;
a=isOrdered(subRoot->right);
b=isOrdered(subRoot->left);

if(subRoot->left!=NULL){
	T rightvalue=isOrdered2(subRoot->left)->elem;
	c = subRoot->elem > rightvalue;
}else c=true;
if(subRoot->right!=NULL){
T leftvalue=isOrdered1(subRoot->right)->elem;

d = subRoot->elem < leftvalue;}else d=true;
/*
           if(subRoot -> right != NULL){ 
              if(subRoot->right->elem < subRoot->elem)
                  return false;
                 else a = isOrdered(subRoot->right);
            }
           if(subRoot->left !=NULL ){
              if(subRoot->left->elem > subRoot->elem)
                  return false;
                 else b = isOrdered(subRoot->left);
*/
            
           return a && b && c && d;
      }
}
/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards,
 * ending at a leaf node. Paths ending in a left node should be printed before
 * paths ending in a node further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{    
    int path[100]; 
    for (int i =0;i<100;i++)
       path[i]=-1;
     int index =0;
    printPaths(root,path,index);
    // your code here
}


template <typename T>
void BinaryTree<T>::printPaths(Node* subRoot, int path[], int index ) const{
     if(subRoot == NULL)  return;
      path [index] = subRoot->elem; 
      index ++; 
      if(subRoot->right == NULL && subRoot->left == NULL){
          cout<< "Path: ";
          for(int i = 0; i<index ; i++ )
             cout << path[i]<<" " ;
         cout<<endl;
         } 
       else{
     //if(subRoot->left != NULL){
         printPaths(subRoot->left,path,index);
        
     //if(subRoot->right != NULL){
          printPaths(subRoot->right,path,index);
            }        
        
     

}
/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{       
    // your code here
     int sum = 0;
    return totalHeight(root,root,sum,0);
}

template <typename T>
int BinaryTree<T>::pathDistance(Node* subRoot, Node* target, int index) const{
     if(subRoot == NULL) return 0; 
     if(subRoot->elem == target->elem) return index; 
         index ++;
         return max(pathDistance(subRoot->right,target,index), pathDistance(subRoot->left,target,index));
}



template <typename T>
int BinaryTree<T>::totalHeight(Node* subRoot,Node* current, int sum, int num) const
{
    // Base case
    if (current == NULL)
        return 0;
    
    /* if(subRoot->left==NULL && subRoot->right== NULL)
       return totalHeight(subRoot->left) + totalHeight(subRoot->right);
     else if(subRoot->left==NULL && subRoot->right!= NULL)
        return 1+totalHeight(subRoot->left) + totalHeight(subRoot->right);
      else if(subRoot->left==NULL && subRoot->right!= NULL)
      return 1+totalHeight(subRoot->left) + totalHeight(subRoot->right);
    // Recursive definition
    else 
    return 2 + totalHeight(subRoot->left) + totalHeight(subRoot->right);
   */
    sum+=pathDistance(subRoot,current,num);
    sum+=totalHeight(subRoot, current->right,0,num);
    sum+=totalHeight(subRoot, current->left,0, num);
    return sum;
 
}

