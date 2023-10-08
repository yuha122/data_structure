#include <iostream>
#include "queue.h"
using namespace std;

int main()
{
    Queue<int> queue;     // a Queue for ints

    for (int i = 1; i <= 8; i++)
        queue.Push(i*i);
    cout << queue.toString() << endl;

    for (int i = 0; i < 4; i++)
        cout << i + 1 << "번째 Pop: " << queue.Pop() << endl;
    cout << queue.toString() << endl;

    for (int i = 0; i < 4; i++)
        queue.Push(i * 100);
    cout << queue.toString() << endl;

    for (int i = 0; i < 6; i++)
        cout << i + 1 << "번째 Pop: " << queue.Pop() << endl;
    cout << queue.toString() << endl;

    
}