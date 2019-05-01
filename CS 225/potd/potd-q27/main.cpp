#include <iostream>
#include "treeNode.h"
using namespace std;

int main() {
  TreeNode n1, n2, n3, n4;

  n1.left = &n2;
  n1.right = &n3;
  n2.left = &n4;

  cout<<"Height of n1: "<<n1.getHeight()<<endl;
  cout<<"Height of n2: "<<n2.getHeight()<<endl;
  cout<<"Height of n3: "<<n3.getHeight()<<endl;
  cout<<"Height of n4: "<<n4.getHeight()<<endl;

  return 0;
}