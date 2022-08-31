// RBT definition header

#ifndef RBT_H
#define RBTREE_H
#endif

enum RBTColor {BLACK=0, RED=1};

struct Node {
    int data; // key value
    bool color; // red/black
    Node *left, *right, *parent; //self-referential pointers
 
    // Constructor
    Node(int data) {
       this->data = data;
       left = right = parent = NULL;
       this->color = RED;
    }
};