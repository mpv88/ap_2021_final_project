///\file RBT_Node.hpp
///\author mpv
///\brief header file with the implementation of RBT's node.

#ifndef NODE_HPP
#define NODE_HPP


enum Color { BLACK=0, RED=1 }; ///< enumerated type color declaration.


///\brief RBTree's single node, each node bears a key and a color (red or black).
///       Each node has a parent and two children (left and right).
template <class T> 
class _Node {
public:
  T data;                      ///< template key of the node.
  Color color;                 ///< color of the node.
  _Node *left, *right, *parent; ///< pointers to parent, left and right children.

  ///\brief Default Constructor of a RBTree's node.
  ///
  _Node() {}

  ///\brief Constructor of a new node given a key and (optionally) color and parent. 
  ///\param k key which will be inserted into the node.
  ///\param clr color of the node (default set to BLACK).
  ///\param p pointer to the parent node.
  /// Initializer List initializes the data members of a class,
  /// default color is BLACK, default parent is NULL [overloaded].
  _Node(T k, Color clr=BLACK, _Node *p=nullptr) : data{k}, color{clr}, left{nullptr}, right{nullptr}, parent{p} {}

};

#endif // NODE_HPP