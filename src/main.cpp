// RBT driver

#include "Node.hpp"
#include "RBT.hpp"
#include "RBT_iterator.hpp"
#include <iostream>

/*
int main() {
  
  typedef int node_type; //where int is the T into RBT
  typedef _Node<node_type> Node;

  Node nodo{5, RED};
  //nodo=1; // default constructor
  std::cout << nodo.data << std::endl;
  std::cout << nodo.color << std::endl;
  std::cout << nodo.left << std::endl;
  std::cout << nodo.right << std::endl;
  std::cout << nodo.parent << std::endl;
  return 0;
}
*/
int main() {
  RBTree<int> rbt;
  rbt.insert(8);
  rbt.insert(18);
  rbt.insert(5);
  rbt.insert(15);
  rbt.insert(17);
  rbt.insert(25);
  rbt.insert(40);
  rbt.insert(80);
  rbt.delete_(25);
  rbt.delete_(10);
  rbt.delete_(55);
  std::cout << std::endl;
  rbt.preorder(); //from top to bottom right
  std::cout << std::endl;
  rbt.inorder(); //total order
  std::cout << std::endl;
  rbt.postorder(); //from bottom left to top
  std::cout << std::endl;
  std::cout << rbt.searchTree(40) << std::endl;
  std::cout << rbt.getRoot() << std::endl;
  rbt.printTree();
  return 0;
}