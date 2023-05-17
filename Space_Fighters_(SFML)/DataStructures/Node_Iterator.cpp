//
// Created by horic on 10/11/2020.
//

#ifndef MAIN_CPP_NODE_ITERATOR_CPP
#define MAIN_CPP_NODE_ITERATOR_CPP

#include "Node_Iterator.h"

template<class T>
Node_Iterator<T>::Node_Iterator()
{
    this->current = nullptr;
}

template<class T>
Node_Iterator<T>::Node_Iterator(Node<T> *curr)
{
    this->current = curr;
}

template<class T>
Node_Iterator<T>& Node_Iterator<T>::operator ++()
{
    current = current->next;

    return *this;
}

template<class T>
Node_Iterator<T>& Node_Iterator<T>::operator ++(int)
{
    Node_Iterator<T> temp(current);

    current = current->next;

    return temp;
}

template<class T>
Node_Iterator<T>& Node_Iterator<T>::operator --()
{
    current = current->prev;

    return *this;
}

template<class T>
Node_Iterator<T>& Node_Iterator<T>::operator --(int)
{
    Node_Iterator<T> temp(current);

    current = current->prev;

    return temp;
}

template<class T>
T& Node_Iterator<T>::operator *()
{
    return current->data;
}

template<class T>
const T& Node_Iterator<T>::operator *() const
{
    return current->data;
}

template<class T>
bool Node_Iterator<T>::operator !=(const Node_Iterator& n)
{
    return (current != n.current);
}

template<class T>
bool Node_Iterator<T>::operator ==(const Node_Iterator& n)
{
    return (current == n.current);
}

#endif