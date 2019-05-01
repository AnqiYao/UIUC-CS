#include "treeNode.h"

#include <cstddef>
#include <iostream>
using namespace std;

TreeNode::TreeNode() : left(NULL), right(NULL) { }

int TreeNode::getHeight() {
   if(left==NULL&&right==NULL) return 0;
   
   else  if(left==NULL && right!=NULL) return 1+right->getHeight();

   else  if(left!=NULL && right == NULL) return 1+left->getHeight();

   return 1+left->getHeight()+right->getHeight();
}
