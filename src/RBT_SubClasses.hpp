///\file RBT_Subclasses.hpp
///\author mpv
///\brief implementation of RBT's sub-classes (iterator and const_iterator).

#ifndef RBTSUBC_HPP
#define RBTSUBC_HPP

#include "RBT.hpp"

enum Color { BLACK = 0, RED = 1 }; ///< enumerated type color declaration.

///\brief RBTree's single node, each node bears a key and a color (red or black).
///       Each node has a parent and two children (left and right).
template <class T, class CMP> 
class RBTree<T, CMP>::Node {

public:
  <const T> data;              ///< template key of the node.
  Color color;                 ///< color of the node (black=0 or red=1).
  Node *left, *right, *parent; ///< pointers to parent, left and right children.

  ///\brief Default Constructor of a RBTree's node.
  ///
  Node() {}

  ///\brief Constructor of a new node given a key and (optionally) color and parent. 
  ///\param k key which will be inserted into the node.
  ///\param clr color of the node (default set to BLACK).
  ///\param p pointer to the parent node.
  /// Initializer List initializes the data members of a class,
  /// default color is BLACK, default parent is NULL [overloaded].
  Node(<T> k, Color clr=BLACK, Node *p=nullptr) : data{k}, color{clr}, left{nullptr}, right{nullptr}, parent{p} {}

};


///\brief RBTree's constant iterator class.
///       Used to iterate over a sequence and access only RBTree's elements.
template <class T, class CMP> 
class RBTree<T, CMP>::const_iterator {
  friend class RBTree;
  typedef RBTree<T, CMP>::Node *NodePtr;

private:
  NodePtr current_node; ///< node currently pointed by the iterator.
  
public:

  ///\brief RBTree's constant iterator constructor.
  ///\param node RBTree's node over which const iterator is constructed.
  explicit const_iterator(NodePtr node) : current_node{node} {}


  ///\brief RBTree's constant iterator destructor.
  ///       RBTree's const iterator is deleted.
    ~const_iterator() {}


  ///\brief RBTree's constant iterator indirection/deference operator.
  ///\return Const T reference to the node pointed (i.e. current) by the iterator. 
  ///       Used to get the value associated to the RBTree's const_iterator.
  const T& operator*() const {
    return current_node->data;
  }  


  ///\brief RBTree's constant iterator member access operator.
  ///\return Const T pointer to the node pointed (i.e. current) by the iterator. 
  ///       Used to access the value associated to the RBTree's const_iterator.
  const T* operator->() const {
    return &(*(*(this));
  }


  ///\brief RBTree's constant iterator prefix ++ operator (i.e. ++IT).
  ///\return Reference const_iterator to the new current RBTree node, after advancing IT. 
  ///       Used to pre-increment the RBTree's const_iterator.
  ///       Reference: https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
  const_iterator& operator++() {
  if (current_node==nullptr) { //case A: RBTree current node is empty //
    current_node = tree->root; // move to root #FIXME: need RBT::get_root()
      if (current_node==nullptr) //case A: RBTree current node is empty //
        throw UnderflowException { }; // get error (if RBTree is empty)
      while (current_node->left!=nullptr) { 
        current_node = current_node->left; //get tree's leftmost node (smallest)
        }
    }
  else if (current_node->right!=nullptr) { //case B: right child isn't empty
    current_node = current_node->right; // move to right child
    while (current_node->left!=nullptr) {
        current_node = current_node->left; // get Rsubtree's leftmost child (smallest)
        }
    }
  else {                         //case C: remaining cases (no right child)   
         NodePtr p {current_node->parent}; // keep track of parent
         while (p!=nullptr && current_node==p->right) { // move up the tree
            current_node = p; //get parent for which current node is left child
            p = p->parent; //move up increment
          }
        current_node = p; //if parent is empty
    }
  return *this;
  }     


  ///\brief RBTree's constant iterator postfix ++ operator (i.e. IT++).
  ///\return Const iterator to previously current node, after advancing IT. 
  ///       Used to post-increment the RBTree's const_iterator [overloaded].
  const_iterator operator++(int) {
    const_iterator retval{*this};
	++(*this);
	return retval;
  }


  ///\brief RBTree's constant iterator prefix -- operator (i.e. --IT).
  ///\return Reference const_iterator to the new current RBTree node, after moving backwards IT. 
  ///       Used to pre-decrement the RBTree's const_iterator.
  const_iterator& operator--() {

  }


  ///\brief RBTree's constant iterator postfix -- operator (i.e. IT--).
  ///\return Const iterator to previously current node, after moving backwards IT. 
  ///       Used to post-decrement the RBTree's const_iterator [overloaded].
  const_iterator operator--(int) {
    const_iterator retval{*this};
	--(*this);
	return retval;
  }


  ///\brief RBTree's constant iterator equality operator.
  ///\return Bool: true if both iterators point to the same node.
  ///       Used to to test whether two iterators are equivalent.
  bool operator==(const const_iterator& other) const {
    return current_node == other.current_node;
  }


  ///\brief RBTree's constant iterator disequality operator.
  ///\return Bool: false if both iterators point to the same node.
  ///       Used to to test whether two iterators are different.
  bool operator!=(const const_iterator&) const {
    return current_node != other.current_node;
  }

};

//TODO: a sketch class for showing inheritance
///\brief RBTree's regular iterator class.
///       Used to iterate over a sequence and manipulate RBTree's elements.
template <class T, class CMP> 
class RBTree<T, CMP>::iterator: public RBTree<T, CMP>::const_iterator {


private:


public:



};

#endif //RBTSUBC_HPP