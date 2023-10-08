#include <iostream>
#include <string>
using namespace std;

#ifndef QSTACK_H
#define QSTACK_H

template <class T>
class Qstack
{ // an order-list that is accessible from both ends
public:
    Qstack(int capacity=10){ // creates an empty Qstack with the given capacity
        this->capacity = capacity;
        array = new T[capacity];
        head = 0;
        tail = 0;
    }   
    bool IsEmpty() const;        // returns true if Qstack has no elements, false otherwise
    void Push(const T& item);    // adds item to front of list
    void Put(const T& item);     // adds item to end of list
    T&   Pop() const;            // returns and removes item from front of list
    T&   Pull() const;           // returns and removes item from end of list
    T&   Peek(int index);        
    // if index is non-negative Peek(i) return the ith item from the front of the
    // list. Peek(0) returns the item at the front, Peek(1) returns the next
    // item, and so on. if the index is negative Peek(i) returns the i+1 item
    // from the end of the list. Peek(-1) returns the end item, Peek(-2) returns 
    // the item second from the end, and so on. Any Peek() access outside the range 
    // of the list throws and exception
private:
    void ChangeSize1D(T *& a, const int oldSize, const int newSize);
    // feel free to use the ChangeSize1D() implementation from the book and lecture 
    T *array;
    mutable int capacity;
    mutable int head;
    mutable int tail;
};

#endif
