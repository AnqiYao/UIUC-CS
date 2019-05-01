#include <iostream>
#include <stdlib.h>

using namespace std;

struct TreeNode {

    int val;

    TreeNode *left;

    TreeNode *right;

    TreeNode(int x) {

      left = NULL;

      right = NULL;

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
  // your code here
  //
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
 	//your code here
	return NULL;

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

  TreeNode * n1 = new TreeNode(4);

  TreeNode * n2 = new TreeNode(7);

  TreeNode * n3 = new TreeNode(11);

  TreeNode * n4 = new TreeNode(13);

  TreeNode * n5 = new TreeNode(14);

  TreeNode * n6 = new TreeNode(22);

  n5->left = n3;

  n5->right = n6;

	n3->right = n4;

  n3->left = n2;

  n2->left = n1;

  
  cout << "Last Unbalanced Node: " << (findLastUnbalanced(n5))->val << endl;

  deleteTree(n5);

  return 0;

}
