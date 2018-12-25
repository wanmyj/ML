#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
/////////////////////////////////////////////////////
// funciton pointer
// int (*pf) (int, char);

// example 1
void PrintMin(int a, int b)
{
    if (a<b)
    {
        printf("%d\n", a);
    }
    else
    {
        printf("%d\n", b);
    }
}
//////////////////////////////////////////////////////
// example 2
int MyCompare(const void *elem1, const void *elem2)
{
    unsigned int *p1, *p2;
    p1 = (unsigned int *)elem1;
    p2 = (unsigned int *)elem2;
    return (*p1%10)-(*p2%10);
}
#define NUM 5

//////////////////////////////////////////////////////
// quote
// int n = 4;
// int &r = n;
void swap(int &a, int &b)
{
    int temp;
    temp = a; a = b; b = temp;
}
int n = 4;
int & SetValue(){return n;}
//////////////////////////////////////////////////////
// class
class CRectangle
{
    public:
    int w, h;

    void init(int w_, int h_)
    {
        w = w_; h = h_;
    }
    int Area()
    {
        return w*h;
    }
    int Parimeter()
    {
        return 2*(w+h);
    }
};
class CEmployee
{
    private:
        char szName[30];
    public:
        int salary;
        void setName(const char *name);
        void getName(char *name);
        void averageBalary(CEmployee e1, CEmployee e2);
};
void CEmployee::setName(const char *name)
{
    strcpy(szName, name); //ok
}
void CEmployee::getName(char *name)
{
    strcpy(name, szName);
}
void CEmployee::averageBalary(CEmployee e1, CEmployee e2)
{
    salary = (e1.salary + e2.salary)/2;
}
//overload member function
class Location
{
    private:
        int x,y;
    public:
        void initial(int X=0, int Y=0);
        void valueX(int val) { x=val; }
        int valueX() {return x;}
};
void Location::initial(int X, int Y)
{
    x = X; y = Y;
}
// constructor
class Complex
{
    private:
        double real, imag;
    public:
        void Set(double r, double i);
        Complex(double r, double i);
        Complex(double r);
        Complex(Complex c1, Complex c2);
};
Complex::Complex(double r, double i)
{
    real = r; imag = i;
}
Complex::Complex(double r)
{
    real = r; imag = 0;
}
Complex::Complex(Complex c1, Complex c2)
{
    real = c1.real + c2.real;
    imag = c1.imag + c2.imag;
}
// constructor in the use of string
class CSample
{
        int x;
    public:
        CSample()
        {
            cout<<"Constructor 1 called"<<endl;
        }
        CSample(int n)
        {
            x = n;
            cout<<"Constructor 2 called"<< endl;
        }
};
//////////////////////////////////////////////////////


int main()
{
    //////////////////////////////////////////////////////
    // example 1
    void (*pf) (int, int);
    int x=4, y=5;
    pf = PrintMin;
    pf(x, y);
    printf("\n");

    //////////////////////////////////////////////////////
    // example 2
    unsigned int an[NUM] = {8, 123,11,10,4};
    qsort(an, NUM, sizeof(unsigned int), MyCompare);
    for (int i=0; i<NUM; i++)
    {
        printf("%d", an[i]);
    }
    printf("\n");
    //////////////////////////////////////////////////////
    // bit operation
    int n1 = 15;
    short n2 = -15;
    unsigned short n3 = 0xffe0;
    n1 = n1>>2;
    n2 >>= 3;
    n3 >>= 4;
    char c = 15;
    c >>= 3;
    printf("n1=%d, n2 = %x, n3 = %x, c = %x", n1, n2, n3, c);
    //////////////////////////////////////////////////////
    // quote
    int q1 = 1, q2 = 2;
    swap(q1, q2);
    printf("\nn1 = %d, n2 = %d\n", q1, q2);
    SetValue() = 40;
    cout<<n<<endl;
    //////////////////////////////////////////////////////
    // class
    int w, h;
    CRectangle r; //object
    cout <<"class rectangle" << endl;
    cin >> w >> h;
    r.init(w, h);
    cout << r.Area() << endl << r.Parimeter()<<endl;

    CEmployee e;
        // strcpy(e.szName, "Tom123"); //wrong it's private
    e.setName("Tom");
    e.salary = 5000;

    //overload member function
    cout<< "overload member function"<<endl;
    Location A;
    A.initial(5);
    cout<<A.valueX()<<endl;

    //constructor
        // Complex c1; // default constructor will be called
        // Complex *pc = new Complex; // default constructor will be called
    Complex c1(2); // OK
    Complex c3(2,4), c2(3,5);
    Complex c4(c1, c2);
    Complex *pc = new Complex(3,4);
    
    // constructor in the use of string
    CSample array1[2]; // initialize with non-para function
    cout << "step1" <<endl;
    CSample array2[2] = {4,5};
    cout << "step2" <<endl;
    CSample array3[2] = {3};
    cout << "step3" <<endl;
    CSample *array4 = new CSample[2];
    delete []array4;    
    //////////////////////////////////////////////////////
    //////////////////////////////////////////////////////

    return 0;
}
