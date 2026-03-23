// ============================================================
// File: DoublyLinkedList.h
// Author: Michael Monreal
// Description: A class template implementing a doubly linked list
//              from scratch. Supports sorted insertion, traversal,
//              linear search, merge sort, and operator overloading.
//              Demonstrates: Class Templates, Data Structures,
//              Sorting, Searching, Operator Overloading ([], <<).
// ============================================================
#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
private:
    // Internal node — wraps data of any type T
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    Node* current;   // Traversal pointer (current song)
    int listSize;

    // ---- Merge Sort helpers (private) ----
    Node* mergeSort(Node* start);
    Node* merge(Node* left, Node* right);
    Node* split(Node* start);

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    // Insertion
    void insertNode(const T& data);
    void insertSorted(const T& data);  // Maintains sorted order on insert

    // Removal
    void removeNode(const T& data);

    // Traversal
    T& traverseForward();
    T& traverseBackward();
    T& getCurrent() const;
    bool hasCurrent() const;
    void resetCurrent();

    // Search
    T* find(const T& target);  // Linear search

    // Info
    int getSize() const;
    bool isEmpty() const;

    // Merge sort (kept as algorithm demonstration;
    // sorted insertion is preferred per instructor guidance)
    void sort();

    // ---- Operator Overloads ----
    T& operator[](int index);
    const T& operator[](int index) const;

    // Friend operator<< must be defined inline for templates
    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& list) {
        typename DoublyLinkedList<T>::Node* temp = list.head;
        int i = 0;
        while (temp != nullptr) {
            os << "[" << i++ << "] " << temp->data << "\n";
            temp = temp->next;
        }
        return os;
    }
};

// ============================================================
// Template implementation (must remain in header)
// ============================================================

// ---- Constructor / Destructor ----

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : head(nullptr), tail(nullptr), current(nullptr), listSize(0) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
}

// ---- Unsorted Insertion (appends to tail) ----

template <typename T>
void DoublyLinkedList<T>::insertNode(const T& data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = tail = current = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    listSize++;
}

// ============================================================
// SORTED INSERTION — walks the list to find the correct
// position and inserts the node there, maintaining sorted
// order. Uses operator< on T for comparison.
// This avoids a separate sort pass over the entire list.
// ============================================================
template <typename T>
void DoublyLinkedList<T>::insertSorted(const T& data) {
    Node* newNode = new Node(data);

    if (head == nullptr) {
        // Empty list — new node becomes head, tail, and current
        head = tail = current = newNode;
    }
    else if (data < head->data) {
        // Insert at the beginning (before head)
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else {
        // Walk the list to find the correct sorted position
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data < data) {
            temp = temp->next;
        }
        // Insert after temp
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next != nullptr) {
            temp->next->prev = newNode;
        } else {
            tail = newNode;   // New node becomes the tail
        }
        temp->next = newNode;
    }

    if (current == nullptr) current = head;
    listSize++;
}

// ---- Removal ----

template <typename T>
void DoublyLinkedList<T>::removeNode(const T& data) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == data) {
            // If removing the current node, shift current
            if (temp == current) {
                current = temp->next ? temp->next : temp->prev;
            }
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == head) head = temp->next;
            if (temp == tail) tail = temp->prev;
            delete temp;
            listSize--;
            return;
        }
        temp = temp->next;
    }
}

// ---- Traversal ----

template <typename T>
T& DoublyLinkedList<T>::traverseForward() {
    if (current == nullptr)
        throw std::runtime_error("List is empty — cannot traverse");
    if (current->next != nullptr)
        current = current->next;
    return current->data;
}

template <typename T>
T& DoublyLinkedList<T>::traverseBackward() {
    if (current == nullptr)
        throw std::runtime_error("List is empty — cannot traverse");
    if (current->prev != nullptr)
        current = current->prev;
    return current->data;
}

template <typename T>
T& DoublyLinkedList<T>::getCurrent() const {
    if (current == nullptr)
        throw std::runtime_error("List is empty — no current element");
    return current->data;
}

template <typename T>
bool DoublyLinkedList<T>::hasCurrent() const {
    return current != nullptr;
}

template <typename T>
void DoublyLinkedList<T>::resetCurrent() {
    current = head;
}

template <typename T>
int DoublyLinkedList<T>::getSize() const {
    return listSize;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return listSize == 0;
}

// ============================================================
// SEARCH — Linear search through the list.
// Returns a pointer to the matching element, or nullptr if
// not found. Uses operator== on T for comparison.
// ============================================================
template <typename T>
T* DoublyLinkedList<T>::find(const T& target) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == target) {
            return &(temp->data);
        }
        temp = temp->next;
    }
    return nullptr;  // Not found
}

// ============================================================
// Operator Overloads
// ============================================================

// operator[] — index-based access (O(n) by nature of linked list)
template <typename T>
T& DoublyLinkedList<T>::operator[](int index) {
    if (index < 0 || index >= listSize)
        throw std::out_of_range("Index out of bounds");
    Node* temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->next;
    return temp->data;
}

template <typename T>
const T& DoublyLinkedList<T>::operator[](int index) const {
    if (index < 0 || index >= listSize)
        throw std::out_of_range("Index out of bounds");
    Node* temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->next;
    return temp->data;
}

// ============================================================
// Merge Sort — O(n log n), demonstrates sorting algorithm.
// Note: Per instructor guidance, sorted insertion via
// insertSorted() is preferred for linked lists to avoid
// hidden traversal overhead. This method is retained as
// an algorithm demonstration.
// ============================================================

template <typename T>
void DoublyLinkedList<T>::sort() {
    if (listSize <= 1) return;

    // Run merge sort on the forward chain
    head = mergeSort(head);

    // Rebuild prev links and find the new tail
    Node* temp = head;
    temp->prev = nullptr;
    while (temp->next != nullptr) {
        temp->next->prev = temp;
        temp = temp->next;
    }
    tail = temp;
    current = head;
}

// split — finds the midpoint and splits the list into two halves
template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::split(Node* start) {
    Node* slow = start;
    Node* fast = start;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* second = slow->next;
    slow->next = nullptr;
    return second;
}

// mergeSort — recursively splits and merges
template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::mergeSort(Node* start) {
    if (start == nullptr || start->next == nullptr)
        return start;

    Node* second = split(start);

    start = mergeSort(start);     // Sort left half
    second = mergeSort(second);   // Sort right half

    return merge(start, second);  // Merge sorted halves
}

// merge — combines two sorted chains using operator< on T
template <typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::merge(Node* left, Node* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    if (left->data < right->data) {
        left->next = merge(left->next, right);
        if (left->next) left->next->prev = left;
        left->prev = nullptr;
        return left;
    } else {
        right->next = merge(left, right->next);
        if (right->next) right->next->prev = right;
        right->prev = nullptr;
        return right;
    }
}
