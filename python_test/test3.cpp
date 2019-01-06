// constructor and destructor demo
// static member

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

class Demo
{
    int id;
    public:
        Demo(int i)
        {
            id = i;
            cout << "id=" << id << "constructed" << endl;
        }
        ~Demo()
        {
            cout << "id=" << id << "Destructed" << endl;
        }
};
Demo d1(1);
void Func()
{
    static Demo d2(2); //static object destructed after the program
    Demo d3(3);
    cout << "Func" << endl;
}

// static memeber
class CRectangle
{
    private:
        int w, h;
        static int nTotalArea;
        static int nTotalNum;
    public:
        CRectangle(int w_, int h_);
        CRectangle(CRectangle &r);
        ~CRectangle();
        static void PrintTotal();
};
CRectangle::CRectangle(int w_, int h_)
{
    w = w_;
    h = h_;
    nTotalNum ++;
    nTotalArea += w*h;
}
CRectangle::CRectangle(CRectangle &r) // copy constructor
{
    w = r.w; h = r.h;
    nTotalNum ++;
    nTotalArea += w*h;
}
CRectangle::~CRectangle()
{
    nTotalNum --;
    nTotalArea -= w*h;
}
void CRectangle::PrintTotal()
{
    cout << nTotalNum << "," << nTotalArea << endl;
}
int CRectangle::nTotalNum = 0;
int CRectangle::nTotalArea = 0; // must be initialized



int main()
{
    Demo d4(4);
    d4 = 6;
    cout << "main" << endl;
    { Demo d5(5); } // action scope, after this field, all constructor should be destructed
    Func();
    cout << "main ends" << endl;

    CRectangle r1(3,3), r2(2,2);
    // cout << CRectangle::nTotalNum; // wrong, private
    CRectangle::PrintTotal();
    r1.PrintTotal();

    return 0;
}