//
// Created by horic on 9/24/2020.
//

#ifndef TEMPLATE_LINKED_LIST_LINKEDLIST_CPP
#define TEMPLATE_LINKED_LIST_LINKEDLIST_CPP

#include "LinkedList.h"
#include <cassert>

template<class T>
dLinkedList<T>::dLinkedList()
: head(nullptr), tail(nullptr), count(0)
{}

template<class T>
dLinkedList<T>::dLinkedList(const dLinkedList<T>& rhs)
{
    if(rhs.head == nullptr)
    {
        count = 0;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        if ( rhs.head == nullptr)
            head = tail = nullptr;
        else
        {
            head = new Node<T>;
            head->data = rhs.head->data;
            tail = head;
            Node<T> *current = rhs.head->next;

            while (current != nullptr )
            {
                tail->next = new Node<T>;
                tail->next->data = current->data;
                tail->next->prev = tail;
                tail = tail->next;
                current = current->next;
            }
            count = rhs.count;
        }



//        copy_List(rhs.head);
//        count = rhs.count;
    }

    std::cout << "COPY CONSTRUCTOR\n";
}

template<class T>
dLinkedList<T>& dLinkedList<T>::operator =(const dLinkedList<T>& list) {
    if (this == &list)
        return *this;
    else
    {
        if (list.head == nullptr)
            head = tail = nullptr;
        else
        {
            head = new Node<T>;
            head->data = list.head->data;
            tail = head;
            Node<T> *current = list.head->next;

            while (current != nullptr)
            {
                tail->next = new Node<T>;
                tail->next->data = current->data;
                tail->next->prev = tail;
                tail = tail->next;
                current = current->next;
            }
            count = list.count;

            std::cout << "COPY ASSIGNMENT OPERATOR\n";
        }
        return *this;
    }
}

template<class T>
dLinkedList<T>::~dLinkedList<T>()
{
    clear_List();
    std::cout << "DESTRUCTOR\n";
}

template<class T>
Node<T>* dLinkedList<T>::getHead() const
{
    //assert(this->tail != nullptr);
    return this->head;
}

template<class T>
Node<T>* dLinkedList<T>::getTail() const
{
    //assert(this->tail != nullptr);
    return this->tail;
}

template<class T>
void dLinkedList<T>::insert_head(const T& item)
{
    Node<T>* temp = new Node<T>;
    temp->data = item;

    if(empty())   //empty list
    {
        temp->prev = nullptr;
        temp->next = nullptr;
        this->head = temp;
        this->tail = temp;
    }
    else    //existing list
    {
        temp->prev = nullptr;
        head->prev = temp;
        temp->next = head;
        this->head = temp;
    }
    this->count++;
}

template<class T>
void dLinkedList<T>::insert_end(const T &item)
{
    Node<T>* temp = new Node<T>;
    temp->data = item;

    if(empty())   //empty list
    {
        temp->prev = nullptr;
        temp->next = nullptr;
        this->tail = temp;
        this->head = temp;
    }
    else    //existing list
    {
        temp->next = nullptr;
        temp->prev = tail;
        tail->next = temp;
        this->tail = temp;
    }

    count++;
}

template<class T>
void dLinkedList<T>::operator +=(const T& item)
{
    insert_end(item);
}

template<class T>
Node<T>* dLinkedList<T>::search_Item(const T& target) const
{
    Node<T>* walker = this->head;

    if(this->tail == nullptr)
        return nullptr;
    else
    {
        for(walker; walker != nullptr; walker = walker->next)
        {
            if(walker->data == target)
                return walker;
        }
    }

    return nullptr;
}

template<class T>
bool dLinkedList<T>::empty() const
{
    if(this->tail == nullptr && this->count == 0)
        return true;
    else
        return false;
}

template<class T>
void dLinkedList<T>::clear_List()
{
    while(this->tail != nullptr)
    {
        removeHead();
    }

    this->head = nullptr;
    this->tail = nullptr;
}

//THIS COPY FUNCTION NEEDS TO BE FIXED!!
template<class T>
void dLinkedList<T>::copy_List(const Node<T>* node1)
{
    const Node<T>* walker1 = node1;

    while(walker1 != nullptr)
    {
        insert_end(walker1->data);
        walker1 = walker1->next;
    }
}

template<class T>
int dLinkedList<T>::size() const
{
    return this->count;
}

template<class T>
void dLinkedList<T>::insertAfter(T search, const T& item)
{
    Node<T>* walker;    //walker pointer walks through list to find the item in the list

    if(empty())
        return;
    else
    {
        Node<T>* temp = new Node<T>;
        temp->data = item;  //put item into the node
        for(walker = this->head; walker != nullptr; walker = walker->next)
        {
            if(walker == search_Item(search))
            {
                if(walker == this->head)
                {
                    insert_head(item);
                }
                else if(walker == this->tail)
                {
                    insert_end(item);
                }
                else
                {
                    temp->prev = walker;
                    temp->next = walker->next;
                    walker->next = temp;
                    walker->next->prev = temp->next;
                    this->count++;
                }
            }
        }
    }
}

template<class T>
void dLinkedList<T>::insert_middle_Before(const T& item)
{
    Node<T>* walker = this->head;

    if(empty())   //checks if the list is empty or only has 1 node
        return;
    else
    {
        for(int i = 0; i < this->count/2; i++)
        {
            walker = walker->next;
        }
        insertBefore(walker->data, item);
    }
}

template<class T>
void dLinkedList<T>::insert_middle_After(const T& item)
{
    Node<T>* walker = this->head;

    if(empty())   //checks if the list is empty or only has 1 node
        return;
    else
    {
        for(int i = 0; i < this->count/2; i++)
        {
            walker = walker->next;
        }
        insertAfter(walker->data, item);
    }
}

template<class T>
void dLinkedList<T>::insertBefore(T search, const T& item)
{
    Node<T>* walker;


    if(empty()) //empty list
        return;
    else    //existing list
    {
        Node<T>* temp = new Node<T>;
        temp->data = item;

        for(walker = this->head; walker != nullptr; walker = walker->next)
        {
            if (walker == search_Item(search))
            {
                if (walker == this->head)
                {
                    insert_head(item);
                }
                else
                {
                    temp->prev = walker->prev;
                    temp->next = walker;
                    walker->prev->next = temp;
                    walker->prev = temp;
                    this->count++;
                }
            }
        }
    }
}

template<class T>
void dLinkedList<T>::remove(const T& search)
{
    Node<T>* temp = search_Item(search);

   if(temp != nullptr)
       remove(temp);
   else
       return;
}

template<class T>
void dLinkedList<T>::removeHead()
{
    remove(this->head);
}

template<class T>
void dLinkedList<T>::removeTail()
{
    remove(this->tail);
}

template<class T>
void dLinkedList<T>::remove(Node<T>* node)
{
    //node is not at the head or the tail
    if(node != this->head && node != this->tail)
    {
        node->next->prev = node->prev;
        node->prev->next = node->next;
        delete node;
    }
    else if(this->count == 1)    //check if it's only one node in the list
    {
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
    }
    //node is at the head
    else if(node == this->head)
    {
        //more than one node in the list
        this->head = this->head->next;
        delete this->head->prev;
        this->head->prev = nullptr;
    }
    else if(node == this->tail)
    {
        this->tail = this->tail->prev;
        delete this->tail->next;
        this->tail->next = nullptr;
    }
    else if(this->tail == nullptr && this->head == nullptr)
    {
//        delete head;
//        this->head == nullptr;
//        this->tail == nullptr;
        return;
    }

    this->count--;
}

template<class T>
typename dLinkedList<T>::iterator dLinkedList<T>::begin() const
{
    return iterator(this->head);
}

template<class T>
typename dLinkedList<T>::iterator dLinkedList<T>::end() const
{
    return nullptr;
}

template<class T>
std::ostream& operator <<(std::ostream& outs, const dLinkedList<T>& list)
{
    Node<T>* walker = list.head;

    for(walker; walker != nullptr; walker = walker->next)
    {
        outs << walker->data << " ";
    }
    outs << std::endl;

    return outs;
}

#endif