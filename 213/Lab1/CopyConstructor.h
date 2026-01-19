/*
Question 1: Copy Constructor of SinglyLinkedList
*/

#ifndef COPY_CONSTRUCTOR_H
#define  COPY_CONSTRUCTOR_H

#include "SinglyLinkedList.h"

template <class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
{
    // YOUR CODE GOES HERE
    head = new SLLNode<T>(T(), NULL);
    SLLNode<T>* current = other.head->next;
    while (current != NULL) {
        PushBack(current->data);
        current = current->next;
    }
}

#endif