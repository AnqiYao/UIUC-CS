#include "treeNode.h"

#include <cstddef>
#include <iostream>
using namespace std;

TreeNode::TreeNode() : left(NULL), right(NULL) { }

bool TreeNode::isComplete() {
  return isComplete(this);
}

bool TreeNode::isPerfect(const TreeNode* subroot){
  if(subroot == NULL) return true;
  if(subroot->left == NULL && subroot->right == NULL) return true;
  else {
  if(subroot->left ==NULL && subroot->right !=NULL ) return false;
  else if(subroot->left != NULL && subroot-> right == NULL) return false;
  else
       return isPerfect(subroot->left)&&isPerfect(subroot->right);
    }
}

int TreeNode::getHeight(const TreeNode* subroot){
  if(subroot == NULL)  return -1;
  else 
      return 1+max(getHeight(subroot->left), getHeight(subroot->right));


}
bool TreeNode::isComplete(const TreeNode* subroot){
     if(subroot == NULL) return true;
    else {
      if (isComplete(subroot->left)){
          if (isPerfect(subroot->right) && getHeight(subroot->left)==getHeight(subroot->right)+1) 
                return true;
         }
      if(isPerfect(subroot->left))  
        if( isComplete(subroot->right)&& getHeight(subroot->left)==getHeight(subroot->right))
             return true;
       return false;
           }
   }

