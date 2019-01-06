// const member function
// const object
// const reference

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

class CTest
{
    private:
        int n;
    public:
        CTest() { n=1; }
        int GetValue() const {return n;}
        int GetValue() { return 2*n;}
};

int main(int argc, char const *argv[])
{
    const CTest objTest1;
    CTest objTest2;
    cout << objTest1.GetValue() << "," << objTest2.GetValue() << endl;
    return 0;
}
