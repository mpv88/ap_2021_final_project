// RBT driver

#include <iostream>
#include "RBTree.h"

int main() {
    RBTree rbt1, rbt2;
    int number {};

    while(!(std::cin >> number)) {
        std::cout << "Please enter a number" << std::endl;
        rbt1.insertValue(number);
        std::cout << "Number is appended to the tree" << std::endl;
    }

    rbt1.preorder();

    while(!(std::cin >> number)) {
        std::cout << "Please enter a number" << std::endl;
        rbt2.insertValue(number);
        std::cout << "Number is appended to the tree" << std::endl;
    
    rbt2.preorder();

    rbt1.merge(rbt2);
    rbt1.preorder();

    return 0;
}