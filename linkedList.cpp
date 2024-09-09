#include "linkedList.hpp"
#include <iostream>
#include <map>


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

Node* linkedList::getHead() const {
    return head;
}

void linkedList::navigateList() const {
    if (!head) {
        cout << "The list is empty." << endl;
        return;
    }

    Node* current = head;
    int blockNumber = 1;

    // Check if the second value is 12, if so, set block number to 6
    if (head->next && head->next->data == 12) {
        blockNumber = 6;
    }

    string choice;

    // Define a map to associate block numbers with street names
    map<int, string> blockMessages = {
        {1, "Ruby-Lidgerwood"},
        {2, "Lidgerwood-Astor"},
        {3, "Astor-Addison"},
        {4, "Addison-Standard"},
        {5, "Standard-Dakota"},
        {6, "Dakota-Cincinnati"},
        {7, "Cincinnati-Hamilton"}
    };

    while (current != nullptr) {
        string blockMessage;

        // Check if there's a custom message for the current block number
        if (blockMessages.find(blockNumber) != blockMessages.end()) {
            blockMessage = blockMessages[blockNumber];
        } else {
            blockMessage = "Block " + to_string(blockNumber);
        }

        cout << blockMessage << " has " << current->data << " trees." << endl;

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

void linkedList::deleteNode(Node* nodeToDelete) {
    if (!nodeToDelete) {
        return;
    }
    
    // Adjust pointers
    if (nodeToDelete == head) {
        head = nodeToDelete->next;
        if (head) {
            head->prev = nullptr;
        }
    } else {
        nodeToDelete->prev->next = nodeToDelete->next;
    }
    
    if (nodeToDelete == tail) {
        tail = nodeToDelete->prev;
        if (tail) {
            tail->next = nullptr;
        }
    } else {
        nodeToDelete->next->prev = nodeToDelete->prev;
    }
    
    delete nodeToDelete;
    --size;
}
