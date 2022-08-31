// RBT definition header

#ifndef RBTREE_H
#define RBTREE_H

enum RBTColor {BLACK=0, RED=1};

//TODO: form struct to templated class
struct Node {
    int data; // key value
    RBTColor color; // red/black
    Node *left, *right, *parent; //self-referential pointers
 
    //      RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode * r):
    //      key(value),color(c),parent(),left(l),right(r) {}
    explicit Node(int); // constructor
};

class RBTree {
private:
    Node *root;

protected:
    int getColor(Node *&);
    void setColor(Node *&, int);
    Node* insertBST(Node *&, Node *&);
    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    void fixInsertRBTree(Node *&);
    void fixDeleteRBTree(Node *&);
    Node* deleteBST(Node *&, int);
    void inorderBST(Node *&);
    void preorderBST(Node *&);
    Node *minValueNode(Node *&);
    Node *maxValueNode(Node *&);
    int getBlackHeight(Node *);

public:
    RBTree(); // constructor
    void insertValue(int);
    void deleteValue(int);
    void inorder();
    void preorder();
    void merge(RBTree);

};


#endif // RBTREE_H