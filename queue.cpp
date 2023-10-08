#include <string>
#include "queue.h"

template <class T>
Queue<T>::Queue(int QueueCapacity)
{
    capacity = QueueCapacity;
    if (capacity < 1)
        throw "capacity must be > 0";
    array = new T[capacity];
    head = 0;
    tail = 0;   
    iamfull = false; 
}

template <class T>
Queue<T>::~Queue() { delete [] array; }

template <class T>
inline int Queue<T>::Size() const { 
    return ((tail + capacity - head) % capacity);
}

template <class T>
inline bool Queue<T>::IsEmpty() const { return Size() == 0;}  // bug in book

template <class T>
void Queue<T>::Push(const T& x) {
    if (iamfull) throw "Queue is full, cannot Push";
    array[tail] = x;
    tail = (tail + 1) % capacity;
    iamfull = (tail == head);
}

template <class T>
T& Queue<T>::Pop() {
    if (IsEmpty()) throw "Queue is empty, cannot Pop";
    T& value = array[head];
    head = (head + 1) % capacity;
    return value;
}

/****************
template <class T>
void ChangeSize1D(T *&a, const int oldSize, const int newSize)
{
    if (newSize < 0)
        throw "New length must be >= 0";
    T *temp = new T[newSize];           // new array
    copy(a, a+min(oldSize, newSize), temp);
    delete [] a;                        // deallocate old array
    a = temp;
}


template <class T>
void Queue<T>::Push(const T& x) {
    if (tail == capacity) {
        if (2*Size() > capacity) {  // grow it
            ChangeSize1D(array, capacity, 2*capacity);
            capacity *= 2;
        } else {                    // shift it
            copy(array+head,array+tail, array);
            tail -= head;
            head = 0;
        }
    }
    array[tail++] = x;
}

template <class T>
T& Queue<T>::Pop() {
    if (IsEmpty()) throw "Queue is empty, cannot Pop";
    T& value = array[head++];
    if (head >= capacity/2) {
        copy(array+head,array+tail+1,array);
        tail -= head;
        head = 0;
        if (4*Size() <= capacity) {
            ChangeSize1D(array, capacity, capacity/2);
            capacity /= 2;
        }
    }
    return value;
}
***************************/
template <class T>
string Queue<T>::toString()
{
    string rval = "capacity = ";
    rval += to_string(capacity);
    rval += "\nsize = ";
    rval += to_string(Size());
    for (int i = 0; i < capacity; i++) {
        rval += "\n" + to_string(array[i]); 
        rval += (i == head ? "<-- head" : (i == tail) ? "<-- tail" : "");
    }
    rval += "\n";
    return rval;
}

template class Queue<int>;    // a Queue for ints
template class Queue<float>;  // a Queue for floats