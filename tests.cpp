#include "skiplist.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <string>

void testConstructor() {
    std::cout << "Testing constructors..." << std::endl;
    
    // Test default constructor
    SkipList<int> list1;
    assert(list1.empty());
    
    // Test parameterized constructor
    SkipList<int> list2(3, 0.5);
    assert(list2.empty());
    
    // Test copy constructor
    list1.insert(5);
    SkipList<int> list3(list1);
    assert(list3.search(5) != nullptr);
    
    std::cout << "Constructor tests passed!" << std::endl;
}

void testInsert() {
    std::cout << "Testing insert..." << std::endl;
    
    SkipList<int> list;
    
    // Test single insert
    list.insert(5);
    assert(list.search(5) != nullptr);
    
    // Test multiple inserts
    list.insert(3);
    list.insert(7);
    assert(list.search(3) != nullptr);
    assert(list.search(7) != nullptr);
    
    // Test duplicate insert
    list.insert(5);
    assert(list.search(5) != nullptr);
    
    std::cout << "Insert tests passed!" << std::endl;
}

void testSearch() {
    std::cout << "Testing search..." << std::endl;
    
    SkipList<int> list;
    
    // Test search in empty list
    assert(list.search(5) == nullptr);
    
    // Test search for existing element
    list.insert(5);
    assert(list.search(5) != nullptr);
    assert(list.search(5)->value == 5);
    
    // Test search for non-existing element
    assert(list.search(3) == nullptr);
    
    std::cout << "Search tests passed!" << std::endl;
}

void testRemove() {
    std::cout << "Testing remove..." << std::endl;
    
    SkipList<int> list;
    
    // Test remove from empty list
    list.remove(5);  // Should not crash
    
    // Test remove existing element
    list.insert(5);
    list.remove(5);
    assert(list.search(5) == nullptr);
    
    // Test remove with multiple elements
    list.insert(3);
    list.insert(5);
    list.insert(7);
    list.remove(5);
    assert(list.search(3) != nullptr);
    assert(list.search(5) == nullptr);
    assert(list.search(7) != nullptr);
    
    std::cout << "Remove tests passed!" << std::endl;
}

void testEmpty() {
    std::cout << "Testing empty..." << std::endl;
    
    SkipList<int> list;
    
    // Test empty on new list
    assert(list.empty());
    
    // Test empty after insert
    list.insert(5);
    assert(!list.empty());
    
    // Test empty after remove
    list.remove(5);
    assert(list.empty());
    
    std::cout << "Empty tests passed!" << std::endl;
}

void testClear() {
    std::cout << "Testing clear..." << std::endl;
    
    SkipList<int> list;
    
    // Test clear on empty list
    list.clear();
    assert(list.empty());
    
    // Test clear with elements
    list.insert(3);
    list.insert(5);
    list.insert(7);
    list.clear();
    assert(list.empty());
    assert(list.search(3) == nullptr);
    assert(list.search(5) == nullptr);
    assert(list.search(7) == nullptr);
    
    std::cout << "Clear tests passed!" << std::endl;
}

void testDifferentTypes() {
    std::cout << "Testing different types..." << std::endl;
    
    // Test with strings
    SkipList<std::string> stringList;
    stringList.insert("hello");
    stringList.insert("world");
    assert(stringList.search("hello") != nullptr);
    assert(stringList.search("world") != nullptr);
    
    // Test with doubles
    SkipList<double> doubleList;
    doubleList.insert(3.14);
    doubleList.insert(2.718);
    assert(doubleList.search(3.14) != nullptr);
    assert(doubleList.search(2.718) != nullptr);
    
    std::cout << "Different types tests passed!" << std::endl;
}

void testCopyConstructor() {
    std::cout << "Testing copy constructor..." << std::endl;
    
    SkipList<int> list1;
    list1.insert(3);
    list1.insert(5);
    list1.insert(7);
    
    // Test copy constructor
    SkipList<int> list2(list1);
    
    // Verify all elements were copied
    assert(list2.search(3) != nullptr);
    assert(list2.search(5) != nullptr);
    assert(list2.search(7) != nullptr);
    
    // Verify original list remains unchanged
    assert(list1.search(3) != nullptr);
    assert(list1.search(5) != nullptr);
    assert(list1.search(7) != nullptr);
    
    // Modify copy and verify original is unchanged
    list2.insert(9);
    assert(list2.search(9) != nullptr);
    assert(list1.search(9) == nullptr);
    
    // Remove from copy and verify original is unchanged
    list2.remove(3);
    assert(list2.search(3) == nullptr);
    assert(list1.search(3) != nullptr);
    
    std::cout << "Copy constructor tests passed!" << std::endl;
}

void testMoveConstructor() {
    std::cout << "Testing move constructor..." << std::endl;
    
    SkipList<int> list1;
    list1.insert(3);
    list1.insert(5);
    list1.insert(7);
    
    // Test move constructor
    SkipList<int> list2(std::move(list1));
    
    // Verify moved elements exist in new list
    assert(list2.search(3) != nullptr);
    assert(list2.search(5) != nullptr);
    assert(list2.search(7) != nullptr);
    
    // Verify original list is empty after move
    assert(list1.empty());
    assert(list1.search(3) == nullptr);
    assert(list1.search(5) == nullptr);
    assert(list1.search(7) == nullptr);
    
    std::cout << "Move constructor tests passed!" << std::endl;
}

void testCopyAssignment() {
    std::cout << "Testing copy assignment operator..." << std::endl;
    
    SkipList<int> list1;
    list1.insert(3);
    list1.insert(5);
    list1.insert(7);
    
    // Test copy assignment
    SkipList<int> list2;
    list2.insert(10);  // Add element to ensure it's cleared after assignment
    list2 = list1;
    
    // Verify all elements were copied
    assert(list2.search(3) != nullptr);
    assert(list2.search(5) != nullptr);
    assert(list2.search(7) != nullptr);
    assert(list2.search(10) == nullptr);  // Verify old elements are gone
    
    // Verify original list remains unchanged
    assert(list1.search(3) != nullptr);
    assert(list1.search(5) != nullptr);
    assert(list1.search(7) != nullptr);
    
    // Test self-assignment
    list1 = list1;
    assert(list1.search(3) != nullptr);
    assert(list1.search(5) != nullptr);
    assert(list1.search(7) != nullptr);
    
    std::cout << "Copy assignment tests passed!" << std::endl;
}

void testMoveAssignment() {
    std::cout << "Testing move assignment operator..." << std::endl;
    
    SkipList<int> list1;
    list1.insert(3);
    list1.insert(5);
    list1.insert(7);
    
    // Test move assignment
    SkipList<int> list2;
    list2.insert(10);  // Add element to ensure it's cleared after assignment
    list2 = std::move(list1);
    
    // Verify moved elements exist in new list
    assert(list2.search(3) != nullptr);
    assert(list2.search(5) != nullptr);
    assert(list2.search(7) != nullptr);
    assert(list2.search(10) == nullptr);  // Verify old elements are gone
    
    // Verify original list is empty after move
    assert(list1.empty());
    assert(list1.search(3) == nullptr);
    assert(list1.search(5) == nullptr);
    assert(list1.search(7) == nullptr);
    
    // Test self-move-assignment
    list2 = std::move(list2);
    assert(list2.search(3) != nullptr);
    assert(list2.search(5) != nullptr);
    assert(list2.search(7) != nullptr);
    
    std::cout << "Move assignment tests passed!" << std::endl;
}

int main() {
    testConstructor();
    testInsert();
    testSearch();
    testRemove();
    testEmpty();
    testClear();
    testDifferentTypes();
    
    // New tests
    testCopyConstructor();
    testMoveConstructor();
    testCopyAssignment();
    testMoveAssignment();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}