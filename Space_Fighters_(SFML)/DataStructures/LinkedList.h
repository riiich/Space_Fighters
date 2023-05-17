//
// Created by horic on 9/24/2020.
//

#ifndef TEMPLATE_LINKED_LIST_LINKEDLIST_H
#define TEMPLATE_LINKED_LIST_LINKEDLIST_H
#include <iostream>
#include "Node_Iterator.h"

//doubly linked list
template<class T>
class dLinkedList {
public:
    typedef Node_Iterator<T> iterator;

    dLinkedList();  //default ctor
    dLinkedList(const dLinkedList<T>& rhs);    //copy ctor
    dLinkedList<T>& operator =(const dLinkedList<T>& list); //copy assignment operator
    ~dLinkedList(); //destructor
    Node<T>* getHead() const;   //get head of the list
    Node<T>* getTail() const;   //get tail of the list
    void insert_end(const T& item); //insert an item at the end of the list
    void operator +=(const T& item);    //insert an item at the end of the list with an operator
    void insert_head(const T& item);  //insert an item at the beginning of the list
    void insert_middle_Before(const T& item); //insert an item in the middle of the list before the node
    void insert_middle_After(const T& item);  //insert an item in the middle of the list after the node
    bool empty() const;     //check if the list is empty
    void clear_List();      //clear the list
    int size() const;   //get the size of the list
    void insertAfter(T search, const T& item);
    void insertBefore(T search, const T& item);
    void remove(const T& search);  //remove an item from the list
    void removeHead();  //remove the head of the list
    void removeTail();  //remove the tail of the list

    //iterators
    iterator begin() const;
    iterator end() const;

    template<class U>
    friend std::ostream& operator <<(std::ostream& outs, const dLinkedList<U>& list); //print all the items in the list

private:
    T value;
    Node<T>* head;
    Node<T>* tail;
    unsigned int count;
    void insertAfter(Node<T>* node, const T& item);
    Node<T>* search_Item(const T& target) const;     //find an item
    void remove(Node<T>* node);
    void copy_List(const Node<T>* node1);   //copy the list
};

#include "LinkedList.cpp"
#endif //TEMPLATE_LINKED_LIST_LINKEDLIST_H
