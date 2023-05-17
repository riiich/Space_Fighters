//
// Created by horic on 10/13/2020.
//
#ifndef _QUEUE_QUEUE_CPP
#define _QUEUE_QUEUE_CPP

#include "Queue.h"

template<class T>
Queue<T>::Queue()
{}

template<class T>
void Queue<T>::push(const T& item)
{
    _top.insert_head(item);
}

template<class T>
T Queue<T>::pop()
{
    if(Queue<T>::empty())
    {
        std::cout << "Empty Queue!\n";
        exit(1);
    }
    else
    {
        T temp;
        temp = _top.getTail()->data;
        _top.removeTail();

        return temp;
    }
}

template<class T>
bool Queue<T>::empty() const
{
    return _top.empty();
}

template<class T>
unsigned int Queue<T>::size() const
{
    return _top.size();
}

template<class T>
T Queue<T>::front() const
{
    return _top.getTail()->data;
}

template<class T>
T Queue<T>::seek(size_type n)
{
    Node<T>* temp;
    unsigned int count = 0;

    for(temp = _top.getHead(); (temp->next != nullptr) && (count < n); temp = temp->next)
    {
        count++;
    }

    return temp->data;
}

template<class T>
std::ostream& operator <<(std::ostream& outs, const Queue<T>& queue)
{
    if(queue.empty())
        outs << "Empty Queue!\n";
    else
    {
        outs << queue._top << " ";
        outs << std::endl;
    }

    return outs;
}

#endif