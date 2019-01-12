// operator overloading

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

class Complex 
{
    public:
        Complex(double r=0, double i=0)
        {
            real = r;
            imag = i;
        }
        double real, imag;
};
Complex operator+ (const Complex &a, const Complex &b)
{
    return Complex(a.real+b.real, a.imag+b.imag);
}

int main(int argc, char const *argv[])
{
    Complex a(1,0), b(0,2), c;
    c = a + b;
    cout << c.real << "+i" << c.imag <<endl;
    return 0;
}
