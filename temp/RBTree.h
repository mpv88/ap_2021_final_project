// RBT definition header

#ifndef RBTREE_H
#define RBTREE_H

#include<functional>
#include<queue>
#include "RBTnode.h"
#include "RBTiterator.h"

template<typename T>
class rb_tree {
    public:
        //definition of new types:
        typedef typename rb_node<T> node_type;
        typedef typename T value_type;
        typedef rb_iterator<node_type> iterator;

        //members
        node_type *root;
        unsigned long size;

        //constructors
        explicit rb_tree(void);
        
        template<typename Iterator_>
        explicit rb_tree(Iterator_ begin, Iterator_ end);

        //utilities
        bool empty(void) const;
        iterator max(void);
        iterator min(void);
        iterator begin(void);
        iterator end(void);
        
        //insertion overloading
        iterator insert(value_type value);
        iterator insert( iterator &current, value_type &value);
        template<typename Iterator_>
        void insert(Iterator_ begin, Iterator_ end);

        //RBT insertion
        node_type *insert(node_type *node);

        //RBT print methods
        void print();
        void inorder_print(node_type *ptr);
        int height();

    protected:
        void print(node_type *node);
        int height(node_type *node);
        node_type *binary_insert(node_type*node);
        void rb_adjust(node_type *node);
        void left_rotate(node_type *node);
        void right_rotate(node_type *node);
};

// instantiation parametrized template classes
// https://stackoverflow.com/questions/115703/storing-c-template-function-definitions-in-a-cpp-file
//template typename rb_tree<int>;

#endif // RBTREE_H