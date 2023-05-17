//
// Created by horic on 11/3/2020.
//

#ifndef HEAP_HEAP_CPP
#define HEAP_HEAP_CPP

#include "Heap.h"

template<class T>
Heap<T>::Heap()
{
    this->capacity = 5;  //initial size of the dynamic array
    heapArr = new T[capacity];    //dynamic array of size initSize
    this->count = 0;
}

template<class T>
Heap<T>::Heap(unsigned int capacity)
{
    this->capacity = capacity;  //initial size of the dynamic array
    heapArr = new T[capacity];    //dynamic array of size initSize
    this->count = 0;
}

template<class T>
Heap<T>::Heap(const Heap& heap)
{
    capacity = heap.capacity;
    count = heap.count;
    heapArr = new T[heap.count];
    copy(heapArr);

    std::cout << "COPY CONSTRUCTOR\n";
}

template<class T>
Heap<T>& Heap<T>::operator =(const Heap& heap)
{
    if(this == &heap)
        return *this;

    capacity = heap.capacity;
    count = heap.count;
    heapArr = new T[heap.count];
    copy(heapArr);

    std::cout << "ASSIGNMENT OPERATOR\n";

    return *this;
}

template<class T>
Heap<T>::~Heap()
{
    delete[] heapArr;
    this->count = 0;
    this->capacity = 10;
}

template<class T>
void Heap<T>::swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<class T>
void Heap<T>::resize()
{
    this->capacity *= 2;  //double the capacity

    T* newArray = new T[capacity];
    copy(newArray);
    heapArr = newArray;
}

template<class T>
void Heap<T>::copy(T* destination)
{
    //copy over elements from old array to new array
    for(int i = 0; i < count; i++)
        *(destination + i) = *(heapArr + i);

    delete[] heapArr;   //delete old array
}

template<class T>
int Heap<T>::getParent(int i)
{
    return ((i - 1)/2);
}

template<class T>
int Heap<T>::getLeft(int i)
{
    return (i*2 + 1);
}

template<class T>
int Heap<T>::getRight(int i)
{
    return ((i*2) + 2);
}

template<class T>
void Heap<T>::push(const T& item)
{
    if(count >= capacity)   //check if the size reaches capacity
    {
        resize();
    }

    int i = count;
    heapArr[this->count] = item; //add an item to the end of the array

    while((heapArr[i] > heapArr[getParent(i)]) && (count > 0))
    {
        swap(heapArr[i], heapArr[getParent(i)]);
        i = getParent(i);
    }

    this->count++;
}

template<class T>
void Heap<T>::operator +=(const T& item)
{
    push(item);
}

template<class T>
void Heap<T>::reheapify(int parent)
{
    int top = parent;
    int left = getLeft(parent);
    int right = getRight(parent);

    if(left < count && heapArr[left] > heapArr[top])
    {
        top = left;
    }
    if(right < count && heapArr[right] > heapArr[top])
    {
        top = right;
    }

    if(top != parent)
    {
        swap(heapArr[parent], heapArr[top]);
        reheapify(top);
    }
}

template<class T>
T Heap<T>::pop()
{
    T temp = heapArr[0];    //get the first item so we can return

    this->count--;      //decrement the size
    heapArr[0] = heapArr[count];    //set the first index of the array to hold the last item in the array
    reheapify(0);

    return temp;
}

template<class T>
T Heap<T>::top() const
{
    return heapArr[0];  //return the item at the top of the heap
}

template<class T>
unsigned int Heap<T>::size() const
{
    return this->count;
}

template<class T>
unsigned int Heap<T>::getCapacity() const
{
    return this->capacity;
}

template<class T>
bool Heap<T>::empty() const
{
    return (count == 0);
}

template<class T>
void Heap<T>::printHeap() const
{
    for(int i = 0; i < size(); i++)
    {
        std::cout << heapArr[i] << " ";
    }

    std::cout << std::endl;
}

#endif