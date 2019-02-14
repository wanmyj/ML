// operator overloading as a member funciton

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

class Complex 
{
    double real, imag;
    public:
        Complex(double r=0, double i=0): real(r), imag(i) {}
        Complex operator+ (const Complex &); //only one parameter bcz a+b = a.operator+
        Complex operator- (const Complex &);
        friend Complex operator+(double r, const Complex &c);
};
// Complex Complex::operator+(double r)
// {
//     return Complex(real+r, imag);
//     // it works for c=c+5; not work for c=5+c;
// }
Complex operator+(double r, const Complex &c)
{
    return Complex(c.real, c.imag);
}
Complex Complex::operator+(const Complex &operatand2)
{
    return Complex(real+operatand2.real, imag+operatand2.imag);
}
Complex Complex::operator-(const Complex &operatand2)
{
    return Complex(real-operatand2.real, imag-operatand2.imag);
}

int main(int argc, char const *argv[])
{
    Complex x, y(1.3,4.01), z(3.2,2.6);
    x = y + z;
    x = y - z;
    return 0;
}
