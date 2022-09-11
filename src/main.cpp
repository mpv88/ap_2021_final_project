// RBT driver

#include <iostream>
#include "RBT.hpp"


/*// #TODO: testing Node class
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
//#TODO: testing RBT_iterator class
*/
int main() {
  RBTree<int> rbt;
  rbt.insert(61);
  rbt.insert(52);
  rbt.insert(20);
  rbt.insert(16);
  rbt.insert(55);
  rbt.insert(85);
  rbt.insert(76);
  rbt.insert(71);
  rbt.insert(65);
  rbt.insert(81);
  rbt.insert(93);
  rbt.insert(90);
  rbt.insert(101);
  std::cout << (rbt.contains(60)) << std::endl; //0
  std::cout << (rbt.contains(61)) << std::endl; //1
  std::cout << (rbt.contains(85)) << std::endl; //1
  std::cout << (rbt.contains(1)) << std::endl;  //0
  std::cout << std::endl;
  rbt.print_ordered_keys(1);  //total order
  std::cout << std::endl;
  rbt.print_ordered_keys(2);  //from top to bottom right
  std::cout << std::endl;
  rbt.print_ordered_keys(3); //from bottom left to top
  std::cout << std::endl;
  rbt.print_tree();
  return 0;
}