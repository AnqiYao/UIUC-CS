#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};


TreeNode* findInBST(TreeNode* root, int val) {


  if(root==NULL) return NULL;
  else {
     if(root->val > val) return findInBST (root->left,val);
     else if(root->val < val) return findInBST (root->right,val);
     else return root;
   }


}

int main() {
  TreeNode n_0, n_1, n_2, n_3, n_4, n_5;
  n_0.val = 10;
  n_1.val = 8;
  n_2.val = 13;
  n_3.val = 3;
  n_4.val = 9;
  n_5.val = 16;

  n_0.left = &n_1;
  n_0.right = &n_2;
  n_1.left = &n_3;
  n_1.right = &n_4;
  n_2.left = NULL;
  n_2.right = &n_5;
  n_3.left = NULL;
  n_4.left = NULL;
  n_5.left = NULL;
  n_3.right = NULL;
  n_4.right = NULL;
  n_5.right = NULL;


  TreeNode* ans;

  ans = findInBST(&n_0, 13);
  bool found = (ans != NULL);
  cout << "findInBST(root, 13):  Was found? " << found << endl;

  ans = findInBST(&n_0, 16);
  found = (ans != NULL);
  cout << "findInBST(root, 16):  Was found? " << found << endl;

  ans = findInBST(&n_0, 42);
  found = (ans != NULL);
  cout << "findInBST(root, 42):  Was found? " << found << endl;

  ans = findInBST(&n_0, 10);
  found = (ans != NULL);
  cout << "findInBST(root, 10):  Was found? " << found << endl;

  return 0;
}
