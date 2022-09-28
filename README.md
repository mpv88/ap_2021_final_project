# ap_2021_final_project - Red-Black Tree class

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

## Folder structure
Current folder contains a simple implementation of a templated Red-Black Tree class, together with its const-iterator.

* `bmk` folder includes a `bmk.cpp` file to run a small experiment aimed at timing the performance of the find() method on our Red-Black Tree naive implementation, against the std::map and std::unordered_map containers' same method. The .txt output is then used as a source for the `bmk_times_plot.py` in order to generate the two .png pictures present in the folder. More detailed description available within the bmk.cpp file.

* `doxygen` folder includes a `doxy_config` file with (custom) options and parameters chosen for automatically creating documentation for the classes. Upon generation, all documentation will be available in both `html` and `latex` subfolders.

* `include` folder is composed of 3 header files:
    * `Node.hpp`: declarations and implementation of members and methods for Node class;
    * `RBT.hpp`: declarations and implementation of members and methods for RBTree class;
    * `RBT_iterator`: declarations and implementation of members and methods for RBTree's const_iterator subclass.

* `test` folder includes both a `tests.cpp` file containing the official unit-tests for the above mentioned classes -all performed with the Boost.Test framework-, paired with an unofficial `main.cc` file, aimed at showing how to use most part of classes' features.


## Execution
Attached `Makefile` is used to help in the compilation of project's files:

* `make` command creates sequentially a `build` and a `bin` folder containing respectively the object (.o) and executable (.x) files for tests.cpp and bmk.cpp.
All generated executable files are then ready for use into the bin folder.

* `make clean` command clears the entire build directory, all the executables present into the bin directory and -if already created- all the documentation within the doxygen folder.

* `make clears` command clears the screen of the Terminal in use from the results coming from previously inserted commands and from the runs of the excecutables.

* `make docs` generates documentation for the code inside the doxygen folder.

* `make format` automatically formats all the code files present in the include and test directories following the clang-format.