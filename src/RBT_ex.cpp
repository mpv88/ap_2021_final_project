/*
Implement the generic classes RBTree<T, CMP=std::less<T>> and RBTree<T,CMP=std::less<T>>::const iterator 
to represent red-black trees and their constant iterators
*/

using namespace std;

template <typename T, typename cmp>
class RBTree<T, cmp=std::less<T>>