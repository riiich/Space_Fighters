//
// Created by horic on 10/11/2020.
//

#ifndef MAIN_CPP_NODE_H
#define MAIN_CPP_NODE_H

template<class T>
struct Node{
    T data;
    Node<T>* next;
    Node<T>* prev;
};


#endif //MAIN_CPP_NODE_H
