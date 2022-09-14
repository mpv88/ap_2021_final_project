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
  friend class const_iterator; //allows const_iterator using leftmost() and rightmost()

  T data;                      ///< template key of the node.
  Color color;                 ///< color of the node.
  _Node *left, *right, *parent; ///< pointers to parent, left and right children.

  ///\brief Default Constructor of a RBTree's node.
  ///
  _Node() {}

  ///\brief Constructor of a new node given a key and (optionally) color and parent. 
  ///\param key key which will be inserted into the node.
  ///\param clr color of the node (default set to BLACK).
  ///\param parent pointer to the parent node.
  /// Initializer List initializes the data members of a class,
  /// default color is BLACK, default parent is empty [overloaded].
  _Node(T key, Color clr=BLACK, _Node *left=nullptr, _Node *right=nullptr, _Node *parent=nullptr) : data{key}, color{clr}, left{left}, right{right}, parent{parent} {}

  ///\brief Destructor of a RBTree's node.
  ///
  ~_Node() noexcept {}


  ///\brief Starting from a node, follows recursively the path towards the leftmost element. 
  ///\return A pointer which points to the leftmost (smallest) key.
  _Node* leftmost() noexcept {
    if(left) {
      return left->leftmost();
    }
    return this;
  }


  ///\brief Starting from a node, follows recursively the path towards the lowest right ancestor. 
  ///\return A pointer which points to the rightmost (largest) key.
  _Node* rightmost() const {
    if(parent) {
      if(parent->right==this) {
        return parent->rightmost();
      }
    }
	  return parent;
  }


};


#endif // NODE_HPP