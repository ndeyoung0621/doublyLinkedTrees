#include "linkedList.hpp"
#include <iostream>

using namespace std;

linkedList::linkedList() : head(nullptr), tail(nullptr) {}

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
}

// Print the list from the beginning
void linkedList::printList() const {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}