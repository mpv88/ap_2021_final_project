///\file RBT.hpp
///\author mpv
///\brief implementation file with all RBT's sub-classes (iterator and
/// const_iterator).

#include "RBT.hpp"

enum Color { BLACK = 0, RED = 1 };
// FIXME:inside or outside node?

///\brief RBTree's single node, each node bears a key and a color (red or black)
///       each node has a parent and two children (left and right)
template <class T, class CMP> class RBTree<T, CMP>::Node {

public:
  <const T> data;              ///< template key of the node
  Color color;                 ///< color of the node (black=0 or red=1)
  Node *left, *right, *parent; ///< pointers to parent, left and right children

  ///\brief default constructor for the node
  ///
  Node() = default;

  ///\brief Constructor of a new node given a key and optionally a color and a
  ///parent \param k key which will be inserted into the node \param c color of
  ///the node (default set to BLACK) \param p pointer to the parent node
  /// Initializer List initializes the data members of a class, default color is
  /// BLACK
  Node(<T> k, Color c = BLACK, Node *p = nullptr)
      : data{k}, color = {c}, left{nullptr}, right{nullptr}, parent{p} {}
};

///\brief RBTree's regular iterator class
///       used to iterate over a sequence and manipulate RBTree's elements
template <class T, class CMP> class RBTree<T, CMP>::iterator {
  friend class RBTree; // FIXME: is this necessary?

private:
  Node *pointed_node; ///< pointer to the node pointed by the iterator

public:
  ///\brief RBTree's constant iterator class
  ///       used to iterate over a sequence and access only RBTree's elements
  template <class T, class CMP> class RBTree<T, CMP>::const_iterator {
