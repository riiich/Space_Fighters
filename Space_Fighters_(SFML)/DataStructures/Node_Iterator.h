//
// Created by horic on 10/11/2020.
//

#ifndef MAIN_CPP_NODE_ITERATOR_H
#define MAIN_CPP_NODE_ITERATOR_H
#include "Node.h"
#include <algorithm>

template<class T>
class Node_Iterator :public std::iterator<std::forward_iterator_tag, T>
{
public:
    Node_Iterator();
    Node_Iterator(Node<T>* curr);
    Node_Iterator& operator ++();   //prefix
    Node_Iterator& operator ++(int);   //postfix
    Node_Iterator& operator --();   //prefix
    Node_Iterator& operator --(int);    //postfix
    T& operator *();
    const T& operator *() const;
    bool operator !=(const Node_Iterator& n);
    bool operator ==(const Node_Iterator& n);

private:
    Node<T>* current;
};

#include "Node_Iterator.cpp"
#endif //MAIN_CPP_NODE_ITERATOR_H
