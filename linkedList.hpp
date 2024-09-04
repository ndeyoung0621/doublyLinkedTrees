#ifndef linkedList_h
#define linkedList_h

struct Node  {
//Defining a "node", a node has data (trees), a pointer to the next node and a pointer to the previous node
    int data;
    Node* prev;
    Node* next;

    Node(int val) : data(val), prev(nullptr), next(nullptr) {}

};

class linkedList {
//defines 
    private:
        Node* head;
        Node* tail;
    public:
        linkedList() noexcept;
        void insert(int value);
        void printList () const;
};

#endif