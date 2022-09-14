///\file RBT.hpp
///\author mpv
///\brief header file with all RBT's members' declarations and methods' definitionss.

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
  NodePtr NIL; ///< empty (leaf) node of the RBTree (always black)


  ///\brief A recursive helper function to create a deep copy of a RBTree.
  ///\param copied The starting node for exploring the RBTree, typically its root.
  ///\param new_parent Supplied parent node in case needed (starting: nullptr).
  ///\param other_rbt The starting node for exploring the RBTree, typically its root.
  ///\return A deep copy of the original RBTree provided.
  void copy(NodePtr& copied, NodePtr new_parent, NodePtr other_rbt);


  ///\brief A recursive helper function to print RBTree's keys (see: print_ordered_keys).
  ///\param root The starting node for exploring the RBTree, typically its root.
  ///\param choice A const integer to explicit which type of traversal you want.
  ///\return Prints the ordered keys of RBTree following the type of traversal chosen.
  void recursive_ordering(NodePtr root, int choice) const;


  ///\brief A recursive helper function to find a RBTree's node given its key (see: contains).
  ///\param root The starting node for exploring the RBTree, typically its root.
  ///\param value The value of the key you are searching within the RBTree.
  ///\return Prints the ordered keys of RBTree following the type of traversal chosen.
  NodePtr recursive_search(NodePtr root, T value) const;


  ///\brief A recursive helper function to print the RBTree's structure (see: print_tree).
  ///\param root The starting node for exploring the RBTree, typically its root.
  ///\param indentation Specifies the degree of indentation for tree's branches.
  ///\param is_right Specifies if we are in the left or right sub-tree.
  ///\return Prints the complete branch-leaf structure of RBTree.
  void recursive_print(NodePtr root, std::string indentation, bool is_right) const;


  ///\brief Private utility function to help rebalance RBTree's after deletion (see: delete_adjustment).
  ///\param replaced The node we want to be replaced with the replacer node.
  ///\param replacer The node we want to be a replacement of replaced node.
  ///\return Modifies RBTree's structure, swapping one node with another.
  void node_replacement(NodePtr replaced, NodePtr replacer);
  

  ///\brief Private utility function to help rebalance RBTree's after insertion/deletion.
  ///\param node The node which constitutes the pivot point for the rotation.
  ///\param to_right Direction of desired rotation: 0=left (child up), 1=right (child down).
  ///\return Modifies RBTree's structure, performing a right/left rotation of nodes.
  void node_rotation(NodePtr node, bool to_right);


  ///\brief Private utility function to rebalance RBTree's after insertion (see: insert).
  ///\param node The node we are going to insert into the previous RBTree structure.
  ///\return Rebalances RBTree's to restore compliance with 5 rules that may have been infringed.
  void rebalance_on_insert(NodePtr node);


  ///\brief Private utility function to rebalance RBTree's after deletion (see: delete_adjustment).
  ///\param node The node we are going to delete from the previous RBTree structure.
  ///\return Rebalances RBTree's to restore compliance with 5 rules that may have been infringed.
  void rebalance_on_delete(NodePtr node);


  ///\brief Private helper function to rebalance RBTree's after key deletion (see: delete).
  ///\param node The starting node for visiting the RBTree, typically its root.
  ///\param value The value you are going to delete.
  ///\return Rebalanced RBTree's compliant with 5 rules, after implementing the deletion.
  void delete_adjustment(NodePtr node, T value);


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
   

  ///\brief Copy constructor for RBTree.
	///\param rbt The RBTree which will be copied to another new tree.
	///\return A 'deep copy' of RBTree, by means of a call to the constructor.
  RBTree(const RBTree &rbt) {
      copy(root, nullptr, rbt.root);  // deep copy
      //root = new Node (*rbt.root);  // shallow copy

}


  ///\brief Copy assignment for RBTree.
	///\param rbt A const lvalue reference to RBTree that will be copied to an existing tree.
	///\return The copy of the RBTree.
  RBTree& operator=(const RBTree& rbt) {
    if (this!=&rbt) {
      if (root!=nullptr) {
        //clear_tree(rbt.root);
      }
      copy(root, nullptr, rbt.root);
    }
  return *this;
}


  ///\brief Move constructor for RBTree.
	///\param rbt The rvalue reference to the RBTree which will be moved to another new tree.
  ///\return The moved RBTree.
	RBTree(RBTree&& rbt) noexcept: root{std::move(rbt.root)} {}


  ///\brief Move assignment for RBTree.
	///\param rbt The rvalue reference to RBTree that will be moved to an existing tree.
  ///\return The moved RBTree.
	RBTree& operator=(RBTree&& rbt) noexcept {
    if (this!=&rbt) {
      if (root!=nullptr) {
      //clear_tree(rbt.root);
      }
      root = std::move(rbt.root);
    } 
    return *this;
  }


  ///\brief Function to get the root of the RBTree.
	///\return A pointer to RBTree's root.
  NodePtr get_root() const;


  ///\brief Function to get the RBTree's height.
	///\param root The starting node for exploring the RBTree, typically its root.
	///\return The total height of the RBTree, as an integer levels count.
  int get_height(NodePtr root) const; 


  ///\brief A function to discover which is the leftmost node in RBTree.
  ///\param node The starting node for exploring the rest of the RBTree.
  ///\return A pointer to the leftmost node, which is the min key in the RBTree.
  NodePtr get_leftmost(NodePtr node) const;


  ///\brief A function to discover which is the rightmost node in RBTree.
  ///\param node The starting node for exploring the rest of the RBTree.
  ///\return A pointer to the rightmost node, which is the max key in the RBTree.
  NodePtr get_rightmost(NodePtr node) const;


  ///\brief Function to insert a new value in the tree.
	///\param value The value you are going to insert.
	///\return A RBTree which includes an additional node with the value inserted.
  void insert(const T& value);

  
  ///\brief Function to test whether the tree contains a value (see: recursive_search).
	///\param value The value to be checked if present within the RBTree.
	///\return Bool true (1) if the value is in the RBTree, false (0) otherwise.
  bool contains(const T& value) const;


  ///\brief Function to find a value in the RBTree (see: recursive_search).
	///\param value The value to be checked if present within the RBTree.
	///\return The value searched if present inside the tree, nothing otherwise.
  T find(const T& value) const;
  

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


  ///\brief A function to discover the successor of the current node.
  ///\param node The starting node for exploring the rest of the RBTree.
  ///\return A pointer to the successive node (one step to the right).
  NodePtr get_successor(NodePtr node) const;


  ///\brief A function to discover the predecessor of the current node.
  ///\param node The starting node for exploring the rest of the RBTree.
  ///\return A pointer to the preceding node (one step to the left).
  NodePtr get_predecessor(NodePtr node) const;


  ///\brief A wrapper function to print RBT's keys (see: recursive_ordering).
  ///\param choice The type of traversal: 1='in-order', 2='pre-order', 3='post-order'.
	///\return A call to recursive_ordering which prints the keys.
  void print_ordered_keys(int choice) const;


  ///\brief A wrapper function to print the RBTree (see: recursive_print).
	///\return The print of the complete RBTree structure.
  void print_tree() const;


  ///\brief Utility function to clear the whole RBTree.
	///\return A totally empty tree.
  void clear_tree() noexcept;
};
// --------------------------------IMPLEMENTATION------------------------------------------

// private methods

template <class T, class CMP>
void RBTree<T, CMP>::copy(NodePtr& copied, NodePtr new_parent, NodePtr other_rbt) {
  if (other_rbt==nullptr) {
    copied = nullptr;
  } else {
    copied = new Node;
    copied->data = other_rbt->data;
    copied->color = other_rbt->color;
    copied->parent = new_parent;
    copy(copied->left, copied, other_rbt->left);
    copy(copied->right, copied, other_rbt->right);
  }
}


template <class T, class CMP>
void RBTree<T, CMP>::recursive_ordering(NodePtr root, const int choice) const {
  if (root!=NIL) {
    switch (choice) {
      case 1: //in-order traversal (left-root-right)
        recursive_ordering(root->left, choice);
        std::cout << root->data << " | ";
        recursive_ordering(root->right, choice);
        break;
      case 2: //pre-order traversal (root-left-right)
        std::cout << root->data << " | ";
        recursive_ordering(root->left, choice);
        recursive_ordering(root->right, choice);
        break;
      case 3: //post-order traversal (left-right-root)
        recursive_ordering(root->left, choice);
        recursive_ordering(root->right, choice);
        std::cout << root->data << " | ";
        break;
      default:
        // choice doesn't match any available case (1, 2, 3)
        std::cout << "Invalid option, please review your choice";
        break;
    }
  }
}


template <class T, class CMP>
typename RBTree<T, CMP>::NodePtr RBTree<T, CMP>::recursive_search(NodePtr root, T value) const {
  if (value==root->data or root==NIL) {
    return root;
  }
  if (comparator(value, root->data)) {
    return recursive_search(root->left, value);
  } else {
    return recursive_search(root->right, value);
  }
}


template<class T, class CMP>
void RBTree<T, CMP>::recursive_print(NodePtr root, std::string indentation, bool is_right) const {
  std::string h_branch {"        "};
  if (root->right) {
    recursive_print(root->right, indentation+(is_right ? h_branch : "L"+h_branch), 1);
  }
  std::cout << indentation << " (" << "----- "; // 
  std::cout << root->data << " " << (root->color ? "RED" : "BLACK") << std::endl;
  if (root->left) {
      recursive_print(root->left, indentation+(is_right ? "R"+h_branch : h_branch), 0);
  }
}


template <class T, class CMP>
void RBTree<T, CMP>::node_replacement(NodePtr replaced, NodePtr replacer) {
  if (replaced->parent==NIL) { // if parent is root 
    root=replacer;   // A: replacer becomes new root
  } else if (replaced==replaced->parent->right) { // if node is right child
    replaced->parent->right=replacer; // B: replacer becomes right child
  } else {
    replaced->parent->left=replacer; // C: replacer becomes left child
  }
  replacer->parent=replaced->parent; // replacer's parent becomes node's parent
}


template <class T, class CMP>
void RBTree<T, CMP>::node_rotation(NodePtr node, bool to_right) {
  NodePtr _node;
  if (to_right) { // right rotation
    _node = node->left; // keep pivot left child
    node->left = _node->right; // pivot left becomes pivot left-right grandchild
    if (_node->right!=NIL) {
      _node->right->parent = node; // pivot's left-right grandchild's parent becomes pivot
      }
    _node->parent = node->parent; // pivot's left child's parent becomes pivot's parent 
    if (node->parent==nullptr) {
      this->root = _node; // root becomes pivot's left child
    } else if (node==node->parent->right) {
      node->parent->right = _node; // pivot's parent right child becomes pivot's left child
    } else {
      node->parent->left = _node; // pivot's parent left child becomes pivot's left child
    }
    _node->right = node; // pivot's left-right granchild becomes pivot
  } else { // left rotation
    _node = node->right; // keep pivot right child
    node->right = _node->left; // pivot right becomes pivot right-left grandchild
    if (_node->left!=NIL) {
      _node->left->parent = node; // pivot's right-left grandchild's parent becomes pivot
      }
    _node->parent = node->parent; // pivot's right child's parent becomes pivot's parent
    if (node->parent==nullptr) {
      this->root = _node; // root becomes pivot's right child
    } else if (node==node->parent->left) {
      node->parent->left = _node; // pivot's parent left child becomes pivot's right child
    } else {
      node->parent->right = _node; // pivot's parent right child becomes pivot's right child
    }
    _node->left = node; // pivot's right-left granchild becomes pivot
  }
  node->parent = _node; // pivot's parent becomes pivot's left or right child
}


template<class T, class CMP>
void RBTree<T, CMP>::rebalance_on_insert(NodePtr node) {
  // details on cases at sources:
  // https://en.wikipedia.org/wiki/Red-black_tree
  // https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
  while (node->parent->color==RED) { // parent is RED
    if (node->parent==node->parent->parent->right) { // if parent is right child
      NodePtr uncle{node->parent->parent->left}; // left uncle
      if (uncle->color==RED) { // case: L_uncle is RED (simple recolor)
        node->parent->parent->color = RED; // grandparent becomes RED
        node->parent->color = BLACK; // parent becomes BLACK
        uncle->color = BLACK; // uncle becomes BLACK
        node = node->parent->parent; // node becomes grandparent
      } else {
        if (node==node->parent->left) { // case: L_uncle is BLACK and node is left child
          node = node->parent; // node becomes parent
          node_rotation(node, 1); // right rotation
        }                            // case: L_uncle is BLACK and node is right child
        node->parent->parent->color = RED; // grandparent becomes RED
        node->parent->color = BLACK; // parent becomes BLACK
        node_rotation(node->parent->parent, 0); // left rotation
      }
    } else {  // if parent is left child
      NodePtr uncle{node->parent->parent->right}; // right uncle
      if (uncle->color==RED) { // case: R_uncle is RED (simple recolor)
        node->parent->parent->color = RED; // grandparent becomes RED
        node->parent->color = BLACK; // parent becomes BLACK
        uncle->color = BLACK; // uncle becomes BLACK
        node = node->parent->parent; // node becomes grandparent
      } else {
        if (node==node->parent->right) { // case: R_uncle is BLACK and node is right child
          node = node->parent; // node becomes parent
          node_rotation(node, 0); // left rotation
        }                            // case: R_uncle is BLACK and node is left child
        node->parent->parent->color = RED; // grandparent becomes RED
        node->parent->color = BLACK; // parent becomes BLACK
        node_rotation(node->parent->parent, 1); // right rotation
      }
    }
    if (node==root) {break;} // stop when node is root
  }
  root->color = BLACK; // keep root BLACK
}


template <class T, class CMP>
void RBTree<T, CMP>::rebalance_on_delete(NodePtr node) {
  // details on cases at sources:
  // https://en.wikipedia.org/wiki/Red-black_tree
  // https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
  while (node->color==BLACK and node!=root) { // node is BLACK and not root
    if (node==node->parent->left) { // if node is left child
      NodePtr sibiling{node->parent->right}; // right sibiling
      if (sibiling->color==RED) { // case: R_sibiling is RED (recolor and rotation)
        node->parent->color = RED; // parent becomes RED
        sibiling->color = BLACK; // sibiling becomes BLACK
        node_rotation(node->parent, 0); // left rotation
        sibiling = node->parent->right; // sibiling becomes anew parent right child
      }
      if (sibiling->right->color==BLACK and sibiling->left->color==BLACK) { // case: both R_sibiling's children are BLACK
        node = node->parent; // node becomes parent
        sibiling->color = RED; // sibiling becomes RED
      } else {
        if (sibiling->right->color==BLACK) { // case: R_sibiling's right child is BLACK and left child is RED
          sibiling->color = RED; // sibiling becomes RED
          sibiling->left->color = BLACK; // sibiling's left child becomes BLACK
          node_rotation(sibiling, 1); // right rotation
          sibiling = node->parent->right; // sibiling becomes anew parent right child
        } // case: R_sibiling's right child is RED
        sibiling->color = node->parent->color; // sibiling's color becomes parent's color
        sibiling->right->color = BLACK; // sibiling's right child becomes BLACK
        node->parent->color = BLACK; // parent becomes BLACK
        node_rotation(node->parent, 0); // left rotation
        node = root; // node becomes root
      }
    } else {   // if node is right child
      NodePtr sibiling{node->parent->left}; // left sibiling
      if (sibiling->color==RED) { // case: L_sibiling is RED (recolor and rotation)
        node->parent->color = RED; // parent becomes RED
        sibiling->color = BLACK; // sibiling becomes BLACK
        node_rotation(node->parent, 1); // right rotation
        sibiling = node->parent->left; // sibiling becomes anew parent left child
      }
      if (sibiling->left->color==BLACK and sibiling->right->color==BLACK) { // case: both L_sibiling's children are BLACK
        node = node->parent; // node becomes parent
        sibiling->color = RED; // sibiling becomes RED
      } else {
        if (sibiling->left->color==BLACK) { // case: L_sibiling's left child is BLACK and right child is RED
          sibiling->color = RED; // sibiling becomes RED
          sibiling->right->color = BLACK; // sibiling's right child becomes BLACK
          node_rotation(sibiling, 0); // left rotation
          sibiling = node->parent->left; // sibiling becomes anew parent left child
        } // case: L_sibiling's left child is RED
        sibiling->color = node->parent->color; // sibiling's color becomes parent's color
        sibiling->left->color = BLACK; // sibiling's left child becomes BLACK
        node->parent->color = BLACK; // parent becomes BLACK
        node_rotation(node->parent, 1); // right rotation
        node = root; // node becomes root
      }
    }
  }
  node->color = BLACK; // keep root BLACK
}


template<class T, class CMP>
void RBTree<T, CMP>::delete_adjustment(NodePtr node, T value) {
  NodePtr node_A{NIL}, node_B{NIL}, node_C{NIL}; // temporary helper nodes
  if(recursive_search(node, value)!=NIL) {
    node_A = recursive_search(node, value); // if found, node_A stores the node to be canceled
  } else {
    std::cout << "Value " << value << " not found" << std::endl;
    return;
  }
  node_B = node_A; // node_B becomes node_A
  Color B_color{node_B->color}; // save original color of node_B node
  if (node_A->left==NIL) { // case: node_A has no left child
    node_C = node_A->right; // node_C becomes node_A's right child
    node_replacement(node_A, node_A->right); // node_A is replaced by node_A's right child
  } else if (node_A->right==NIL) { // case: node_A has no right child
    node_C = node_A->left; // node_C becomes node_A's left child
    node_replacement(node_A, node_A->left); // node_A is replaced by node_A's left child
  } else { // case: node_A has both children
    node_B = get_leftmost(node_A->right); // node_B becomes node_A's right child's leftmost node
    B_color = node_B->color; // update color of node_B node
    node_C = node_B->right; // node_C becomes node_B's right child
    if (node_B->parent==node_A) { // subcase: node_B's parent equals node_A
      node_C->parent = node_B; // node_C's parent becomes node_B
    } else { // subcase: node_B's parent not equals node_A
      node_replacement(node_B, node_B->right); // node_B is replaced by node_B's right child
      node_B->right = node_A->right; // node_B's right child becomes node_A's right child
      node_B->right->parent = node_B; // node_B's right child's parent becomes node_B
    }
    node_replacement(node_A, node_B); // replace node_A with node_B
    node_B->left = node_A->left; // node_B's left child becomes node_A's left child
    node_B->left->parent = node_B; // node_B's left child's parent becomes node_B
    node_B->color = node_A->color; // node_B's color becomes node_A's color
  }
  delete node_A;
  if (B_color==BLACK) { // if node_B was BLACK, we need to fix the tree deleting node_C
    rebalance_on_delete(node_C);  
  }
}

// public methods

template <class T, class CMP>
typename RBTree<T, CMP>::NodePtr RBTree<T, CMP>::get_root() const {
  if(this->root==nullptr) {
    return nullptr;
  }
  return this->root;
}


template <class T, class CMP>
int RBTree<T, CMP>::get_height(NodePtr root) const {
  if (root==NIL) {
    return 0;
  }
  return std::max(get_height(root->left), get_height(root->right))+1; 
} 


template<class T, class CMP>
typename RBTree<T, CMP>::NodePtr RBTree<T, CMP>::get_leftmost(NodePtr node) const {
  while (node->left!=NIL) {
    node = node->left;
  }
  return node;
}


template<class T, class CMP>
typename RBTree<T, CMP>::NodePtr RBTree<T, CMP>::get_rightmost(NodePtr node) const {
  while (node->right!=NIL) {
    node = node->right;
  }
  return node;
}


template <class T, class CMP>
void RBTree<T, CMP>::insert(const T& value) {
  NodePtr node{new Node(value, RED)};
  node->left = node->right = NIL;
  NodePtr node_B{nullptr}; // temporary helper node_B
  NodePtr node_A{get_root()}; // temporary helper node_A
  while (node_A!=NIL) { // root is different than NIL
    node_B = node_A; // node_B becomes node_A
    if (comparator(node->data, node_A->data)) {
      node_A = node_A->left; 
    } else if (comparator(node_A->data, node->data)) {
      node_A = node_A->right;
    } else {  // key already present
      std::cout << "Value " << value << " already in the RBTree" << std::endl;
      return;
    }
  }
  node->parent = node_B; // node's parent becomes node_B
  if (node_B==nullptr) {
    this->root = node;  // if tree was empty, node becomes root
  } else if (comparator(node->data, node_B->data)) { // if node's data is smaller than node_B's data
    node_B->left = node; // node becomes node_B's left child
  } else { // if node's data is equal or bigger than node_B's data
    node_B->right = node; // node becomes node_B's right child
  }
  if (node->parent==nullptr) { // recolor when node's parent is NIL
    node->color = BLACK;
    return;
  }
  if (node->parent->parent==nullptr) {
    return;
  }
  rebalance_on_insert(node);
}


template <class T, class CMP>
bool RBTree<T, CMP>::contains(const T& value) const {
  if (recursive_search(get_root(), value)->data==value) {
    return true;
  } else {
    return false;
  }
}


template <class T, class CMP>
T RBTree<T, CMP>::find(const T& value) const {
    return recursive_search(root, value)->data;
}


template <class T, class CMP>
void RBTree<T, CMP>::delete_(const T& value) {
  delete_adjustment(get_root(), value);
}


template <class T, class CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::begin() const {
  return const_iterator(get_leftmost(get_root()));
}


template <class T, class CMP>
typename RBTree<T, CMP>::const_iterator RBTree<T, CMP>::end() const {
  return const_iterator(nullptr);
}


template<class T, class CMP>
typename RBTree<T, CMP>::NodePtr RBTree<T, CMP>::get_successor(NodePtr node) const {
  if (node->right!=NIL) {
    return get_leftmost(node->right);
  }
  while (node==node->parent->right and node->parent!=NIL) {
    // lowest grandparent whose left child is a node's ancestor as well
    node = node->parent;
    node->parent = node->parent->parent;
  }
  return node->parent;
}


template<class T, class CMP>
typename RBTree<T, CMP>::NodePtr RBTree<T, CMP>::get_predecessor(NodePtr node) const {
  if (node->left!=NIL) {
    return get_rightmost(node->left);
  }
  while (node==node->parent->left and node->parent!=NIL) {
    // lowest grandparent whose right child is a node's ancestor as well
    node = node->parent;
    node->parent = node->parent->parent;
  }
  return node->parent;
}


template<class T, class CMP>
 void RBTree<T, CMP>::print_ordered_keys(int const choice) const {
    recursive_ordering(get_root(), choice);
}


template <class T, class CMP>
void RBTree<T, CMP>::print_tree() const {
  if (root!=NIL) {
    recursive_print(get_root(), "", 1);
  } else {
    std::cout << "RBTree is empty, nothing to print here!" << std::endl;
  }
}

//#FIXME: why segmentation fault?
template<class T, class CMP>
 void RBTree<T, CMP>::clear_tree() noexcept {
    if (root==NIL) return; 
    //p = clear_tree(get_root()->left); 
    //p = clear_tree(get_root()->right);
    delete root;
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
3) check instances of to-be-changed methods                           OK
4) replace with to-be-changed methods (N.B. use the comparator->OK)   OK
_
5) check if all methods are implemented                               OK
6) terminate regular iterator + inheritance on const_iter             ???
7) set up unit test suite:                                          in progress...
while with 50 int, same with 50 double, test iteratorS, print tree, test find,
print inorder traversal, etc..
*/

#include "RBT_iterator.hpp"
#endif // RBT_HPP