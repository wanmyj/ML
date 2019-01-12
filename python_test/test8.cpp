// operator overloading as a member funciton

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

class Complex 
{
    public:
        Complex(double r=0, double i=0): real(r), imag(i) {}
        Complex operator+ (const Complex &); //only one parameter bcz a+b = a.operator+
        Complex operator- (const Complex &);
        double real, imag;
};
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
    cout << x.real << "+i" << x.imag <<endl;
    x = y - z;
    cout << x.real << "+i" << x.imag <<endl;
    return 0;
}
