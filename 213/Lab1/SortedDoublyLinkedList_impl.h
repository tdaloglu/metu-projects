#ifndef SORTED_DOUBLY_LINKED_LIST_IMPL_H
#define SORTED_DOUBLY_LINKED_LIST_IMPL_H

#include "SortedDoublyLinkedList.h"
#include "Exception.h"

// -------------------------
// Node Implementation
// -------------------------
template <class T>
DLLNode<T>::DLLNode(const T& item, DLLNode<T>* nextNode, DLLNode<T>* prevNode)
    : item(item), next(nextNode), prev(prevNode) {}

// -------------------------
// Constructors & Destructor
// -------------------------
template <class T>
SortedDoublyLinkedList<T>::SortedDoublyLinkedList() {
    head = new DLLNode<T>(T());
    tail = new DLLNode<T>(T());
    head->next = tail;
    tail->prev = head;
}

template <class T>
SortedDoublyLinkedList<T>::~SortedDoublyLinkedList() {
    Clear();
    delete head;
    delete tail;
}

// -------------------------
// Core Operations
// -------------------------
template <class T>
void SortedDoublyLinkedList<T>::InsertItem(const T& item) {
    DLLNode<T>* curr = head->next;
    while (curr != tail && (curr->item < item || curr->item == item))
        curr = curr->next;

    DLLNode<T>* newNode = new DLLNode<T>(item, curr, curr->prev);
    curr->prev->next = newNode;
    curr->prev = newNode;
}

template <class T>
void SortedDoublyLinkedList<T>::InsertItemPrior(const T& item) {
    DLLNode<T>* curr = head->next;
    while (curr != tail && curr->item < item)
        curr = curr->next;

    DLLNode<T>* newNode = new DLLNode<T>(item, curr, curr->prev);
    curr->prev->next = newNode;
    curr->prev = newNode;
}

template <class T>
T SortedDoublyLinkedList<T>::RemoveFirstItem() {
    if (IsEmpty())
        throw EmptyCollectionException();

    DLLNode<T>* node = head->next;
    T value = node->item;
    head->next = node->next;
    node->next->prev = head;
    delete node;
    return value;
}

template <class T>
T SortedDoublyLinkedList<T>::RemoveFirstItem(int priority) {
    if (IsEmpty())
        throw EmptyCollectionException();
    DLLNode<T>* curr = head->next;
    while (curr != tail) {
        if (curr->item == priority) {
            T value = curr->item;
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
            return value;
        }
        curr = curr->next;
    }
    throw NotFoundException();
}

template <class T>
T SortedDoublyLinkedList<T>::RemoveLastItem(int priority) {
    if (IsEmpty())
        throw EmptyCollectionException();
    DLLNode<T>* curr = tail->prev;
    while (curr != head) {
        if (curr->item == priority) {
            T value = curr->item;
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
            return value;
        }
        curr = curr->prev;
    }
    throw NotFoundException();
}

// -------------------------
// Query
// -------------------------
template <class T>
const T& SortedDoublyLinkedList<T>::FirstItem() const {
    if (IsEmpty())
        throw EmptyCollectionException();
    return (head->next->item);
}

template <class T>
const T& SortedDoublyLinkedList<T>::LastItem() const {
    if (IsEmpty())
        throw EmptyCollectionException();
    return (tail->prev->item);
}

template <class T>
bool SortedDoublyLinkedList<T>::IsEmpty() const {
    return head->next == tail;
}

template <class T>
size_t SortedDoublyLinkedList<T>::GetSize() const {
    size_t count = 0;
    DLLNode<T>* curr = head->next;
    while (curr != tail) {
        count++;
        curr = curr->next;
    }
    return count;
}
 
// -------------------------
// Modification
// -------------------------
template <class T>
void SortedDoublyLinkedList<T>::Clear() {
    DLLNode<T>* curr = head->next;
    while (curr != tail) {
        DLLNode<T>* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head->next = tail;
    tail->prev = head;
}

// -------------------------
// Operator <<
// -------------------------
template <class T>
std::ostream& operator<<(std::ostream& os, const SortedDoublyLinkedList<T>& list) {
    if (list.head->next == list.tail) {
        os << "Empty";
        return os;
    }
    DLLNode<T>* curr = list.head->next;
    while (curr != list.tail) {
        os << curr->item;
        if (curr->next != list.tail)
            os << " -> ";
        curr = curr->next;
    }
    return os;
}

#endif // SORTED_DOUBLY_LINKED_LIST_IMPL_H