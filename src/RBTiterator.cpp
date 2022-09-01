// RBTiterator Implementation

#include "RBTiterator.h"

//RBTiterator constructors
rb_iterator::rb_iterator(void): iterator(), Iterator(NULL) { }  //initialisation list
rb_iterator::rb_iterator(T *ptr): Iterator(ptr) { }  //initialisation list
rb_iterator::rb_iterator(const rb_iterator & that): Iterator(that.Iterator) { }  //initialisation list

//RBTiterator operators
rb_iterator rb_iterator::operator++(void) {
    Iterator = Iterator->successor();
    return *this;
}

rb_iterator rb_iterator::operator++(int) {
    T *temp = Iterator;
    operator++();
    return rb_iterator(temp);
}

rb_iterator rb_iterator::operator--(void) {
    Iterator = Iterator->predecessor();
    return *this;
}

rb_iterator rb_iterator::operator--(int) {
    T *temp = Iterator;
    operator--();
    return rb_iterator(temp);
}

rb_iterator & rb_iterator::operator=(const_reference that) {
    Iterator->value = that;
    return *this;
}

bool rb_iterator::operator==(const rb_iterator & that) const {
    return (Iterator == that.Iterator);
}

bool rb_iterator::operator!=(const rb_iterator & that) const {
    return (Iterator != that.Iterator);
}

rb_iterator::operator T &() {
    return *Iterator;
}

rb_iterator::operator const T &() const {
    return *Iterator;
}

reference rb_iterator::operator*(void) {
    return Iterator->value;
}

T * rb_iterator::operator->(void) {
    return Iterator;
}
