// THIS FILE IS NOT GRADED
// THIS FILE I FOR YOU TO TEST YOUR CODES WITH YOURN OWN CUSTOM TEST CASES

#include "SinglyLinkedList.h"
#include "SortedDoublyLinkedList.h"
#include "Queue.h"

int main()

{
    Queue<int>  q;
    for(int i = 0; i < 3 ; i++)
    {
        q.Enqueue(i*5 + 5);
    }
    std::cout << "Before split:" << std::endl;
    std::cout << "original queue: " << q; // std::endl is included in operator<<

    Queue<int>* new_queues = q.Split(5);

    std::cout << "After split:" << std::endl;
    std::cout << "original queue: " << q;
    for(int i = 0; i < 4; i++)
        std::cout << "new_queue_" << i << ": "<< new_queues[i];

    delete[] new_queues;
    return 0;
}
