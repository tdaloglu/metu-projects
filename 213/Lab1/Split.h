/*
Question 3: Split a Queue
*/

#ifndef SPLIT_H
#define SPLIT_H


#include "Queue.h"

template <class T>
Queue<T>* Queue<T>::Split(int n)
{
    // YOUR CODE GOES HERE
    Queue<T>* queues = new Queue<T>[n-1];
    Queue<T> newQueue;
    int count = GetSize();
    
    for (int i = 0; i < count; i++) {
        if (i % n == 0) {
            T element = Dequeue();
            newQueue.Enqueue(element);
        } else {
            int index = i % n;
            T element = Dequeue();
            queues[index - 1].Enqueue(element);
        }
    }
    
    while (!newQueue.IsEmpty()) {
        T value = newQueue.Dequeue();
        this->Enqueue(value);
    }
    
    return queues;
}

#endif