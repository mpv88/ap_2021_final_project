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
  RBTree<int> rbt{};
  rbt.insert(61); //insert
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
  rbt.insert(102);
  rbt.delete_(102); //delete
  rbt.delete_(82); //delete
  rbt.delete_(52); //delete
  rbt.delete_(55); //delete
  rbt.delete_(10); //delete
/*std::cout << (rbt.find(61)) << std::endl; //find & contains
  std::cout << (rbt.contains(60)) << std::endl; //0
  std::cout << (rbt.contains(61)) << std::endl; //1
  std::cout << (rbt.contains(85)) << std::endl; //1
  std::cout << (rbt.contains(1)) << std::endl;  //0
  std::cout << std::endl;*/
  rbt.print_ordered_keys(1);  //total order
  std::cout << std::endl;
/*rbt.print_ordered_keys(2);  //from top to bottom right
  std::cout << std::endl;
  rbt.print_ordered_keys(3); //from bottom left to top
  std::cout << std::endl;
  std::cout << rbt.get_height(rbt.get_root()) << std::endl; //get height + root
  std::cout << rbt.get_leftmost(rbt.get_root())->data << std::endl; // min
  std::cout << rbt.get_rightmost(rbt.get_root())->data << std::endl; // max
  std::cout << rbt.get_successor(rbt.get_root())->data << std::endl; // 1st right
  std::cout << rbt.get_predecessor(rbt.get_root())->data << std::endl; // 1nd left
  std::cout << (rbt.get_root()->data) << std::endl;
  rbt.clear_tree();  //clear whole */
  //rbt.print_tree();  //print whole

  //copy & move constructors/assignments
  //RBTree<int> rbt2{};   // constructor
  //RBTree<int> rbt2{rbt};  // copy constructor
  //RBTree<int> rbt2{std::move(rbt)};  // move constructor MAY modify original object (not always)
  //rbt2 = rbt; // copy assignment
  //rbt2 = std::move(rbt); // move assignment
  //rbt2.print_tree();	  // print copied tre
  //rbt.insert(102);
  //rbt.print_tree();
  //rbt2.print_tree(); // testing for deep copy so not shallow (not 102 added to original)
  
  //constant iterator use
 /* auto it{rbt->begin()};
  auto end{rbt->end()};NodePtr current_node; ///< node currently pointed by the iterator.
    if(it==end) { return; }
    for(; it != end; ++it) {
      std::cout << *it << std::endl
    } */
  //auto it = rbt.begin();
  //auto it2 = rbt.end();
  //std::cout << *it << std::endl; //dereference & begin OK
  //std::cout << it->first << std::endl; //dereference & end OK
  rbt.print_tree();
  std::cout << "Testing const_iterator" << std::endl;
  for (auto it=rbt.begin(); it!=rbt.end(); it++) {
    //std::cout << *it << std::endl;
    }
  
    //for(auto &element : rbt){
    //  rbt.delete(element.data);
  //std::cout << *(++it) << std::endl;
  //std::cout << *(it++) << std::endl;
 /* std::cout << *(--it) << std::endl;
  std::cout << *(it--) << std::endl;
  std::cout << it==it2 << std::endl;
  std::cout << it!=it2 << std::endl; */
  return 0;
};