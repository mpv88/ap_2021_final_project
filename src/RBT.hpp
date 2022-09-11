///\file RBT.hpp
///\author mpv
///\brief header file with all RBT's members' declarations and methods' definition.

#ifndef RBT_HPP
#define RBT_HPP

#include <iostream>
#include "Node.hpp"


///\brief RBTree is a template class which implements R. Bayer's Red Black Tree (1972).
///\param T type of the tree nodes' keys.
///\param CMP relational function to compare nodes' keys (default std::less<T>).
template <class T, class CMP=std::less<T>> 
class RBTree {

public:
  typedef T node_type; ///< type of the tree nodes' keys.
  typedef _Node<node_type> Node; ///< type of template tree node.
  typedef Node *NodePtr; ///< type of pointer to template tree node.


  ///\brief RBTree's regular iterator class.
  ///       Used to iterate over a sequence and manipulate RBTree's elements.
  class iterator;

  ///\brief RBTree's constant iterator class.
  ///      Used to iterate over a sequence and access only RBTree's elements.
  class const_iterator;


private:
  NodePtr root; ///< root of the RBTree (always black)
  NodePtr NIL; ///< leaf of the RBTree (always black)

  ///\brief Function to get the root of the RBTree.
	///\return A pointer to RBTree's root.
  NodePtr get_root() const;


  //SPECIALS:
  void preOrderHelper(NodePtr node) const;
  void inOrderHelper(NodePtr node) const;
  void postOrderHelper(NodePtr node) const;
  NodePtr searchTreeHelper(NodePtr node, T key) const;
  void fixDelete(NodePtr x);
  void rbTransplant(NodePtr u, NodePtr v);
  void deleteNodeHelper(NodePtr node, T key);
  void fixInsert(NodePtr k);
  void printHelper(NodePtr rt, std::string indent, bool last);






public:
  CMP comparator; ///< comparison operator. 


  ///\brief RBTree's constructor.
  ///       Default constructor for the RBTree class.
  RBTree() noexcept {root = NIL = new Node;}


	///\brief Constructor for RBTree given the root node.
	///\param value The value to be inserted into the RBTree's root node.
	///\param cmp A custom comparison function for tree nodes (defaulted to std::less).
	RBTree(T value, CMP cmp=CMP{}) : root{new Node{value}}, comparator{cmp}, NIL{new Node} {}


  ///\brief RBTree's destructor.
  ///       Default destructor for the RBTree class.
  ~RBTree() {}
   
//--------------------------------------------------------------------
  ///\brief Copy constructor for RBTree.
	///\param rbt The RBTree which will be copied to a new one.
	///\param cmp A custom comparison function for tree nodes (defaulted to std::less).
  RBTree(const RBTree &rbt) {
    root = copy(rbt.root);
  }
 

  ///\brief Copy assignment for RBTree.
	///\param rbt The RBTree which is going to be copied.
	///\param cmp A custom comparison function for tree nodes (defaulted to std::less).
  RBTree& operator=(const RBTree &rbt) {
    root.reset();
    auto tmp = rbt; 
    *this = std::move(tmp);
    return *this;
  }


  ///\brief Move constructor for RBTree.
	///\param rbt The RBTree which will be moved into a new one.
	RBTree(RBTree&& rbt) noexcept : root{std::move(rbt.root)} {}

  ///\brief Move assignment for RBTree.
	///\param rbt The RBTree which will be moved into a new one.
	RBTree& operator=(RBTree&& rbt) {
    if (this!=&rbt) {
      delete this->root;
      root = std::move(rbt.root);
    }
  }
 
//--------------------------------------------------------------------

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
  void delete_(const T& value);


  ///\brief Function to get a constant tree iterator over all the tree keys.
	///\return RBTree's const_iterator to the in-order first element of the tree.
  RBTree<T, CMP>::const_iterator begin() const;


  ///\brief Function to get the last value for a tree iterator.
	///\return A RBTree without the node which contained the value inserted.
  RBTree<T, CMP>::const_iterator end() const;

  ///\brief Wrapper function to print .
	///\return A RBTree without the node which contained the value inserted.
  void inorder() const;


  void preorder() const;
  void postorder() const;
  void printTree(); //const?
  NodePtr minimum(NodePtr node); //const?
  NodePtr maximum(NodePtr node); //const?
  NodePtr successor(NodePtr node); //const?
  NodePtr predecessor(NodePtr node); //const?

  // to become private
  void leftRotate(NodePtr node);
  void rightRotate(NodePtr node);
  

};


// private methods

template <class T, class CMP>
void RBTree<T, CMP>::preOrderHelper(NodePtr node) const {
  if (node!=NIL) {
    std::cout << node->data << " | ";
    preOrderHelper(node->left);
    preOrderHelper(node->right);
  }
}

template <class T, class CMP>
void RBTree<T, CMP>::inOrderHelper(NodePtr node) const {
  if (node!=NIL) {
    inOrderHelper(node->left);
    std::cout << node->data << " | ";
    inOrderHelper(node->right);
  }
}

template <class T, class CMP>
void RBTree<T, CMP>::postOrderHelper(NodePtr node) const {
  if (node!=NIL) {
    postOrderHelper(node->left);
    postOrderHelper(node->right);
    std::cout << node->data << " | ";
  }
}



template <class T, class CMP>
void RBTree<T, CMP>::fixDelete(NodePtr x) {
  NodePtr s;
  while (x->color==BLACK and x!=root) {
    if (x==x->parent->left) {
      s=x->parent->right;
      if (s->color==RED) { 
        // case 3.1
        s->color=BLACK;
        x->parent->color=RED;
        leftRotate(x->parent);
        s=x->parent->right;
      }
      if (s->right->color==BLACK and s->left->color==BLACK) {
        // case 3.2
        s->color=RED;
        x=x->parent;
      } else {
        if (s->right->color==BLACK) {
          // case 3.3
          s->left->color=BLACK;
          s->color=RED;
          rightRotate(s);
          s=x->parent->right;
        }
        // case 3.4
        s->color=x->parent->color;
        x->parent->color=BLACK;
        s->right->color=BLACK;
        leftRotate(x->parent);
        x=root;
      }
    } else {
      s=x->parent->left;
      if (s->color==RED) {
        // case 3.1
        s->color=BLACK;
        x->parent->color=RED;
        rightRotate(x->parent);
        s=x->parent->left;
      }
      if (s->left->color==BLACK and s->right->color==BLACK) {
        // case 3.2
        s->color=RED;
        x=x->parent;
      } else {
        if (s->left->color==BLACK) {
          // case 3.3
          s->right->color=BLACK;
          s->color=RED;
          leftRotate(s);
          s=x->parent->left;
        }
        // case 3.4
        s->color=x->parent->color;
        x->parent->color=BLACK;
        s->left->color=BLACK;
        rightRotate(x->parent);
        x=root;
      }
    }
  }
  x->color=BLACK;
}


template <class T, class CMP>
void RBTree<T, CMP>::rbTransplant(NodePtr u, NodePtr v) {
  if (u->parent==NIL) {
    root=v;
  } else if (u==u->parent->left) {
    u->parent->left=v;
  } else {
    u->parent->right=v;
  }
  v->parent=u->parent;
}


template<class T, class CMP>
void RBTree<T, CMP>::deleteNodeHelper(NodePtr node, T key) {
  NodePtr z=NIL;
  NodePtr x, y;
  while (node!=NIL) {
    if (node->data==key) {
      z=node;
    }
    if (node->data <= key) {
      node=node->right;
    } else {
      node=node->left;
    }
  }
  if (z==NIL) {
    std::cout << "Couldn't find key " << key << " in the tree" <<std::endl;
    return;
  }
  y=z;
  Color y_original_color=y->color;
  if (z->left==NIL) {
    x=z->right;
    rbTransplant(z, z->right);
  } else if (z->right==NIL) {
    x=z->left;
    rbTransplant(z, z->left);
  } else {
    y=minimum(z->right);
    y_original_color=y->color;
    x=y->right;
    if (y->parent==z) {
      x->parent=y;
    } else {
      rbTransplant(y, y->right);
      y->right=z->right;
      y->right->parent=y;
    }
    rbTransplant(z, y);
    y->left=z->left;
    y->left->parent=y;
    y->color=z->color;
  }
  delete z;
  if (y_original_color==BLACK) {
    fixDelete(x);
  }
}

template<class T, class CMP>
void RBTree<T, CMP>::fixInsert(NodePtr k) {
  NodePtr u;
  while (k->parent->color == RED) {
    if (k->parent == k->parent->parent->right) {
      u = k->parent->parent->left; // uncle
      if (u->color == RED) {
        // case 3.1
        u->color = BLACK;
        k->parent->color = BLACK;
        k->parent->parent->color = RED;
        k = k->parent->parent;
      } else {
        if (k == k->parent->left) {
          // case 3.2.2
          k = k->parent;
          rightRotate(k);
        }
        // case 3.2.1
        k->parent->color = BLACK;
        k->parent->parent->color = RED;
        leftRotate(k->parent->parent);
      }
    } else {
      u = k->parent->parent->right; // uncle

      if (u->color == RED) {
        // mirror case 3.1
        u->color = BLACK;
        k->parent->color = BLACK;
        k->parent->parent->color = RED;
        k = k->parent->parent;
      } else {
        if (k == k->parent->right) {
          // mirror case 3.2.2
          k = k->parent;
          leftRotate(k);
        }
        // mirror case 3.2.1
        k->parent->color = BLACK;
        k->parent->parent->color = RED;
        rightRotate(k->parent->parent);
      }
    }
    if (k == root) {
      break;
    }
  }
  root->color = BLACK;
}

template<class T, class CMP>
void RBTree<T, CMP>::printHelper(NodePtr root, std::string indent, bool last) {
  if (root!=nullptr) {
    std::cout << indent;
    if (last) {
      std::cout << "R----";
      indent += "     ";
    } else {
      std::cout << "L----";
      indent += "|    ";
    }
    std::string sColor = root->color ? "RED" : "BLACK";
    std::cout << root->data << "(" << sColor << ")" << std::endl;
    printHelper(root->left, indent, false);
    printHelper(root->right, indent, true);
  }
}


// public methods
/*template<class T, class CMP>
 void RBTree<T, CMP>::preorder() const {
    preOrderHelper(this->root);
} */

template<class T, class CMP>
void RBTree<T, CMP>::preorder() const {
  preOrderHelper(this->root);
}


template<class T, class CMP>
void RBTree<T, CMP>::inorder() const {
  inOrderHelper(this->root);
}


template<class T, class CMP>
void RBTree<T, CMP>::postorder() const {
  postOrderHelper(this->root);
}


template<class T, class CMP>
typename RBTree<T, CMP>::NodePtr RBTree<T, CMP>::minimum(NodePtr node) {
  while (node->left!=NIL) {
    node = node->left;
  }
  return node;
}


template<class T, class CMP>
typename RBTree<T, CMP>::NodePtr RBTree<T, CMP>::maximum(NodePtr node) {
  while (node->right!=NIL) {
    node = node->right;
  }
  return node;
}


template<class T, class CMP>
typename RBTree<T, CMP>::NodePtr RBTree<T, CMP>::successor(NodePtr node) {
  if (node->right!=NIL) {
    return minimum(node->right);
  }
  NodePtr p = node->parent;
  while (node==p->right and p!=NIL) {
    node = p;
    p = p->parent;
  }
  return p;
}


template<class T, class CMP>
typename RBTree<T, CMP>::NodePtr RBTree<T, CMP>::predecessor(NodePtr node) {
  if (node->left!=NIL) {
    return maximum(node->left);
  }
  NodePtr p = node->parent;
  while (node==p->left and p!=NIL) {
    node = p;
    p = p->parent;
  }
  return p;
}


template <class T, class CMP>
void RBTree<T, CMP>::leftRotate(NodePtr node) {
  NodePtr right_node = node->right;
  node->right = right_node->left;
  if (right_node->left!=NIL) {
    right_node->left->parent = node;
  }
  right_node->parent = node->parent;
  if (node->parent==nullptr) {
    this->root = right_node;
  } else if (node==node->parent->left) {
    node->parent->left = right_node;
  } else {
    node->parent->right = right_node;
  }
  right_node->left = node;
  node->parent = right_node;
}


template <class T, class CMP>
void RBTree<T, CMP>::rightRotate(NodePtr node) {
  NodePtr left_node = node->left;
  node->left = left_node->right;
  if (left_node->right!=NIL) {
    left_node->right->parent = node;
  }
  left_node->parent = node->parent;
  if (node->parent==nullptr) {
    this->root = left_node;
  } else if (node==node->parent->right) {
    node->parent->right = left_node;
  } else {
    node->parent->left = left_node;
  }
  left_node->right = node;
  node->parent = left_node;
}


template <class T, class CMP>
void RBTree<T, CMP>::insert(const T& value) {
  NodePtr node{new Node(value, RED, nullptr)};
  node->left = node->right = NIL;
  NodePtr y{nullptr};
  NodePtr x{this->root};
  while (x!=NIL) {
    y = x;
    if (comparator(node->data, x->data)) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  node->parent = y;
  if (y==nullptr) {
    this->root = node;
  } else if (comparator(node->data, y->data)) {
    y->left = node;
  } else {
    y->right = node;
  }
  if (node->parent==nullptr) {
    node->color = BLACK;
    return;
  }
  if (node->parent->parent==nullptr) {
    return;
  }
  fixInsert(node);
}


template <class T, class CMP>
void RBTree<T, CMP>::delete_(const T& value) {
  deleteNodeHelper(this->root, value);
}


template <class T, class CMP>
void RBTree<T, CMP>::printTree() {
  if (root!=nullptr) {
    printHelper(this->root, "", true);
  } else {
    std::cout << "Empty Tree" << std::endl;
  }
}

template <class T, class CMP>
typename RBTree<T, CMP>::NodePtr RBTree<T, CMP>::get_root() const {
  if(this->root==nullptr) {
    return nullptr;
  }
  return this->root;
}


template <class T, class CMP>
bool RBTree<T, CMP>::contains(const T& value) const {
  if (searchTreeHelper(this->root, value)->data==value) {
    return true;
  } else {
    return false;
  }
}


template <class T, class CMP>
typename RBTree<T, CMP>::NodePtr RBTree<T, CMP>::searchTreeHelper(NodePtr node, T key) const {
  if (key==node->data or node==NIL) {
    return node;
  }
  if (comparator(key, node->data)) {
    return searchTreeHelper(node->left, key);
  } else {
    return searchTreeHelper(node->right, key);
  }
}

template <class T, class CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::begin() const {
  return const_iterator(minimum(this->root));
}


template <class T, class CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::end() const {
  return const_iterator(NIL);
}



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
                    const_iterator& operator--()                      NOT OK
                    const_iterator operator--(int)                    OK
                    bool operator==(const const_iterator&) const      OK
                    bool operator!=(const const_iterator&) const      OK
  for RBTree:
                    void insert(const T& value)                       OK
                    void delete(const T& value)                       OK
                    bool contains(const T& value) const               OK    
                    RBTree<T, CMP>::const_iterator begin() const      OK
                    RBTree<T, CMP>::const_iterator end() const        OK

1) update doxygen                                                     OK
2) check segmentation fault from root node                            OK
3) check instances of to-be-changed methods                          in progress...
4) replace with to-be-changed methods (N.B. use the comparator->OK)
_
5) check if all methods are implemented
6) terminate regular iterator + inheritance on const_iter
7) set up unit test suite:
while with 50 int, same with 50 double, test iteratorS, print tree, test find,
print inorder traversal, etc..
*/

#include "RBT_iterator.hpp"
#endif // RBT_HPP