//source: https://www.boost.org/doc/libs/1_80_0/libs/test/doc/html/boost_test/utf_reference/testing_tool_ref.html

#define BOOST_TEST_MODULE RBTree_tests
#define BOOST_TEST_LOG_LEVEL message //   ./tests --log_level=message
#include "RBT.hpp"
#include <boost/mpl/list.hpp>
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <vector>


BOOST_AUTO_TEST_SUITE(RBTree_Node)
//--------------------------------------
BOOST_AUTO_TEST_CASE(constructors) {
  BOOST_TEST_MESSAGE("A Node<double> :");
  _Node<double> nod1{1.55}; // default

  BOOST_CHECK_EQUAL(nod1.data, 1.55);
  BOOST_CHECK_EQUAL(nod1.color, BLACK);
  BOOST_CHECK_EQUAL(nod1.left, nullptr);
  BOOST_CHECK_EQUAL(nod1.right, nullptr);
  BOOST_CHECK_EQUAL(nod1.parent, nullptr);

  BOOST_TEST_MESSAGE("A Node<int> :");
  _Node<int> nod2{5, RED}; //custom

  BOOST_CHECK_EQUAL(nod2.data, 5);
  BOOST_CHECK_EQUAL(nod2.color, RED);
  BOOST_CHECK_EQUAL(nod2.left, nullptr);
  BOOST_CHECK_EQUAL(nod2.right, nullptr);
  BOOST_CHECK_EQUAL(nod2.parent, nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
//----------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(RBTree_class)
RBTree<int, std::greater<int>> rbt0{}; //define alternative template
RBTree<int> rbt{}; // default constructor
RBTree<int> rbt1{1}; // int constructor
RBTree<double> rbt2{1.5}; // double constructor

//--------------------------------------
BOOST_AUTO_TEST_CASE(constructors) {
  rbt.print_tree();
  BOOST_TEST_MESSAGE("A RBTree<int> :");
  BOOST_CHECK_EQUAL(rbt1.get_root()->data, 1);
  BOOST_CHECK_EQUAL(rbt1.get_root()->color, BLACK);
  BOOST_CHECK_EQUAL(rbt1.get_root()->left, nullptr);
  BOOST_CHECK_EQUAL(rbt1.get_root()->right, nullptr);
  BOOST_CHECK_EQUAL(rbt1.get_root()->parent, nullptr);

  rbt2.print_tree();
  BOOST_TEST_MESSAGE("A RBTree<double> :");
  BOOST_CHECK_EQUAL(rbt2.get_root()->data, 1.5);
  BOOST_CHECK_EQUAL(rbt2.get_root()->color, BLACK);
  BOOST_CHECK_EQUAL(rbt2.get_root()->left, nullptr);
  BOOST_CHECK_EQUAL(rbt2.get_root()->right, nullptr);
  BOOST_CHECK_EQUAL(rbt2.get_root()->parent, nullptr);
}
//--------------------------------------
BOOST_AUTO_TEST_CASE(insert_method) {
  std::vector<int> v{61,52,20,16,55,85,76,71,65,81,93,90,101,102};
  for(long unsigned int i{0}; i<v.size(); i++) {
    rbt.insert(v[i]);
    rbt0.insert(v[i]);
  }
  BOOST_TEST_MESSAGE("Testing RBTree insert():");
  rbt.print_tree(); // default
  std::cout << std::endl;
  rbt0.print_tree(); // template parameter
  std::cout << std::endl;

  BOOST_TEST_MESSAGE("Inserting a duplicate key :");
  rbt.insert(101); // duplicate key ignored by design
  rbt.print_tree();
  std::cout << std::endl;
}
//--------------------------------------
BOOST_AUTO_TEST_CASE(find_and_contains_methods) {
  BOOST_TEST_MESSAGE("Testing RBTree find() and contains() :");
  BOOST_CHECK_EQUAL(rbt.find(61), 61); // if found returns the key
  BOOST_CHECK_EQUAL(rbt.find(1), 0); // if not found returns nothing
  BOOST_CHECK_EQUAL(rbt.contains(60), false); // if not found returns false
  BOOST_CHECK_EQUAL(rbt.contains(1), false); // if not found returns false
  BOOST_CHECK_EQUAL(rbt.contains(52), true); // if found returns true
  BOOST_CHECK_EQUAL(rbt.contains(55), true); // if found returns true
}
//--------------------------------------
BOOST_AUTO_TEST_CASE(delete_method) {
  BOOST_TEST_MESSAGE("Testing RBTree delete_() :");
  rbt.delete_(102);
  rbt.delete_(52);
  rbt.delete_(55);
  BOOST_CHECK_EQUAL(rbt.contains(52), false); // after deletion not found
  BOOST_CHECK_EQUAL(rbt.contains(55), false); // after deletion not found
  rbt.delete_(82); // not present not deleted
  rbt.delete_(10); // not present not deleted
}
//--------------------------------------
BOOST_AUTO_TEST_CASE(get_root_method) {
  BOOST_TEST_MESSAGE("Testing RBTree get_root() :");
  BOOST_CHECK_EQUAL(rbt.get_root()->data, 85);
  BOOST_CHECK_EQUAL(rbt.get_root()->color, BLACK); // root is always black
  BOOST_CHECK_EQUAL(rbt0.get_root()->data, 61);
  BOOST_CHECK_EQUAL(rbt0.get_root()->color, BLACK); // root is always black
}
//--------------------------------------
BOOST_AUTO_TEST_CASE(get_height_method) {
  BOOST_TEST_MESSAGE("Testing RBTree get_height() :"); // root level is 1st
  BOOST_CHECK_EQUAL(rbt.get_height(rbt.get_root()), 5); 
  BOOST_CHECK_EQUAL(rbt0.get_height(rbt0.get_root()), 5);
}
//--------------------------------------
BOOST_AUTO_TEST_CASE(get_leftmost_and_get_rightmost_method) {
  BOOST_TEST_MESSAGE("Testing RBTree get_leftmost() and get_rightmost() :");
  BOOST_CHECK_EQUAL(rbt.get_leftmost(rbt.get_root())->data, 16); // smallest 
  BOOST_CHECK_EQUAL(rbt.get_rightmost(rbt.get_root())->data, 101); // greatest
  BOOST_CHECK_EQUAL(rbt0.get_leftmost(rbt0.get_root())->data, 102); // greatest
  BOOST_CHECK_EQUAL(rbt0.get_rightmost(rbt0.get_root())->data, 16); // smallest 
}
//--------------------------------------
BOOST_AUTO_TEST_CASE(get_predecessor_and_get_successor_method) {
  BOOST_TEST_MESSAGE("Testing RBTree get_predecessor() and get_successor() :");
  BOOST_CHECK_EQUAL(rbt.get_predecessor(rbt.get_root())->data, 81); 
  BOOST_CHECK_EQUAL(rbt.get_successor(rbt.get_root())->data, 90);
  BOOST_CHECK_EQUAL(rbt0.get_predecessor(rbt0.get_root())->data, 65);
  BOOST_CHECK_EQUAL(rbt0.get_successor(rbt0.get_root())->data, 55); 
}
//--------------------------------------
BOOST_AUTO_TEST_CASE(print_ordered_keys_method) {
  BOOST_TEST_MESSAGE("Testing RBTree print_ordered_keys() :");
  rbt.print_ordered_keys(1);  // total order
  std::cout << std::endl;
  rbt.print_ordered_keys(2);  // from top to bottom right
  std::cout << std::endl;
  rbt.print_ordered_keys(3); // from bottom left to top
  std::cout << std::endl;
}
//--------------------------------------
BOOST_AUTO_TEST_CASE(clear_tree_method) {
  BOOST_TEST_MESSAGE("Testing RBTree clear_tree() :");
  rbt0.clear_tree(rbt0.get_root());  // clear whole tree
  //BOOST_CHECK_EQUAL(rbt0.find(102), 0);// after deletion root not found
  //BOOST_CHECK_EQUAL(rbt0.contains(55), false); // after deletion not found
}
//--------------------------------------

BOOST_AUTO_TEST_SUITE_END()
//----------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(RBTree_copy_move_semantics)
RBTree<int> rbt{999}; 
RBTree<int> rbt3{rbt};              // copy constructor
RBTree<int> rbt4{};
RBTree<int> rbt5{std::move(rbt)};   //move constructor
RBTree<int> rbt6{};

BOOST_AUTO_TEST_CASE(copy_constructor_and_assignement) {
  BOOST_TEST_MESSAGE("Testing RBTree copy constructor & assignment :");
  rbt.print_tree();
  std::cout << std::endl;
  rbt3.print_tree();
  std::cout << std::endl;
  BOOST_CHECK_EQUAL(rbt3.find(999), rbt.find(999));
  BOOST_CHECK_NE(&rbt3.find(999), &rbt.find(999)); // testing deep copy (different addresses)

  rbt4 = rbt;                       // copy assignment
  rbt4.print_tree();
  std::cout << std::endl;
  BOOST_CHECK_EQUAL(rbt4.find(999), rbt.find(999));
  BOOST_CHECK_NE(&rbt4.find(999), &rbt.find(999)); // testing deep copy (different addresses)
}
//--------------------------------------
BOOST_AUTO_TEST_CASE(move_constructor_and_assignement) {
  BOOST_TEST_MESSAGE("Testing RBTree move constructor & assignment :");
  rbt5.print_tree();
  std::cout << std::endl;
  BOOST_CHECK_EQUAL(rbt5.find(999), rbt.find(999));
  BOOST_CHECK_EQUAL(&rbt5.find(999), &rbt.find(999)); // testing move (same address)
  rbt6 = std::move(rbt5);           // move assignment
  rbt6.print_tree();
  std::cout << std::endl;
  BOOST_CHECK_EQUAL(rbt6.find(999), rbt5.find(999));
  BOOST_CHECK_EQUAL(&rbt6.find(999), &rbt5.find(999)); // testing move (same address)
}
//--------------------------------------

BOOST_AUTO_TEST_SUITE_END()
//----------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(RBTree_const_iterator)
RBTree<int> rbt{}; // define base case
RBTree<int>* tree_ptr{&rbt};

BOOST_AUTO_TEST_CASE(const_iterator) {
  // fill up the tree
  std::vector<int> v{61,52,20,16,55,85,76,71,65,81,93,90,101,102};
  for(long unsigned int i{0}; i<v.size(); i++) {
  rbt.insert(v[i]);
  }

  BOOST_TEST_MESSAGE("Testing RBTree forward const_iterator :");
  RBTree<int>::const_iterator fwd_it_begin{rbt.begin()};
  RBTree<int>::const_iterator fwd_it_end{rbt.end()};

  BOOST_CHECK_EQUAL((*fwd_it_begin), 16); // dereference/indirection operator
  BOOST_CHECK_EQUAL((*tree_ptr->begin()), 16); // access operator
  BOOST_CHECK_EQUAL((fwd_it_begin==rbt.begin()), 1); // == operator  
  BOOST_CHECK_EQUAL((fwd_it_begin!=rbt.end()), 1); // != operator

  /*
  while(fwd_it_begin!=fwd_it_end) {
    std::cout << *fwd_it_begin << std::endl;
    fwd_it_begin++;
  }
  while(fwd_it_begin!=fwd_it_end) {
    std::cout << *fwd_it_begin << std::endl;
    ++fwd_it_begin;
  }*/

  BOOST_TEST_MESSAGE("Testing RBTree backward const_iterator :");
  RBTree<int>::const_iterator bwd_it_begin{rbt.rbegin()};
  RBTree<int>::const_iterator bwd_it_end{rbt.rend()};

  BOOST_CHECK_EQUAL((*bwd_it_begin), 102); // dereference/indirection operator
  BOOST_CHECK_EQUAL((*tree_ptr->rbegin()), 102); // access operator
  BOOST_CHECK_EQUAL((bwd_it_begin==rbt.rbegin()), 1); // == operator  
  BOOST_CHECK_EQUAL((bwd_it_begin!=rbt.rend()), 1); // != operator

  /*
  while(bwd_it_begin!=bwd_it_end) {
    std::cout << *bwd_it_begin << std::endl;
    bwd_it_begin--;
  }
  while(rit!=bwd_it_end) {
    std::cout << *bwd_it_begin << std::endl;
    --bwd_it_begin;
  } 
  */
}
//--------------------------------------

BOOST_AUTO_TEST_SUITE_END()
//----------------------------------------------------------------



/*/ ----------------------------------------boost assertions list:
source: https://www.boost.org/doc/libs/1_80_0/libs/test/doc/html/boost_test/utf_reference/testing_tool_ref.html
BOOST_CHECK_NE(left, right);
BOOST_CHECK_EQUAL(left, right);
BOOST_CHECK_EQUAL_COLLECTIONS(left_begin, left_end, right_begin, right_end);
BOOST_CHECK_CLOSE_FRACTION(left, right, tolerance);
BOOST_CHECK_CLOSE(left, right, tolerance);
BOOST_CHECK_GE(left, right);
BOOST_CHECK_GT(left, right);
BOOST_CHECK_LE(left, right);
BOOST_CHECK_LT(left, right);
BOOST_CHECK_MESSAGE(predicate, message);
BOOST_CHECK_NO_THROW(expression);
BOOST_CHECK_THROW(expression, exception_type);
BOOST_CHECK_EXCEPTION(expression, exception_type, predicate);
BOOST_CHECK_SMALL(value, tolerance); 
*/