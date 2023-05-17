//
// Created by horic on 10/13/2020.
//

#ifndef STACK_STACK_CPP
#define STACK_STACK_CPP

#include "Stack.h"

template<class T>
Stack<T>::Stack()
{

}

template<class T>
void Stack<T>::push(const T &item)
{
    _top.insert_head(item);
}

template<class T>
T Stack<T>::pop()
{
    if(Stack<T>::empty())
    {
        std::cout << "Empty Stack!\n";
        exit(1);
    }
    else
    {
        T temp;
        temp = _top.getHead()->data;    //get the item at the top of the list
        _top.removeHead();  //remove the item at the top of the list

        return temp;    //return the item that was on the top of the list previous to removing
    }
}

template<class T>
bool Stack<T>::empty() const
{
    return _top.empty();
}

template<class T>
unsigned int Stack<T>::size() const
{
    return _top.size();
}

template<class T>
T& Stack<T>::top() const
{
    return _top.getHead()->data;
}

template<class T>
T Stack<T>::seek(size_type n)
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
std::ostream& operator <<(std::ostream& outs, const Stack<T>& stack)
{
    if(stack.empty())
        outs << "Empty Stack!\n";
    else
    {
        outs << stack._top << " ";
        outs << std::endl;
    }

    return outs;
}


#endif