#include <iostream>
#include "Polynomial.h"
using namespace std;

int main()
{ 
    float aCoef[] = {1.0,2.0,1.0};      // coefficients for A(x) = x^2 + 2x + 1
    float bCoef[] = {-1.0,1.0};         // coefficients for B(x) = x - 1
    Polynomial a(aCoef, 3);
    Polynomial b(bCoef, 2);
    b.setCoef(1.0,5);                   // B(x) = x^5 + x -1

    Polynomial s = a.Add(b);            // S = A(x) + B(x)
    Polynomial p = a.Mult(b);           // P = A(x) B(x)

    cout << "Degree(b) = " << b.getDegree() << endl;
    cout << a.toString() << endl;
    cout << b.toString() << endl;
    cout << s.toString() << endl;
    cout << p.toString() << endl;
    //cout << "a x b(10.0) = " << p.Eval(10.0) << endl;

    cout << b.Derivative().toString() << endl;
    cout << s.Derivative().toString() << endl;
    cout << p.Derivative().toString() << endl;
}