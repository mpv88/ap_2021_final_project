///\file RBT.hpp
///\author mpv
///\brief header file with all RBT's members' declarations.

#ifndef RBT_HPP
#define RBT_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// FIXME:
//  definition of new types:
typedef Node *NodePtr;

///\brief RBTree is a template class which implements R. Bayer's Red Black Tree
///(1972) \param T type of the tree nodes' keys \param CMP relational function
/// to compare nodes' keys (default set to std::less<T>)
template <class T, class CMP = std::less<T>> class RBTree {

protected:
  ///\brief RBTree's single node, each node bears a key and a color (red or
  /// black)
  ///       each node has a parent and two children (left and right)
  class Node; // FIXME: maybe struct?

public:
  ///\brief RBTree's regular iterator class
  ///       used to iterate over a sequence and manipulate RBTree's elements
  class iterator;

  ///\brief RBTree's constant iterator class
  ///       used to iterate over a sequence and access only RBTree's elements
  class const_iterator;

protected:
  std::unique_ptr<Node> root; ///< root of the tree (always black)

  NodePtr TNULL;

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

#endif // RBT_HPP

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
                    bool contains(const T& value)         ----> see Bibeknam's
searchTreeHelper void delete(const T& value) RBTree<T, CMP>::const_iterator
begin() const RBTree<T, CMP>::const_iterator end() const
*/