#ifndef _TREENODE_H
#define _TREENODE_H

#include <cstddef>
#include <iostream>
using namespace std;

class TreeNode {
public:
  TreeNode *left;
  TreeNode *right;
  TreeNode();
  bool isComplete();
private:
  bool isComplete(const TreeNode* subroot);
  bool isPerfect(const TreeNode* subroot);
  int getHeight(const TreeNode* subroot);
};

#endif
