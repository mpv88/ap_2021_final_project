// RBT definition header

#ifndef RBT_H
#define RBT_H

#include <iostream>

using namespace std;

// data structure that represents a node in the tree
class Node {
    public:
        int data;     // key
        int color;    // 1 -> Red, 0 -> Black
        Node *parent; // ptr to parent
        Node *left;   // ptr to left child
        Node *right;  // ptr to right child
};

//definition of new types:
typedef Node *NodePtr;

// class RBTree implements the operations in Red Black Tree
class RBTree {
    protected:
        // members
        NodePtr root;
        NodePtr TNULL;

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

    public:
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
        void prettyPrint();
};

#endif // RBTREE_H