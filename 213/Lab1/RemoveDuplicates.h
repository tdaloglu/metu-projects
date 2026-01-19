/*
Question 2: Remove Duplicates in SortedDoublyLinkedList
*/

#ifndef REMOVE_DUPLICATES_H
#define REMOVE_DUPLICATES_H

#include "SortedDoublyLinkedList.h"

template <class T>
void SortedDoublyLinkedList<T>::RemoveDuplicates()
{
    // YOUR CODE GOES HERE
    if (head->next == tail || head->next->next == tail) return;
    else {
        DLLNode<T>* current = head->next->next;
        DLLNode<T>* prev = head->next;
        while (current != tail) {
            if (current->item == prev->item) {
                prev = current;
                RemoveFirstItem(current->item);
                current = current->next;
                continue;
            }
            prev = current;
            current = current->next;
        }
    }
}

#endif