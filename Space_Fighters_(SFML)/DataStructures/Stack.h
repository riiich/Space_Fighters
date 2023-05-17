//
// Created by horic on 10/13/2020.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H
#include "LinkedList.h"

template<class T>
class Stack {
public:
    typedef size_t size_type;

    Stack();    //initialize empty stack
    void push(const T& item);   //add an item to the stack
    T pop(); //remove an item from the stack
    bool empty() const; //returns true if there are no items in the stack
    unsigned int size() const;  //return the number of items in the stack
    T& top() const; //returns the item on the top of the stack, without removing it
    T seek(size_type n); //return value is the item that is n from the top(with the top at n = 0, the next at 1, and so on)
                         //    The stack is not changed.

    template<class U>
    friend std::ostream& operator <<(std::ostream& outs, const Stack<U>& stack);

private:
    dLinkedList<T> _top;
};

#include "Stack.cpp"
#endif //STACK_STACK_H
