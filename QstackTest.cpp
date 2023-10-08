#include <iostream>
#include <string>
#include "Qstack.h"
using namespace std;

int main(){

    Qstack<int> qstack;
    /*for (int i = 0; i < 10; i++){
        qstack.Put(i);
    }*/

   qstack.Push(-1);
   qstack.Push(0);

    for (int i = 0; i < 11; i++){
        cout << qstack.Peek(i) << " ";
    }
    
}