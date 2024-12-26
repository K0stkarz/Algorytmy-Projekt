#include "skiplist.h"
#include <cassert>
#include <iostream>


void runTests() {
    // Test 1: Basic operations
    SkipList<int> list1;
    list1.insert(3);
    list1.insert(6);
    list1.insert(7);
    list1.insert(9);
    list1.insert(12);
    
    std::cout << "After insertions:" << std::endl;
    list1.display();
    
    assert(list1.search(6) == true);
    assert(list1.search(8) == false);
    
    list1.remove(6);
    std::cout << "After removing 6:" << std::endl;
    list1.display();
    assert(list1.search(6) == false);
    
    
    // Test 3: Edge cases
    SkipList<int> list3(4, 0.5); // Small max level
    for (int i = 1; i <= 10; i++) {
        list3.insert(i);
    }
    
    std::cout << "Skip list with 10 elements:" << std::endl;
    list3.display();
    
    // Test removing first and last elements
    list3.remove(1);
    list3.remove(10);
    std::cout << "After removing first and last elements:" << std::endl;
    list3.display();
    
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}