#ifndef linkedList_h
#define linkedList_h

struct Node  {
//Defining a "node", a node has data (trees), a pointer to the next node and a pointer to the previous node
    int data;
    Node* prev;
    Node* next;
    int size = 0;
    Node(int val) : data(val), prev(nullptr), next(nullptr), size(val) {}

};

class linkedList {
    private:
        Node* head;
        Node* tail;
    public:
        int size;
        linkedList() noexcept;
        public:
        Node* getHead() const;  
        void insert(int value);
        void printList() const;
        void deleteNode(Node* nodeToDelete);
        int getSize() const;
        int getThirdValue() const;
        void navigateList() const;
        int search(int index) const; // New search method
}; 

#endif