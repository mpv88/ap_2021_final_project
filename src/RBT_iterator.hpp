///\file RBT_iterator.hpp
///\author mpv
///\brief implementation of RBT's iterator and const_iterator sub-classes.


#ifndef RBT_ITERATOR_HPP
#define RBT_ITERATOR_HPP

#include "Node.hpp"
#include "RBT.hpp"


///\brief RBTree's constant iterator class.
///       Used to iterate over a sequence and access only RBTree's elements.
template <class T, class CMP> 
class RBTree<T, CMP>::const_iterator {
  friend class RBTree;

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
    return &(*(*(this)));
  }


  ///\brief RBTree's constant iterator prefix ++ operator (i.e. ++IT).
  ///\return Reference const_iterator to the new current RBTree node, after advancing IT. 
  ///       Used to pre-increment the RBTree's const_iterator.
  ///       Reference: https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
  const_iterator& operator++() {
    //current_node = current_node->successor();
    //return *this;
    if(current_node) {
      if(current_node->right) {
        current_node = current_node->right->leftmost();
      } else {
        current_node = current_node->rightmost();
      }
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
    current_node = current_node->predecessor();
    return *this;
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
  bool operator!=(const const_iterator& other) const {
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

#endif //RBT_ITERATOR_HPP