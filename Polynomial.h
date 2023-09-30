#include <string>
using namespace std;

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial {
// p(x)=a[0] x^0 + a[1] x^1 + ... + a[n] x^n; 
// a set of ordered pairs of <int power, float coefficent>,
// where a[power] is the coefficient of x^power 
public:
    Polynomial();   
    // Construct the polynomial p(x)=0.
    Polynomial(int d);   
    // Construct a polynomial of degree "d" with coefficients initialized to 0.0.
    Polynomial(float c[], int n);
    // Construct a polynomial with n coefficients from c[] with degree n-1.    
    Polynomial Add(Polynomial poly); 
    // Return the sum of the polynomials *this and poly.
    Polynomial Mult(Polynomial poly); 
    // Return the product of the polynomials this and poly.
    float Eval(float x);
    // Evaluate the polynomial *this at x and return the result.
    void setCoef(float value, int power);
    float getCoef(int power);
    int getDegree();
    string toString();
    Polynomial Derivative();

private:
    int degree;
    float *coef;
};
#endif