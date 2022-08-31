// RBT Implementation

#include "RBTree.h"

// Node constructor
Node::Node(int data) {
       this->data = data;
       this->color = RED;
       left = right = parent = nullptr;
    }

// RBTree constructor
RBTree::RBTree() {
    root = nullptr;
}

// RBTree protected methods

int RBTree::getColor(Node *&node) {
    /// Lorem ipsum.
    if (node == nullptr)
        return BLACK;
    return node->color;
}

void RBTree::setColor(Node *&, int) {}




