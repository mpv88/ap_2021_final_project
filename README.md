# ap_2021_final_project

## Problem Definition
Red-Black Trees are binary search trees satisfying the following conditions:

- every node is either red or black;
- the root is black;
- every leaf (NIL) is black;
- if a node is red, then its children are black;
- for each node x, all the simple paths from x to descendant leaves contain the same number of black nodes.

Thanks to the mentioned properties, it is possible to insert, delete, and search a value in a red-black tree in time O(log n) [1].


![image](https://user-images.githubusercontent.com/56740461/185750889-6148a944-393e-4abe-865c-fbe0f3dc16b1.png)


## References
<a id="1">[1]</a> 
Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. 
Introduction to Algorithms. 
The MIT Press, 2nd edition, 2001.

### TODOs
-pp. 2, 'delete' has void type (not bool)