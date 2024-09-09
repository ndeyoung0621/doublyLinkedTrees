#include <iostream>
#include <cassert>
#include "linkedList.hpp"

using namespace std;

// Define a macro to simplify the test assertions
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

// Test Insert Function
void testInsert() {
    linkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);

    ASSERT_EQ(3, list.getSize());
}

// Test Delete Node Function
void testDeleteNode() {
    linkedList list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    // Assuming we want to delete the second node (which has value 2)
    Node* nodeToDelete = list.getHead()->next; // This is the node with value 2
    list.deleteNode(nodeToDelete);

    // After deletion, the list should have 2 elements and the second value should be 3
    ASSERT_EQ(2, list.getSize());
    ASSERT_EQ(3, list.getHead()->next->data);
}

// Test Search Function
void testSearch() {
    linkedList list;
    list.insert(5);
    list.insert(10);
    list.insert(15);

    // Test valid index
    ASSERT_EQ(10, list.search(1));

    // Test out-of-bounds index
    ASSERT_EQ(-1, list.search(3)); // Should be -1 since there is no 4th element
}

int main() {
    // Run tests
    testInsert();
    testDeleteNode();
    //testPrintList();
    testSearch();

    cout << "All tests passed!" << endl;
    return 0;
}