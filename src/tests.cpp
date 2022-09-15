#define BOOST_TEST_MODULE RBTree_Tests
//#define BOOST_TEST_LOG_LEVEL = message RBTree_Tests
#include "RBT.hpp"
#include <boost/test/included/unit_test.hpp>

#include <iostream>

BOOST_AUTO_TEST_SUITE(RBTree_Node)
//--------------------------------------
BOOST_AUTO_TEST_CASE(Initializazion) {
  BOOST_TEST_MESSAGE( "Testing _Node's initialization :" );

  BOOST_TEST_MESSAGE( "A Node<double> :" );
  _Node<double> nod1{1.55}; // default

  BOOST_CHECK_EQUAL(nod1.data, 1.55);
  BOOST_CHECK_EQUAL(nod1.color, BLACK);
  BOOST_CHECK_EQUAL(nod1.left, nullptr);
  BOOST_CHECK_EQUAL(nod1.right, nullptr);
  BOOST_CHECK_EQUAL(nod1.parent, nullptr);

  BOOST_TEST_MESSAGE( "A Node<int> :" );
  typedef int node_type; // declare T type intended
  typedef _Node<node_type> Node;
  Node nod2{5, RED}; //custom
  
  BOOST_CHECK_EQUAL(nod2.data, 5);
  BOOST_CHECK_EQUAL(nod2.color, RED);
  BOOST_CHECK_EQUAL(nod2.left, nullptr);
  BOOST_CHECK_EQUAL(nod2.right, nullptr);
  BOOST_CHECK_EQUAL(nod2.parent, nullptr);
}
//--------------------------------------
BOOST_AUTO_TEST_CASE(Methods) {

}

BOOST_AUTO_TEST_SUITE_END()

//----------------------------------------------------------------
BOOST_AUTO_TEST_SUITE(RBTree_class)


//--------------------------------------
BOOST_AUTO_TEST_CASE(Initialization) {
//RBTree<int> rbt;
//rbt.insert(61);
}

//--------------------------------------
BOOST_AUTO_TEST_SUITE_END()