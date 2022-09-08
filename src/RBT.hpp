///\file RBT.hpp
///\author mpv
///\brief header file with all RBT's members' declarations.

#ifndef RBT_HPP
#define RBT_HPP

#include <iostream>
#include <string>
#include <vector>

//RBTree class forward declaration to break cyclic references with includes.
template <class T, class CMP=std::less<T>> 
class RBTree;

#include "RBT_SubClasses.hpp"
#include "RBT_Methods.hpp"


///\brief RBTree is a template class which implements R. Bayer's Red Black Tree (1972).
///\param T type of the tree nodes' keys.
///\param CMP relational function to compare nodes' keys (default std::less<T>).
template <class T, class CMP> 
class RBTree {
  friend class const_iterator;//TODO: maybe duplicated from Node class
  friend class iterator;//TODO: maybe duplicated from Node class
  typedef Node *NodePtr; //TODO: maybe duplicated from Node class

private:

  ///\brief RBTree's single node, each node bears a key and a color (red or black).
  ///       Each node has a parent and two children (left and right).
  class Node;


public:
  ///\brief RBTree's regular iterator class.
  ///       Used to iterate over a sequence and manipulate RBTree's elements.
  class iterator;

  ///\brief RBTree's constant iterator class.
  ///      Used to iterate over a sequence and access only RBTree's elements.
  class const_iterator;


private:
  NodePtr root; ///< root of the RBTree (always black)
  NodePtr NIL; ///< leaf of the RBTree (always black)


public:
  CMP comparator; ///< comparison operator. 


  ///\brief RBTree's constructor.
  ///       Default constructor for the RBTree class.
  RBTree() noexcept {}


	///\brief Constructor for RBTree given the root node.
	///\param value The value to be inserted into the RBTree's root node.
	///\param cmp A custom comparison function for tree nodes (defaulted to std::less).
	RBTree(T value, CMP cmp=CMP{}) : root{new Node{value}}, comparator{cmp} {}


  ///\brief RBTree's destructor.
  ///       Default destructor for the RBTree class.
  ~RBTree() {}
   

  ///\brief Copy constructor for RBTree.
	///\param rbt The RBTree which will be copied to a new one.
	///\param cmp A custom comparison function for tree nodes (defaulted to std::less).
  RBTree(const RBTree &rbt, CMP cmp=CMP{}) : {root = copy(rbt.root)}
 

  ///\brief Move constructor for RBTree.
	///\param rbt The RBTree which will be moved into a new one.
	RBTree(RBTree&& rbt) noexcept : root{std::move(rbt.root)} {}

  ///\brief Function to insert a new value in the tree.
	///\param value The value you are going to insert.
	///\return A RBTree which includes an additional node with the value inserted.
  void insert(const T& value);
  
  
  ///\brief Function to test whether the tree contains a value.
	///\param value The value to be checked if already present within the RBTree.
	///\return Bool true if the value is in the RBTree, false otherwise.
  bool contains(const T& value) const;

  ///\brief Function to delete a value from the tree.
	///\param value The value you are going to delete.
	///\return A RBTree without the node which contained the value inserted.
  void delete(const T& value);
  
  ///\brief Function to get a constant tree iterator over all the tree keys.
	///\param value The value you are going to delete.
	///\return A RBTree without the node which contained the value inserted.
  RBTree<T, CMP>::const_iterator begin() const
  
  ///\brief Function to get the last value onstant tree iterator over all the tree keys.
	///\param value The value you are going to delete.
	///\return A RBTree without the node which contained the value inserted.
  RBTree<T, CMP>::const_iterator end() const


/*
public:
  // utility methods
  void initializeNULLNode(NodePtr node, NodePtr parent);
  void preOrderHelper(NodePtr node);
  void inOrderHelper(NodePtr node);
  void postOrderHelper(NodePtr node);
  NodePtr searchTreeHelper(NodePtr node, int key);
  void fixDelete(NodePtr x);
  void rbTransplant(NodePtr u, NodePtr v);
  void deleteNodeHelper(NodePtr node, int key);
  void fixInsert(NodePtr k);
  void printHelper(NodePtr root, string indent, bool last);

  //----------------------------------------------------------------
  // Constructor
  RBTree();

  // Public methods
  void preorder();
  void inorder();
  void postorder();
  NodePtr searchTree(int k);
  NodePtr minimum(NodePtr node);
  NodePtr maximum(NodePtr node);
  NodePtr successor(NodePtr x);
  NodePtr predecessor(NodePtr x);
  void leftRotate(NodePtr x);
  void rightRotate(NodePtr x);
  void insert(int key);
  NodePtr getRoot();
  void deleteNode(int data);
  void printTree();
};

/*TODO:
CLASSES:
  RBTree<T, CMP=std::less<T>>                                         OK
  RBTree<T, CMP=std::less<T>>::const_iterator                         OK

PUBLIC METHODS:
  for const_iterator:
                    const T& operator*() const                        OK
                    const T* operator->() const                       OK
                    const_iterator& operator++()                      OK
                    const_iterator operator++(int)                    OK
                    const_iterator& operator--()                      OK
                    const_iterator operator--(int)                    OK
                    bool operator==(const const_iterator&) const      OK
                    bool operator!=(const const_iterator&) const      OK

  for RBTree:
                    void insert(const T& value)
                    bool contains(const T& value)---->Bibeknam's searchTreeHelper 
                    void delete(const T& value) 
                    RBTree<T, CMP>::const_iterator begin() const
                    RBTree<T, CMP>::const_iterator end() const
*/

#endif // RBT_HPP