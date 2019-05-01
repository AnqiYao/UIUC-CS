#include "treeNode.h"

#include <cstddef>
#include <iostream>
using namespace std;

TreeNode::TreeNode() : left(NULL), right(NULL) { }

bool TreeNode::isPerfect() {
  if(this->left == NULL && this->right == NULL) return true;
  else {
  if(this->left ==NULL && this->right !=NULL ) return false;
  else if(this->left != NULL && this-> right == NULL) return false;
  else 
       return this->left->isPerfect()&&this->right->isPerfect();
    }
}
