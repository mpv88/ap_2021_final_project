// RBTiterator definition header

#ifndef RBTITERATOR_H
#define RBTITERATOR_H

#include <iterator>
#include "RBTnode.h"


using std::iterator;
using std::bidirectional_iterator_tag;

template<typename T>
class rb_iterator:  public std::iterator<bidirectional_iterator_tag, typename T::value_type> {

    protected:
        T *Iterator; //ptr to a RBTnode
    
    public:
        //definition of new types:
        typedef typename T::value_type *pointer;			 
        typedef typename T::value_type const *const_pointer;		
        typedef typename T::value_type &reference;			
        typedef typename T::value_type const &const_reference;	

        //constructors:
        explicit rb_iterator(void);
        explicit rb_iterator(T *ptr);
        explicit rb_iterator(const rb_iterator & that);

        //operators
        rb_iterator operator++(void);
        rb_iterator operator++(int);
        rb_iterator operator--(void);
        rb_iterator operator--(int);
        rb_iterator & operator=(const_reference that);

        bool operator==(const rb_iterator & that) const;
        bool operator!=(const rb_iterator & that) const;
        operator T &();
        operator const T &() const;
        reference operator*(void);
        T * operator->(void);
};


#endif // RBTITERATOR_H