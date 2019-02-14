//variable length int array
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

// need contructor, destructor, pull_back(), length()......
// need malloc to restore the elements, which needs a pointer
// deep overload operator
// obj[] by overloading []
// copy constructor, cannot be default 
class CArray
{
    private:
        int size;
        int *ptr;
    public:
        void push_back(int v);
        int length(){return size;}
        CArray(int s=0);
        CArray(CArray &a);
        CArray & operator= (const CArray &a);// assignment between objects
        ~CArray();
        int & operator[] (int i)
        {
            // n = a[i]; a[i] = 4;
            return ptr[i];
        }
};
CArray::CArray(int s):size(s)
{
    if(s==0)
        ptr = NULL;
    else
        ptr = new int[s];
}
CArray::CArray(CArray & a)
{
    if (!a.ptr)
    {
        ptr = NULL;
        size = 0;
        return;
    }
    ptr = new int[a.size];
    memcpy(ptr, a.ptr, sizeof(int)*a.size);
    size = a.size;
}
CArray::~CArray()
{
    if (ptr) delete []ptr;
}
CArray & CArray::operator=(const CArray &a)
{
    if (ptr == a.ptr)
        return *this;
    if (a.ptr == NULL)
    {
        if (ptr) delete [] ptr;
        ptr = NULL;
        size = 0;
        return *this;
    }
    if (size < a.size)
    {
        if(ptr) delete [] ptr;
        ptr = new int[a.size];
    }
    memcpy( ptr, a.ptr, sizeof(int)*a.size);
    size = a.size;
    return *this;
}
void CArray::push_back(int v)
{
    if(ptr)
    {
        int *tmpPtr = new int[size+1];
        memcpy(tmpPtr, ptr, sizeof(int)*size);
        delete [] ptr;
        ptr = tmpPtr;
    }
    else // origin array is empty
        ptr = new int[1];
    ptr[size++] = v;
}


int main(int argc, char const *argv[])
{
    CArray a; // empty array
    for(int i=0; i<5; i++)
    {
        a.push_back(i);   // 0~4 elements
    }
    CArray a2, a3;
    a2 = a; //a2 is a new array with same content as a
    for (int i=0; i<a2.length(); ++i)
    { cout << a2[i] << " ";} // output 0 1 2 3 4
    cout << endl;
    a2 = a3; // a2 is empty and original memory space should be released
    for (int i=0; i<a2.length(); ++i)
    { cout << a2[i] << " ";} // nothing output here
    cout << endl;
    a[3] = 100;
    CArray a4(a); //a4 = 0 1 2 100 4 
    for (int i=0; i<a4.length(); ++i)
    {cout << a4[i]<< " ";}

    return 0;
}
