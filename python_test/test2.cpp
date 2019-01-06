#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

/////////////////////////////////////////////////////
// Copy constructor
class Complex
{
    public:
        double real, imag;
    Complex(){};
    Complex(const Complex &c)
    {
        real = c.real;
        imag = c.imag;
        cout<<"Copy constructor called"<<endl;
    }
};
// a function's formal parameter is the object of class A, then when this function is calles, the copy constructor of class A is called
class A
{
    public:
    int v;
    A(){v = 10;};
    A(int n){v = n;};
    A(const A &a)
    {
        v = a.v;
        cout <<"Copy Constructor is called"<<endl;
    }
};

void Func(A a1){}   
A Func()
{
    A b(4);
    return b;
}

// conversion constructor
class Complex2
{
    public:
        double real, imag;
        Complex2(int i)
        {
            // conversion constructor
            cout << "int Constructor called"<<endl;
            real = i; imag = 0;
        }
        Complex2(double r, double i)
        {   real = r; imag = i;}
};

/////////////////////////////////////////////////////


int main()
{
    /////////////////////////////////////////////////
    Complex c1;
    Complex c2(c1);

    A a2;
    Func(a2);
    cout<<"---"<<endl;
    cout <<Func().v<<endl;

    // converison constructor
    Complex2 c3(7,8);
    Complex2 c4 = 12; // = operator is to initialize, not to assignment. conversion constructor called without temporary class object  
    cout << "---" << endl;
    c3 = 9; // = is a assignment operator. 9 is converted to be a temporary Complex2 object
    cout << c3.real << "," << c3.imag << endl;
    return 0;
}