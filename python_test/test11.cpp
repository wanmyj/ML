
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
        friend ostream & operator<< (ostream &os, const Complex &c);
        friend istream & operator>> (istream &is, Complex &c);
};
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

ostream & operator<<(ostream &os, const Complex &c)
{
    os<<c.real<<"+"<<c.imag<<"i";
    return os;
}
istream & operator>>(istream &is, Complex &c)
{
    string s;
    is >> s; // read as a string
    int pos  = s.find("+",0);
    string sTmp = s.substr(0, pos); //find the string represents real
    c.real = atof(sTmp.c_str()); 
    sTmp = s.substr(pos+1, s.length()-pos-2); // find the string represents imag
    c.imag = atof(sTmp.c_str());
    return is;
}
int main(int argc, char const *argv[])
{
    Complex c;
    int n;
    cin >> c >> n;
    cout << c << "," << n;

    return 0;
}