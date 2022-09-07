///\file RBT_Methods.hpp
///\author mpv
///\brief implementation of RBT class's methods.

#ifndef RBTMTD_HPP
#define RBTMTD_HPP

#include "RBT.hpp"

// RBT methods

void RBTree::initializeNULLNode(NodePtr node, NodePtr parent) {
  /// initializes the nodes with appropirate values
  /// all the pointers are set to point to the null pointer
  node->data = 0;
  node->parent = parent;
  node->left = nullptr;
  node->right = nullptr;
  node->color = 0;
}

void RBTree::preOrderHelper(NodePtr node) {
  if (node != TNULL) {
    cout << node->data << " ";
    preOrderHelper(node->left);
    preOrderHelper(node->right);
  }
}

void RBTree::inOrderHelper(NodePtr node) {
  if (node != TNULL) {
    inOrderHelper(node->left);
    cout << node->data << " ";
    inOrderHelper(node->right);
  }
}

void RBTree::postOrderHelper(NodePtr node) {
  if (node != TNULL) {
    postOrderHelper(node->left);
    postOrderHelper(node->right);
    cout << node->data << " ";
  }
}

NodePtr RBTree::searchTreeHelper(NodePtr node, int key) {
  if (node == TNULL || key == node->data) {
    return node;
  }
  if (key < node->data) {
    return searchTreeHelper(node->left, key);
  }
  return searchTreeHelper(node->right, key);
}

void RBTree::fixDelete(NodePtr x) {
  /// fix the rb tree modified by the delete operation
  NodePtr s;
  while (x != root && x->color == 0) {
    if (x == x->parent->left) {
      s = x->parent->right;
      if (s->color == 1) {
        // case 3.1
        s->color = 0;
        x->parent->color = 1;
        leftRotate(x->parent);
        s = x->parent->right;
      }

      if (s->left->color == 0 && s->right->color == 0) {
        // case 3.2
        s->color = 1;
        x = x->parent;
      } else {
        if (s->right->color == 0) {
          // case 3.3
          s->left->color = 0;
          s->color = 1;
          rightRotate(s);
          s = x->parent->right;
        }

        // case 3.4
        s->color = x->parent->color;
        x->parent->color = 0;
        s->right->color = 0;
        leftRotate(x->parent);
        x = root;
      }
    } else {
      s = x->parent->left;
      if (s->color == 1) {
        // case 3.1
        s->color = 0;
        x->parent->color = 1;
        rightRotate(x->parent);
        s = x->parent->left;
      }

      if (s->right->color == 0 && s->right->color == 0) {
        // case 3.2
        s->color = 1;
        x = x->parent;
      } else {
        if (s->left->color == 0) {
          // case 3.3
          s->right->color = 0;
          s->color = 1;
          leftRotate(s);
          s = x->parent->left;
        }

        // case 3.4
        s->color = x->parent->color;
        x->parent->color = 0;
        s->left->color = 0;
        rightRotate(x->parent);
        x = root;
      }
    }
  }
  x->color = 0;
}

void RBTree::rbTransplant(NodePtr u, NodePtr v) {
  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void RBTree::deleteNodeHelper(NodePtr node, int key) {
  /// find the node containing key
  NodePtr z = TNULL;
  NodePtr x, y;
  while (node != TNULL) {
    if (node->data == key) {
      z = node;
    }

    if (node->data <= key) {
      node = node->right;
    } else {
      node = node->left;
    }
  }

  if (z == TNULL) {
    cout << "Couldn't find key in the tree" << endl;
    return;
  }

  y = z;
  int y_original_color = y->color;
  if (z->left == TNULL) {
    x = z->right;
    rbTransplant(z, z->right);
  } else if (z->right == TNULL) {
    x = z->left;
    rbTransplant(z, z->left);
  } else {
    y = minimum(z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      rbTransplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    rbTransplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  delete z;
  if (y_original_color == 0) {
    fixDelete(x);
  }
}

void RBTree::fixInsert(NodePtr k) {
  /// fix the red-black tree
  NodePtr u;
  while (k->parent->color == 1) {
    if (k->parent == k->parent->parent->right) {
      u = k->parent->parent->left; // uncle
      if (u->color == 1) {
        // case 3.1
        u->color = 0;
        k->parent->color = 0;
        k->parent->parent->color = 1;
        k = k->parent->parent;
      } else {
        if (k == k->parent->left) {
          // case 3.2.2
          k = k->parent;
          rightRotate(k);
        }
        // case 3.2.1
        k->parent->color = 0;
        k->parent->parent->color = 1;
        leftRotate(k->parent->parent);
      }
    } else {
      u = k->parent->parent->right; // uncle

      if (u->color == 1) {
        // mirror case 3.1
        u->color = 0;
        k->parent->color = 0;
        k->parent->parent->color = 1;
        k = k->parent->parent;
      } else {
        if (k == k->parent->right) {
          // mirror case 3.2.2
          k = k->parent;
          leftRotate(k);
        }
        // mirror case 3.2.1
        k->parent->color = 0;
        k->parent->parent->color = 1;
        rightRotate(k->parent->parent);
      }
    }
    if (k == root) {
      break;
    }
  }
  root->color = 0;
}

void RBTree::printHelper(NodePtr root, string indent, bool last) {
  /// print the tree structure on the screen
  if (root != TNULL) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "     ";
    } else {
      cout << "L----";
      indent += "|    ";
    }
    string sColor = root->color ? "RED" : "BLACK";
    cout << root->data << "(" << sColor << ")" << endl;
    printHelper(root->left, indent, false);
    printHelper(root->right, indent, true);
  }
  // cout<<root->left->data<<endl; //segmentation fault
}

// RBTree Constructors
RBTree::RBTree() {
  TNULL = new Node;
  TNULL->color = 0;
  TNULL->left = nullptr;
  TNULL->right = nullptr;
  root = TNULL;
}

// Public Functions
void RBTree::preorder() {
  /// Pre-Order traversal: Node->Left Subtree->Right Subtree
  preOrderHelper(this->root);
}

void RBTree::inorder() {
  /// In-Order traversal: Left Subtree->Node->Right Subtree
  inOrderHelper(this->root);
}

void RBTree::postorder() {
  /// Post-Order traversal: Left Subtree->Right Subtree->Node
  postOrderHelper(this->root);
}

NodePtr RBTree::searchTree(int k) {
  /// Search the tree for the key k
  /// and return the corresponding node
  return searchTreeHelper(this->root, k);
}

NodePtr RBTree::minimum(NodePtr node) {
  /// Find the node with the minimum key
  while (node->left != TNULL) {
    node = node->left;
  }
  return node;
}

NodePtr RBTree::maximum(NodePtr node) {
  /// Find the node with the maximum key
  while (node->right != TNULL) {
    node = node->right;
  }
  return node;
}

NodePtr RBTree::successor(NodePtr x) {
  /// Find the successor of a given node.
  /// if the right subtree is not null,
  /// the successor is the leftmost node in the
  /// right subtree
  if (x->right != TNULL) {
    return minimum(x->right);
  }
  // else it is the lowest ancestor of x whose
  // left child is also an ancestor of x.
  NodePtr y = x->parent;
  while (y != TNULL && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

NodePtr RBTree::predecessor(NodePtr x) {
  /// Find the predecessor of a given node.
  /// if the left subtree is not null,
  /// the predecessor is the rightmost node in the
  /// left subtree
  if (x->left != TNULL) {
    return maximum(x->left);
  }
  NodePtr y = x->parent;
  while (y != TNULL && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

void RBTree::leftRotate(NodePtr x) {
  /// Left-rotate the node x.
  NodePtr y = x->right;
  x->right = y->left;
  if (y->left != TNULL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    this->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void RBTree::rightRotate(NodePtr x) {
  /// Right-rotate the node x.
  NodePtr y = x->left;
  x->left = y->right;
  if (y->right != TNULL) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    this->root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

void RBTree::insert(int key) {
  /// Insert the key to the tree in its appropriate position
  /// and fix the tree starting with an ordinary Binary Search Insertion
  NodePtr node = new Node;
  node->parent = nullptr;
  node->data = key;
  node->left = TNULL;
  node->right = TNULL;
  node->color = 1; // new node must be red
  NodePtr y = nullptr;
  NodePtr x = this->root;

  while (x != TNULL) {
    y = x;
    if (node->data < x->data) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  // y is parent of x
  node->parent = y;
  if (y == nullptr) {
    root = node;
  } else if (node->data < y->data) {
    y->left = node;
  } else {
    y->right = node;
  }
  // if new node is a root node, simply return
  if (node->parent == nullptr) {
    node->color = 0;
    return;
  }
  // if the grandparent is null, simply return
  if (node->parent->parent == nullptr) {
    return;
  }
  // Fix the tree
  fixInsert(node);
}

NodePtr RBTree::getRoot() {
  /// Get the root of the tree
  return this->root;
}

void RBTree::deleteNode(int data) {
  /// Delete the node from the tree
  deleteNodeHelper(this->root, data);
}

void RBTree::printTree() {
  /// Print the tree structure on the screen
  if (root) {
    printHelper(this->root, "", true);
  }
}

#endif // RBTMTD_HPP