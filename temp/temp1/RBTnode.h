// RBTiterator definition header

#ifndef RBTNODE_H
#define RBTNODE_H

template<typename T>
class rb_node {
    private:
        enum RBTColor {
            RED = 0,
            BLACK = 1
        };

    public:
        //definition of new types:
        typedef T value_type;
        
        T value;            // key value
        bool color;         // red/black
        rb_node *left, *right, *parent; //self-referential pointers


        //constructors	
        explicit rb_node(value_type _value, rb_node *_parent, bool _color);
        explicit rb_node(value_type _value, rb_node * _parent);
        explicit rb_node(const value_type &_value);
        explicit rb_node(void);
        explicit rb_node(rb_node const &other);

        
        //operators
        value_type & operator=(const value_type & _value);
        bool operator==(const value_type & _value) const;
        bool operator!=(const value_type & _value) const;
        bool operator>(const value_type & _value) const;
        bool operator<(const value_type & _value) const;
        bool operator>=(const value_type & _value) const;
        bool operator<=(const value_type & _value) const;
        bool operator==(const rb_node & other) const;
        bool operator!=(const rb_node & other) const;
        bool operator>(const rb_node & other) const;
        bool operator<(const rb_node & other) const;
        bool operator>=(const rb_node & other) const;
        bool operator<=(const rb_node & other) const;
        
        //other functions
        const bool is_a_left_son(void) const;
        const bool is_a_right_son(void) const;
        rb_node *max(void);    //max value in a subtree
        rb_node *min(void);    //min value in a subtree
        rb_node *successor(void);  //get the successor of a node
        rb_node * predecessor(void);    //get the predecessor of a node
        rb_node *sibling(void);    //get the sibling of a node
        void print();   //print the node value
};

#endif // RBTNODE_H