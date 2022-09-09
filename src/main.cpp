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
  rbt.printTree();  
  rbt.insert(18);
/*rbt.insert(5);
  rbt.insert(15);
  rbt.insert(17);
  rbt.insert(25);
  rbt.insert(40);
  rbt.insert(80);
  rbt.deleteNode(25);
  rbt.printTree(); */
  return 0;
}