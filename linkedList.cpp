#include "linkedList.hpp"
#include <iostream>

using namespace std;

linkedList::linkedList() noexcept : head(nullptr), tail(nullptr), size(0) {}

//fixed insert function
void linkedList::insert(int value) {
    Node* newNode = new Node(value);

    // If the list is empty, both head and tail should point to the new node
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        // Add the new node to the end of the list and update the tail
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    ++size;
}


//purely for testing purposes
int linkedList::getSize() const {
    return size;
}

int linkedList::getThirdValue() const {
    if(head && head->next) {
        return head->next->next->data;
    } else {
        return 0;
    }
}

// Print the list from the beginning
//(not the way I was taught but it works)
void linkedList::printList() const {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void linkedList::navigateList() const {
    cout << "Navigate List is called\n";
    //Check to make sure list has data 
    if (!head) {
        cout << "The list is empty." << endl;
        return;
    }

    Node* current = head;
    int blockNumber = 1;
    string choice;

    while (current != nullptr) {
        // Display current block information
        cout << "Block " << blockNumber << " has " << current->data << " trees." << endl;

        // Ask the user if they want to move forward or backward
        cout << "Enter 'forward' to move to the next block, 'back' to move to the previous block, or 'exit' to stop: ";
        cin >> choice;

        if (choice == "forward") {
            if (current->next) {
                current = current->next;
                ++blockNumber;
            } else {
                cout << "You are at the last block." << endl;
            }
        } else if (choice == "back") {
            if (current->prev) {
                current = current->prev;
                --blockNumber;
            } else {
                cout << "You are at the first block." << endl;
            }
        } else if (choice == "exit") {
            break;
        } else {
            cout << "Invalid input. Please enter 'forward', 'back', or 'exit'." << endl;
        }
    }

    cout << "Traversal finished." << endl;
}

int linkedList::search(int index) const {
    if (index < 0 || index >= size) {
        cout << "Index out of bounds!" << endl;
        return -1; // Return a sentinel value indicating an error
    }

    Node* current = head;
    int currentIndex = 0;

    // Traverse the list to find the node at the given index
    while (current != nullptr && currentIndex < index) {
        current = current->next;
        ++currentIndex;
    }

    // If current is not null, return the data at that index
    if (current != nullptr) {
        return current->data;
    }

    return -1; // Return -1 if something went wrong
}
