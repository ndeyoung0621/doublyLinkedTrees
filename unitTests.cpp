#include <iostream>
#include <cassert>
#include "linkedList.hpp"

using namespace std;

// Define a macro to simplify the test assertions
// I am done trying to make stupid GTEST work
#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            cerr << "Assertion failed: (" << #expected << " == " << #actual << ") " \
                      << "at " << __FILE__ << ":" << __LINE__ << endl; \
            cerr << "  Expected: " << (expected) << endl; \
            cerr << "  Actual: " << (actual) << endl; \
            exit(EXIT_FAILURE); \
        } \
    } while (0)


void testInsert() {
    // Example list
    linkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);

    ASSERT_EQ(3, list.getSize());  
}

// Test if the values inserted are in the right place (they are not)
void testLinkedValues() {
    // Example list
    linkedList list;
    list.insert(69);
    list.insert(6969);
    list.insert(696969);

    ASSERT_EQ(696969, list.getThirdValue());
}

int main() {
    // Run tests
    testInsert();
    testLinkedValues();

    cout << "All tests passed!" << endl;
    return 0;
}