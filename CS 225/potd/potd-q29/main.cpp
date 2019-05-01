#include <iostream>
#include "treeNode.h"
using namespace std;

int main() {
  TreeNode n1, n2, n3, n4;
  n1.left = &n2;
  n1.right = &n3;
  n2.left = &n4;
  cout<<"n1.isComplete(): "<<n1.isComplete()<<endl;
  cout<<"n2.isComplete(): "<<n2.isComplete()<<endl;
  cout<<"n3.isComplete(): "<<n3.isComplete()<<endl;
  cout<<"n4.isComplete(): "<<n4.isComplete()<<endl;

  TreeNode p1, p2, p3, p4, p5, p6, p7;
  p1.left = &p2;
  p1.right = &p3;
  p2.left = &p4;
  p2.right = &p5;
  p3.left = &p6;
  p3.right = &p7;
  cout<<"p1.isComplete(): "<<p1.isComplete()<<endl;

  return 0;
}
