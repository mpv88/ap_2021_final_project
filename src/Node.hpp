///\file RBT_Node.hpp
///\author mpv
///\brief header file with the implementation of RBT's node.

#ifndef NODE_HPP
#define NODE_HPP


enum Color { BLACK=0, RED=1 }; ///< enumerated type, colors' declaration.


///\brief RBTree's single node, each node bears a key and a color (red or black).
///       Each node has a parent and two children (left and right).
template <class T> 
class _Node {
public:

  T data;                      ///< templated key of the node.
  Color color;                 ///< color of the node.
  _Node *left, *right, *parent; ///< pointers to parent, left and right children.


  ///\brief Default Constructor of a RBTree's node.
  ///
  _Node() noexcept {}


  ///\brief Constructor of a new node given a key and (optionally) color and parent. 
  ///\param key key which will be inserted into the node.
  ///\param clr color of the node (default set to BLACK).
  ///\param parent pointer to the parent node (default set to nullptr).
  /// Initializer List initializes the data members of a class,
  /// default color is BLACK, default parent is empty [overloaded].
  _Node(T key, Color clr=BLACK, _Node *parent=nullptr) noexcept: data{key}, color{clr}, left{nullptr}, right{nullptr}, parent{parent} {}


  ///\brief Destructor of a RBTree's node.
  ///
  ~_Node() noexcept {}


  ///\brief Copy constructor for RBTree's single node.
	///\param node The RBTree's node which will be copied to another node.
	///\return A copy of RBTree' node, by means of a call to the constructor.
  _Node(const _Node &node) noexcept: data{node.data}, color{node.color}, left{node.left}, right{node.right}, parent{node.parent} {}


  ///\brief Move constructor for RBTree's single node.
	///\param rbt The rvalue reference to a RBTree's node which will be moved to another new node.
  ///\return The moved RBTree.
  _Node(_Node &&node) noexcept: data{std::move(node.data)}, color{std::move(node.color)}, left{std::move(node.left)}, right{std::move(node.right)}, parent{std::move(node.parent)} {}


  ///\brief Starting from a node, follows recursively the path towards the leftmost element. 
  ///\return A pointer which points to the leftmost node.
  _Node* f_leftmost() noexcept {
    if(left!=nullptr and left->data!=0) { //neither out of tree nor a leaf
      return left->f_leftmost();
    }
    return this;
  }


  ///\brief Starting from a node, follows recursively the path towards the rightmost element. 
  ///\return A pointer which points to the rightmost node.
  _Node* b_rightmost() noexcept {
    if(right!=nullptr and right->data!=0) { //neither out of tree nor a leaf
      return right->b_rightmost();
    }
    return this;
  }


  ///\brief Starting from a node, follows recursively the path towards the closest right ancestor. 
  ///\return A pointer which points to the most close right ancestor node.
  _Node* f_rightmost() const noexcept {
    if(parent!=nullptr and parent->data!=0) { //neither out of tree nor a leaf
      if(parent->right==this) { //if this is the right child of its parent
        return parent->f_rightmost(); //go up and repeat
      }
    }
	  return parent; //if this is the left child of its parent
  }


  ///\brief Starting from a node, follows recursively the path towards the closest left ancestor. 
  ///\return A pointer which points to the most close left ancestor node.
  _Node* b_leftmost() const noexcept {
    if(parent!=nullptr and parent->data!=0) { //neither out of tree nor a leaf
      if(parent->left==this) { //if this is the left child of its parent
        return parent->b_leftmost(); //go up and repeat
      }
    }
	  return parent; //if this is the right child of its parent
  }


  ///\brief Getter for the data stored within the RBTree's node. 
  ///\return Reference to the data contained inside a node's instance.
  const T& get_data() const noexcept {
    return data;
  }


  ///\brief Getter for the left child of a RBTree's node. 
  ///\return Reference to the node's left child.
  const _Node*& get_left() const noexcept {
    return left;
  }


///\brief Getter for the right child of a RBTree's node. 
///\return Reference to the node's right child.
  const _Node*& get_right() const noexcept {
    return right;
  }


///\brief Getter for the parent of a RBTree's node. 
///\return Reference to the node's parent.
const _Node*& get_parent() const noexcept {
    return parent;
  }

};


#endif // NODE_HPP