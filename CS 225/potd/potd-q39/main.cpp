#include <iostream>

using namespace std;


// Definition for a binary tree node.

struct TreeNode {

    int val;

    TreeNode *left;

    TreeNode *right;
    
    TreeNode *parent;

    TreeNode(int x) {

      left = NULL;

      right = NULL;

      parent = NULL;

      val = x;

    }

};


int getHeight(TreeNode* root){
    if(root == NULL)
          return -1;
   return 1+ max(getHeight(root->left),getHeight(root->right));
}

bool isAVL(TreeNode* root) {
  if(root == NULL)
       return true;
  if( getHeight(root->left) - getHeight(root->right) >1 ||  getHeight(root->left) - getHeight(root->right)<-1)
          return false;
  return isAVL(root->right) && isAVL(root->left);
 }

int getLevel(TreeNode* subroot,TreeNode* root){
        if(subroot->val == root->val)
                  return 0;
        else if( subroot->val > root->val)
                  return 1+getLevel(subroot,root->right);
        else 
             return 1+ getLevel(subroot,root->left);
 }


TreeNode* findLastUnbalanced(TreeNode* root) {
       if( !isAVL(root) && isAVL(root->left) && isAVL(root->right))
                        return root;
       else if ( !isAVL(root->left) && isAVL(root->right))
                  return findLastUnbalanced(root->left);
       else if ( !isAVL(root->right) && isAVL(root->left))
                  return findLastUnbalanced(root->right);
       else if ( !isAVL(root->right) && !isAVL(root->left))
             return getLevel(findLastUnbalanced(root->right),root) >= getLevel(findLastUnbalanced(root->left),root) ? findLastUnbalanced(root->right):findLastUnbalanced(root->left); 
	return NULL;

}

void rightRotate(TreeNode* root) {
  TreeNode* n = root->parent;
  TreeNode* temp = root ->left;
  root->left = temp -> right;
  temp -> right = root;
  temp->parent = n;
  if(n->left == root)
      n->left = temp;
  else 
      n->right = temp;
  root-> parent = temp;
  root->left->parent = root;
}


void leftRotate(TreeNode* root) {
  TreeNode* n = root->parent;
  TreeNode* temp = root ->right; 
  root -> right = temp ->left;
  temp -> left  = root;
  temp->parent = n;
  if(n->left == root)
       n->left = temp;
  else 
       n->right = temp;
  root ->parent = temp;
    root->right->parent = root;
}

void deleteTree(TreeNode* root)

{

  if (root == NULL) return;

  deleteTree(root->left);

  deleteTree(root->right);

  delete root;

  root = NULL;

}

int main() {

  TreeNode * n1 = new TreeNode(2);

  TreeNode * n2 = new TreeNode(5);

  TreeNode * n3 = new TreeNode(8);

  TreeNode * n4 = new TreeNode(10);

  TreeNode * n5 = new TreeNode(13);

  n4->left = n3;
  
  n3->parent = n4;

  n4->right = n5;

  n5->parent = n4;

  n3->left = n2;

  n2->parent = n3;

  n2->left = n1;

  n1->parent = n2;
 
  if(findLastUnbalanced(n4)!= NULL){
        if(getHeight( findLastUnbalanced(n4)->right)> getHeight(findLastUnbalanced(n4)->left))
              leftRotate(findLastUnbalanced(n4));
        else 
              rightRotate(findLastUnbalanced(n4));
     } 
 // Your Code Here (Right or left rotate to balance above tree? )


  cout << "Ex 1 Inorder traversal : " << ((n4->left)->left)->val << ", " << (n4->left)->val << ", " <<((n4->left)->right)->val << ", " << n4->val << ", " << (n4->right)->val << endl;

  n1 = new TreeNode(2);

  n2 = new TreeNode(5);

  n3 = new TreeNode(8);

  n4 = new TreeNode(10);

  n5 = new TreeNode(13);

  n2->right = n3;
  
  n3->parent = n2;

  n2->left = n1;

  n1->parent = n2;

  n3->right = n4;

  n4->parent = n3;

  n4->right = n5;

  n5->parent = n4;

 
  if(findLastUnbalanced(n2)!= NULL){
        if(getHeight( findLastUnbalanced(n2)->right)> getHeight(findLastUnbalanced(n2)->left))
              leftRotate(findLastUnbalanced(n2));
        else 
               rightRotate(findLastUnbalanced(n2));
     }  
 // Your Code Here (Right or left rotate to balance above tree? )

  cout << "Ex 2 Inorder traversal : " << (n2->left)->val << ", " << n2->val << ", " << ((n2->right)->left)->val << ", " << (n2->right)->val << ", " << ((n2->right)->right)->val << endl;

  deleteTree(n2);

  return 0;
}
