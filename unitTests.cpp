#include <iostream>
#include <cassert>
#include "linkedList.hpp"

// Define a macro to simplify the test assertions
#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            std::cerr << "Assertion failed: (" << #expected << " == " << #actual << ") " \
                      << "at " << __FILE__ << ":" << __LINE__ << std::endl; \
            std::cerr << "  Expected: " << (expected) << std::endl; \
            std::cerr << "  Actual: " << (actual) << std::endl; \
            std::exit(EXIT_FAILURE); \
        } \
    } while (0)

// Example test functions
void testInsert() {
    // Example list
    // Assuming you have a `DoublyLinkedList` class with an `append` method and `getSize` method
    linkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);

    ASSERT_EQ(3, list.getSize());  // Test case
}

int main() {
    // Run tests
    testInsert();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}