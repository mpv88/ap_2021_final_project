// RBTnode Implementation

#include "RBTnode.h"

//RBTnode constructors
rb_node::rb_node(value_type _value,rb_node *_parent, bool _color): value(_value), parent(_parent), color(_color), left(NULL), right(NULL) { }   //initialisation list
rb_node::rb_node(value_type _value, rb_node *_parent): value(_value), parent(_parent), color(RED), left(NULL), right(NULL) { }  //initialisation list
rb_node::rb_node(const value_type &_value): value(_value), parent(NULL), color(RED), left(NULL), right(NULL) { }  //initialisation list
rb_node::rb_node(void): parent(NULL), color(BLACK), left(NULL), right(NULL) { }  //initialisation list
rb_node::rb_node(rb_node const &other) {(*this) = other;}


//RBTnode operators
value_type & rb_node::operator=(const value_type &_value) {
    value = _value; 
    return value;
}

bool rb_node::operator==(const value_type &_value) const {
    return (value == _value);
}

bool rb_node::operator==(const rb_node &other) const {
    return (value == other.value) && (parent == other.parent);
}

bool rb_node::operator!=(const value_type &_value) const {
    return (value != _value);
}  

bool rb_node::operator!=(const rb_node &other) const {
    return (value != other.value) || (parent != other.parent);
}

bool rb_node::operator>(const value_type &_value) const {
    return (value > _value);
}

bool rb_node::operator>(const rb_node &other) const {
    return (value > other.value);
}

bool rb_node::operator>=(const value_type &_value) const {
    return (value >= _value);
}

bool rb_node::operator>=(const rb_node &other) const {
    return (value >= other.value);
}

bool rb_node::operator<(const value_type &_value) const {
    return (value < _value);
}

bool rb_node::operator<(const rb_node &other) const {
    return (value < other.value);
}

bool rb_node::operator<=(const value_type &_value) const {
    return (value <= _value);
}

bool rb_node::operator<=(const rb_node &other) const {
    return (value <= other.value);
}


//RBTnode other methods
const bool is_a_left_son( void ) const {
    return (parent != NULL) && (parent->left == this);
}

const bool is_a_right_son( void ) const {
    return (parent != NULL) && (parent->right == this);
}

rb_node *rb_node::max(void) {
    return (right==NULL) ? this : right->max();
}

rb_node *rb_node::min(void) {
    return (left==NULL) ? this : left->min();
}

rb_node *rb_node::successor(void) {
    if(this!=NULL) {
    // this node has a right subtree?
        if (right!=NULL) return right->min();
    // this node has a left son?
        if (is_a_left_son()) return parent;
    
    // so node has not neither a right subtree nor is a left son
    // then search for the next successor which is also a right son
        rb_node *succ = this;
        do { 
            succ = succ->parent; 
        } while ((succ!=NULL) && succ->is_a_right_son());
        if (succ!=NULL)
            return succ->parent;
        else
            return NULL;
    }
        return NULL;
}

rb_node *rb_node::predecessor(void) {
    if(this!=NULL) {
        if (left!=NULL) //this node has a left subtree?
            return left->max();
        if (is_a_right_son()) // this node has a right son?
            return parent;
    // so node has not neither a left subtree nor is a right son
    // then search for the next predecessor which is also a left son
        rb_node *pred = this;
        do { 
            pred = pred->parent; 
        } while ((pred!=NULL) && pred->is_a_left_son());
        if (pred!=NULL)
            return pred->parent;
        else
            return NULL;
    }
        return NULL;
}

rb_node *rb_node::sibiling(void) {
    if(this!=NULL) {
        if(parent==NULL)
            return NULL;
        return (is_a_left_son()) ? parent->right : parent->left;
    }
    return NULL;
}

void rb_node::print(void) {
    std::cout << std::endl << "(Node value:" << value << " Color:" << color;
    if(parent!=NULL) std::cout << " Parent:" << parent->value;
    if(left!=NULL) std::cout << " Left:" << left->value;
    if(right!=NULL) std::cout << " Right:" << right->value;
    std::cout << ")" << std::endl;
}