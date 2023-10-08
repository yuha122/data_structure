#include <iostream>
#include <string>
#include "Qstack.h"
using namespace std;


template <class T>
bool Qstack<T>::IsEmpty() const {return (head == tail);}

template <class T>
void Qstack<T>::Push(const T& item)
{
    if (head > capacity / 2){
        copy(array+head, array+tail+1, array);
        tail -= head;
        head = 0;
        if ((tail - head) * 4 <= capacity){
            ChangeSize1D(array, capacity, capacity/2);
            capacity /= 2;
        }
    }
    if (head == 0){
        if (tail == capacity){
            ChangeSize1D(array, capacity, 2*capacity);
            capacity *= 2;
        }
        else{
            copy(array+head, array+tail, array+head+1);
            head += 1;
            tail += 1;
        }
    }
    array[--head] = item;
}

template <class T>
void Qstack<T>::Put(const T& item)
{
    if (tail < capacity / 2){
        if ((tail - head) * 4 <= capacity){
            ChangeSize1D(array, capacity, capacity/2);
            capacity /= 2;
        }
    }
    if (tail == capacity) {
        if (head == 0) {  
            ChangeSize1D(array, capacity, 2*capacity);
            capacity *= 2;
        } else {                    
            copy(array+head, array+tail, array+head-1);
            head -= 1;
            tail -= 1;
        }
    }
    array[tail++] = item;
}

template <class T>
T& Qstack<T>::Pop() const
{
    if (IsEmpty()) throw "Qstack is empty, cannot Pop";
    return array[head++];

}

template <class T>
T& Qstack<T>::Pull() const
{
    if (IsEmpty()) throw "Qstack is empty, cannot Pull";
    return array[tail--];
}



template <class T>
T& Qstack<T>::Peek(int index)
{
    if (index >= tail - head || index < head - tail) throw "out of range, cannot Peek";
    if (index >= 0){
        return array[head + index];
    }
    else{
        return array[tail + index];
    }
}

template <class T>
void Qstack<T>::ChangeSize1D(T *& a, const int oldSize, const int newSize)
{
    if (newSize < 0)
        throw "New length must be >= 0";
    T *temp = new T[newSize];           // new array
    copy(a, a+min(oldSize, newSize), temp);
    delete [] a;                        // deallocate old array
    a = temp;
}

template class Qstack<int>;
template class Qstack<float>;

/*********************
     

************************/