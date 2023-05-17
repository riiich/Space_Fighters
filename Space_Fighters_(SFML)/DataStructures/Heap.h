//
// Created by horic on 11/3/2020.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H
#include <iostream>

template<class T>
class Heap {
public:
    Heap();
    Heap(unsigned int capacity);
    Heap(const Heap& heap);
    Heap& operator=(const Heap& heap);
    ~Heap();
    int getParent(int i);
    int getLeft(int i);
    int getRight(int i);
    void push(const T& item);
    void operator +=(const T& item);
    T pop();
    T top() const;
    unsigned int size() const;
    unsigned int getCapacity() const;
    bool empty() const;
    void printHeap() const;

private:
    T* heapArr;
    unsigned int capacity;
    unsigned int count;
    void swap(T& a, T& b);
    void resize();
    void copy(T* destination);
    void reheapify(int parent);
};

#include "Heap.cpp"
#endif //HEAP_HEAP_H
