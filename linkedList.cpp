#include "linkedList.hpp"
#include <iostream>

using namespace std;

linkedList::linkedList() noexcept : head(nullptr), tail(nullptr), size(0) {}

// Insert at the front
void linkedList::insert(int value) {
    Node* newNode = new Node(value);

    //As I understand it, if this is the only thing in the list besides head,
    //give this new node all the rights from the previous nodes, otherwise,
    //keep head at the front but "push" everything else back 
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    ++size;
}

//purely for testing purposes
int linkedList::getSize() const {
    return size;
}

int linkedList::getSecondValue() const {
    if(head && head->next) {
        return head->next->data;
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