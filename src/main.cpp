// RBT driver

#include "node.hpp"
#include <iostream>


int main() {
  
  typedef int node_type; //where int is the T inside the RBT class
  typedef Node<node_type> node;

  node nodo{5, RED};
  //nodo=1; // default constructor
  std::cout << nodo.data << std::endl;
  std::cout << nodo.color << std::endl;
  std::cout << nodo.left << std::endl;
  std::cout << nodo.right << std::endl;
  std::cout << nodo.parent << std::endl;



  return 0;
}
/*
int main() {
  RBTree bst;
  bst.insert(8);
  bst.insert(18);
  bst.insert(5);
  bst.insert(15);
  bst.insert(17);
  bst.insert(25);
  bst.insert(40);
  bst.insert(80);
  bst.deleteNode(25);
  bst.printTree();
  return 0;
}
*/