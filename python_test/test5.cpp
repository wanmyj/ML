// friend
// this pointer
// const object function

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

class CCar;
class CDriver
{
    public:
        void ModifyCar(CCar *pCar); 
};
class CCar
{
    private:
        int price;
        friend int MostExpensiveCar(CCar cars[], int total); // declare friend
        friend void CDriver::ModifyCar(CCar *pCar); // declare friend
};
void CDriver::ModifyCar(CCar *pCar)
{
    pCar->price += 1000; // after modification, price increases
}
int MostExpensiveCar(CCar cars[], int total)
{
    int tmpMax = -1;
    for (int i=0; i<=total; i++)
    {
        if (cars[i].price > tmpMax)
        {
            tmpMax = cars[i].price;
        }
    }
    return tmpMax;
}

class Complex
{
    public:
        double real, imag;
        void Print() {cout << real << "," << imag << endl;}
        Complex(double r, double i): real(r), imag(i) {}
        Complex AddOne()
        {
            this -> real++; // equal to real++;
            this -> Print(); // equal to Print
            return *this;
        }
};

// const object func
class Sample
{
    public:
        int value;
        void GetValue() const;
        void func() {};
        Sample() {};
};
void Sample::GetValue() const
{
    // value = 0;    //wrong! cannot access class member
    // func();        // wrong!
}

int main(int argc, char const *argv[])
{
    Complex c1(1,1), c2(0,0);
    c2 = c1.AddOne();
    c1.Print();
    c2.Print();
    return 0;
}
