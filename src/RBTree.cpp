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

/**
 * @brief gets black for root & leaf nodes
 */
int RBTree::getColor(Node *&node) {
    if (node == nullptr)
        return BLACK;
    return node->color;
}

/**
 * @brief sets black for root & leaf nodes
 */
void RBTree::setColor(Node *&, int) {}




