//source: https://www.boost.org/doc/libs/1_80_0/libs/test/doc/html/boost_test/utf_reference/testing_tool_ref.html

#define BOOST_TEST_MODULE RBTree_tests
//#define BOOST_TEST_SHOW_PROGRESS true
#include "RBT.hpp"
#include <boost/mpl/list.hpp>
#include <boost/test/included/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE(RBTree_Node)
//--------------------------------------
BOOST_AUTO_TEST_CASE(Constructors) {
  BOOST_TEST_MESSAGE( "A Node<double> :" );
  _Node<double> nod1{1.55}; // default

  BOOST_CHECK_EQUAL(nod1.data, 1.55);
  BOOST_CHECK_EQUAL(nod1.color, BLACK);
  BOOST_CHECK_EQUAL(nod1.left, nullptr);
  BOOST_CHECK_EQUAL(nod1.right, nullptr);
  BOOST_CHECK_EQUAL(nod1.parent, nullptr);

  BOOST_TEST_MESSAGE( "A Node<int> :" );
  _Node nod2{5, RED}; //custom

  BOOST_CHECK_EQUAL(nod2.data, 5);
  BOOST_CHECK_EQUAL(nod2.color, RED);
  BOOST_CHECK_EQUAL(nod2.left, nullptr);
  BOOST_CHECK_EQUAL(nod2.right, nullptr);
  BOOST_CHECK_EQUAL(nod2.parent, nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
//----------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(RBTree_class)
//--------------------------------------
BOOST_AUTO_TEST_CASE(Constructors) {
  RBTree<int> rbt{}; //default constructor
  rbt.print_tree();
  RBTree<int> rbt1{1.5}; //custom constructor
  rbt1.print_tree();
  BOOST_TEST_MESSAGE( "A RBTree<int> :" );
  BOOST_CHECK_EQUAL(rbt.get_root()->data, 61);
  BOOST_CHECK_EQUAL(rbt.get_root()->color, BLACK);
  BOOST_CHECK_NE(rbt.get_root()->left, nullptr);
  BOOST_CHECK_NE(rbt.get_root()->right, nullptr);
  BOOST_CHECK_EQUAL(rbt.get_root()->parent, nullptr);
}

//--------------------------------------
BOOST_AUTO_TEST_SUITE_END()


//BOOST_CHECK_NE(left, right);
//BOOST_CHECK_EQUAL(left, right);
//BOOST_CHECK_EQUAL_COLLECTIONS(left_begin, left_end, right_begin, right_end);
//BOOST_CHECK_CLOSE_FRACTION(left, right, tolerance);
//BOOST_CHECK_CLOSE(left, right, tolerance);
//BOOST_CHECK_GE(left, right);
//BOOST_CHECK_GT(left, right);
//BOOST_CHECK_LE(left, right);
//BOOST_CHECK_LT(left, right);
//BOOST_CHECK_MESSAGE(predicate, message);
//BOOST_CHECK_NO_THROW(expression);
//BOOST_CHECK_THROW(expression, exception_type);
//BOOST_CHECK_EXCEPTION(expression, exception_type, predicate);
//BOOST_CHECK_SMALL(value, tolerance);
// while with 50 int, same with 50 double, test iteratorS, print tree, test find, print inorder traversal, etc..