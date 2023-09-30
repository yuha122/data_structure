#include <string>
#include <cstdio>
#include "Polynomial.h"
using namespace std;

Polynomial::Polynomial()
{ // A null constructor
    degree = 0;
    coef = (float *) NULL;
}

Polynomial::Polynomial(int power)
{ // Constructs a polynomial that 
  // can hold upto the given power
    degree = power + 1;
    coef = new float[degree];
    for (int i = 0; i < degree; i++)
        coef[i] = 0.0;
}

Polynomial::Polynomial(float c[], int n)
{ // Constructs a polynomial from an array of coefficents
    degree = n;
    coef = new float[n];
    for (int i = 0; i < n; i++)
        coef[i] = c[i];
}

void Polynomial::setCoef(float value, int power)
{
    if (power >= degree) { // grows the coefficent array if needed
        float *newcoef = new float[power + 1];
        for (int i = 0; i < power; i++)
            newcoef[i] = (i < degree) ? coef[i] : 0.0f;
        delete coef;
        degree = power + 1;
        coef = newcoef;
    }
    coef[power] = value;
}

float Polynomial::getCoef(int power)
{
    return (power < degree) ? coef[power] : 0.0f; 
}

int Polynomial::getDegree()
{
    for (int power = degree - 1; power >= 0; power--)
        if (power > 0)
            return power;
    return 0;
}

Polynomial Polynomial::Add(Polynomial poly)
{
    int maxDegree = (poly.degree > this->degree) ? poly.degree : this->degree; 
    Polynomial p(maxDegree);
    for (int i = 0; i < maxDegree; i++)
        p.setCoef(this->getCoef(i) + poly.getCoef(i), i);
    return p;
}

Polynomial Polynomial::Mult(Polynomial poly)
{
    Polynomial p(this->degree + poly.degree - 1);
    for (int i = 0; i < this->degree; i++)
        for (int j = 0; j < poly.degree; j++)
            p.setCoef(this->getCoef(i) * poly.getCoef(j) + p.getCoef(i+j), i+j);
    return p;
}

float Polynomial::Eval(float x)
{
    float value = this->coef[0];
    float power = x;
    for (int i = 1; i < this->degree; i++) {
        value += this->coef[i]*power;
        power *= x;
    }
    return value;
}

string Polynomial::toString()
{
    string poly;
    bool first = true;
    for (int power = degree - 1; power >= 0; power--) {
        if (coef[power] == 0.0f)
            continue;
        if (first) {
            first = false;
            poly = to_string(coef[power]);
        } else 
        if (coef[power] > 0.0f)
            poly += " + " + to_string(coef[power]);
        else
            poly += " - " + to_string(-coef[power]);
        if (power > 1)
            poly += " x^" + to_string(power);
        else
        if (power > 0)
            poly += " x";
    }
    return poly;
}

Polynomial Polynomial::Derivative() {
    Polynomial p(degree-1);
    for (int i = 1; i < degree; i++) {
        p.setCoef(i*coef[i], i-1);
    }
    return p;
}
