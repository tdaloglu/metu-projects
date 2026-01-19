#ifndef SINGLY_LINKED_LIST_IMPL_H
#define SINGLY_LINKED_LIST_IMPL_H

#include "SinglyLinkedList.h"
#include "Exception.h"

// -------------------------
// Node Implementation
// -------------------------
template <class T>
SLLNode<T>::SLLNode(const T& data, SLLNode<T>* next)
    : data(data), next(next) {}

// -------------------------
// Constructors & Destructor
// -------------------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    // dummy head node
    head = new SLLNode<T>(T(), NULL);
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    Clear();
    delete head; 
}

// -------------------------
// Basic Operations
// -------------------------
template <class T>
void SinglyLinkedList<T>::PushFront(const T& value) {
    SLLNode<T>* newNode = new SLLNode<T>(value, head->next);
    head->next = newNode;
}

template <class T>
void SinglyLinkedList<T>::PushBack(const T& value) {
    SLLNode<T>* curr = head;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = new SLLNode<T>(value, NULL);
}

template <class T>
T SinglyLinkedList<T>::PopFront() {
    if (head->next == NULL) {
        throw EmptyCollectionException();
    }

    SLLNode<T>* temp = head->next;
    T value = temp->data;
    head->next = temp->next;
    delete temp;
    return value;
}

template <class T>
T SinglyLinkedList<T>::PopBack() {
    if (head->next == NULL) {
        throw EmptyCollectionException();
    }

    SLLNode<T>* curr = head;
    while (curr->next->next != NULL)
        curr = curr->next;

    T value = curr->next->data;
    delete curr->next;
    curr->next = NULL;
    return value;
}

// -------------------------
// Accessors
// -------------------------
template <class T>
bool SinglyLinkedList<T>::IsEmpty() const {
    return head->next == NULL;
}

template <class T>
size_t SinglyLinkedList<T>::GetSize() const {
    size_t count = 0;
    SLLNode<T>* curr = head->next;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

template <class T>
T& SinglyLinkedList<T>::Front() {
    if (head->next == NULL)
        throw EmptyCollectionException();

    return (head->next->data);
}

template <class T>
const T& SinglyLinkedList<T>::Front() const {
    if (head->next == NULL)
        throw EmptyCollectionException();

    return (head->next->data);
}

template <class T>
T& SinglyLinkedList<T>::Back() {
    if (head->next == NULL)
        throw EmptyCollectionException();

    SLLNode<T>* curr = head->next;
    while (curr->next != NULL)
        curr = curr->next;

    return (curr->data);
}

template <class T>
const T& SinglyLinkedList<T>::Back() const {
    if (head->next == NULL)
        throw EmptyCollectionException();

    SLLNode<T>* curr = head->next;
    while (curr->next != NULL)
        curr = curr->next;

    return (curr->data);
}

// -------------------------
// Searching & Removal
// -------------------------
template <class T>
bool SinglyLinkedList<T>::Contains(const T& value) const {
    SLLNode<T>* curr = head->next;
    while (curr != NULL) {
        if (curr->data == value)
            return true;
        curr = curr->next;
    }
    return false;
}

template <class T>
bool SinglyLinkedList<T>::Remove(const T& value) {
    SLLNode<T>* curr = head;
    while (curr->next != NULL && curr->next->data != value)
        curr = curr->next;

    if (curr->next == NULL)
        return false;

    SLLNode<T>* temp = curr->next;
    curr->next = curr->next->next;
    delete temp;
    return true;
}

// -------------------------
// Utility
// -------------------------
template <class T>
void SinglyLinkedList<T>::Clear() {
    while (head->next != NULL)
        PopFront();
}

template <class T>
void SinglyLinkedList<T>::Reverse() {
    SLLNode<T>* prev = NULL;
    SLLNode<T>* curr = head->next;
    SLLNode<T>* next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    head->next = prev;
}

// -------------------------
// Operator << Overload
// -------------------------
template <class T>
std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& list) {
    if (list.head->next == NULL) {
        os << "Empty";
        return os;
    }
    SLLNode<T>* curr = list.head->next; 
    while (curr != NULL) {
        os << curr->data;
        if (curr->next != NULL)
            os << " -> ";
        curr = curr->next;
    }
    return os;
}

#endif // SINGLY_LINKED_LIST_IMPL_H