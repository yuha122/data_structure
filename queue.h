#include <string>
#include <iostream>
using namespace std;

#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue
{
public:
    Queue(int QueueCapacity = 10);  // constructor
    ~Queue();                       // destructor

    int Size() const;           // return the number of elements in Queue
    bool IsEmpty() const;       // return true if the Queue is empty; false otherwise

    void Push(const T&);        // insert an integer into the Queue
    T& Pop();                   // return and remove an integer from the Queue
    string toString();          // render the Queue's contents

private:
    T *array;
    int capacity;               // capacity of array
    int head;                   // position of the front element
    int tail;                   // position of the rear element
    bool iamfull;
};

#endif