// RBT driver

#include <iostream>
#include "RBT.hpp"


// testing RBTree main class
int main() {
    
  // create a new RBTree
  RBTree<int> rbt{};

  // print empty tree
  rbt.print_tree();

  // insert some values & following (automatic) tree rebalancing
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
  rbt.insert(102);

  // delete some nodes & following (automatic) tree rebalancing
  rbt.delete_(102);
  rbt.delete_(82); 
  rbt.delete_(52);
  rbt.delete_(55); 
  rbt.delete_(10);

  // retreive some keys within the tree (find & contains methods)
  std::cout << (rbt.find(61)) << std::endl; // 61
  std::cout << (rbt.contains(60)) << std::endl; //0
  std::cout << (rbt.contains(61)) << std::endl; //1
  std::cout << (rbt.contains(85)) << std::endl; //1
  std::cout << (rbt.contains(1)) << std::endl;  //0
  std::cout << std::endl;

  // print tree traversal methods
  rbt.print_ordered_keys(1);  // total order
  std::cout << std::endl;
  rbt.print_ordered_keys(2);  // from top to bottom right
  std::cout << std::endl;
  rbt.print_ordered_keys(3); // from bottom left to top
  std::cout << std::endl;

  // get and print the tree's root value
  std::cout << (rbt.get_root()->data) << std::endl;
  
  // get and print the tree's height
  std::cout << rbt.get_height(rbt.get_root()) << std::endl; //get height + root
  
  // get and print the tree's smallest and largest values
  std::cout << rbt.get_leftmost(rbt.get_root())->data << std::endl; // min
  std::cout << rbt.get_rightmost(rbt.get_root())->data << std::endl; // max
  
  // get and print the values of predecessor and successor nodes of a given node (e.g. the root)
  std::cout << rbt.get_successor(rbt.get_root())->data << std::endl; // 1st right
  std::cout << rbt.get_predecessor(rbt.get_root())->data << std::endl; // 1nd left
  
  // print the tree
  rbt.print_tree();

  // checking copy & move constructors/assignments
  RBTree<int> rbt2{rbt};  // copy constructor
  RBTree<int> rbt3{};   // default constructor
  rbt3 = rbt2; // copy assignment
  rbt2.print_tree();	  // print copied tree
  
  RBTree<int> rbt4{std::move(rbt)};  // move constructor MAY modify original object
  RBTree<int> rbt5{};   // default constructor
  rbt5 = std::move(rbt); // move assignment

  rbt2.print_tree();	  // print copied tree
  rbt.insert(102);
  rbt.print_tree();
  rbt2.print_tree(); // testing for deep copy so not shallow (not 102 added to original)
  
  // clear trees
  rbt2.clear_tree(rbt2.get_root());
  rbt3.clear_tree(rbt3.get_root());

  // constant fwd iterator use
  auto it{rbt.begin()};
  auto end{rbt.end()};
  
  // test iterator's indirection operator
  std::cout << *it << std::endl; // dereference & begin OK
  //std::cout << *end << std::endl; // dereference nullptr leads to seg fault
  
  // test equality and inequality operators
  std::cout << (it==rbt.begin()) << std::endl; //1
  std::cout << (it!=rbt.end()) << std::endl; //1
  
  // test fwd prefix iterator
  while(it!=end) {
    std::cout << *it << std::endl;
    ++it;
  }

  // test fwd potfix iterator
  while(it!=end) {
    std::cout << *it << std::endl;
    it++;
  }

  // constant bwd iterator use
  auto rit{rbt.rbegin()};
  auto rend{rbt.rend()};
  
  // test iterator's indirection operator
  std::cout << *rit << std::endl; //  dereference & begin OK
  //std::cout << *rend << std::endl; // dereference nullptr leads to seg fault
  
  // test bwd prefix iterator
  while(rit!=rend) {
    std::cout << *rit << std::endl;
    --rit;
  }

  // test bwd postfix iterator
  while(rit!=rend) {
    std::cout << *rit << std::endl;
    rit--;
  }

  // test iterator's access operator
  RBTree<int>* tree_ptr = &rbt;
  for(auto i=tree_ptr->begin(); i!=tree_ptr->end(); ++i) {
    std::cout << *i << "|";
  }
  std::cout << std::endl;
  return 0;
};