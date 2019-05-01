#include <iostream>
#include <cstddef>
using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};

TreeNode* find(TreeNode* root, int key){
if(root == NULL)   return NULL;
if(root->val == key)     return root;
else {
 if(root->val > key) return find(root->left,key);
 else return find(root->right,key);
}
}

TreeNode* findLar(TreeNode* &root){
if( root== NULL ) return NULL;
if( root->right == NULL) 
{  TreeNode* a = new TreeNode;
   a->val = root ->val;
   
   root = NULL;
   return a;}

else 
   return findLar(root->right);
}

TreeNode* findSma(TreeNode* &root){
if( root == NULL ) return NULL;
if(root -> left == NULL) 
{  TreeNode* a = new TreeNode;
   a->val = root ->val;
   
   root = NULL;
   return a;}
else 
    return findSma(root->left);
}

TreeNode* deleteNode(TreeNode* root, int key) {
  if(find(root,key) == NULL) return root;
  if(find(root,key)->right == NULL && find(root,key)->left== NULL)
     {  delete find(root,key);
        return root;}
  else{ 
      TreeNode* a = findLar(find(root,key)->left);
      
       
       if(a!= NULL) {
       
        find(root,key)->val = a ->val;
       
       }
       else {
         TreeNode* b = findSma(find(root,key)->right);
          if(b!=NULL)
        find(root,key)->val = b->val;
        }
        return root;  
       }
 
    

  // your code here
  
}

void inorderPrint(TreeNode* node)
{
    if (!node)  return;
    inorderPrint(node->left);
    cout << node->val << " ";
    inorderPrint(node->right);
}


int main() {
/*
 * Example:
 * key = 3
 *   5
 *  / \
 * 3   6
 * /\   \
 *2 4    7
 *
 * After delete 3:
 * (One valid answer, IoS)
 *      5
 *     / \
 *    4   6
 *   /     \
 *  2       7
 *
 * (Another valid answer, IoP)
 *       5
 *      / \
 *     2   6
 *      \   \
 *       4   7
 */

  TreeNode n_0, n_1, n_2, n_3, n_4, n_5;
  n_0.val = 5;
  n_1.val = 3;
  n_2.val = 6;
  n_3.val = 2;
  n_4.val = 4;
  n_5.val = 7;

  n_0.left = &n_1;
  n_0.right = &n_2;
  n_1.left = &n_3;
  n_1.right = &n_4;
  n_2.left = NULL;
  n_2.right = &n_5;
  n_3.left = NULL;
  n_3.right = NULL;
  n_4.left = NULL;
  n_4.right = NULL;
  n_5.left = NULL;
  n_5.right = NULL;

  cout << "Before removal: " << endl;
  inorderPrint(&n_0);
  TreeNode* ans = deleteNode(&n_0, 3);
  cout << endl;
  cout << "After removal: " << endl;
  inorderPrint(ans);
  cout << endl;
 
  return 0;

}
