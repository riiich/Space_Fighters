//
// Created by horic on 10/13/2020.
//

#ifndef _QUEUE_QUEUE_H
#define _QUEUE_QUEUE_H
#include <iostream>
#include "LinkedList.h"

template<class T>
class Queue {
public:
    typedef size_t size_type;

    Queue();
    void push(const T& item);   //add an item to the queue
    T pop(); //remove an item from the queue
    bool empty() const; //returns true if there are no items in the queue
    unsigned int size() const;  //return the number of items in the queue
    T front() const; //returns the item on the stop of the stack, without removing it
    T seek(size_type n); //return value is the item that is n from the top(with the top at n = 0, the next at 1, and so on)
                         //    The queue is not changed.

    template<class U>
    friend std::ostream& operator <<(std::ostream& outs, const Queue<U>& queue);

private:
    dLinkedList<T> _top;
};

#include "Queue.cpp"
#endif //_QUEUE_QUEUE_H
