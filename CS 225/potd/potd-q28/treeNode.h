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
  bool isPerfect();
};

#endif
