// member object and enclosing class
// initializer list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

class CTyre
{
    private:
        int radius;
        int width;
    public:
        CTyre(int r, int w): radius(r), width(w){}
        CTyre(){ cout << "CTyre constructor" << endl;}
        ~CTyre(){ cout << "CTyre destructor" << endl;}
};
class CEngine
{
    public:
        CEngine(){cout << "CEngine contructor" << endl;}
        ~CEngine(){cout << "CEngine destructor" << endl;}
};
class CCar
{
    private:
        int price;
        CTyre tyre;
        CEngine engine;
    public:
        CCar(int p, int tr, int w);
        CCar(){ cout << "CCar contructor" << endl;}
        ~CCar(){ cout << "CCar destructor" << endl;}
};
CCar::CCar(int p, int tr, int w):price(p), tyre(tr,w){};

int main(int argc, char const *argv[])
{
    //CCar car(20000, 17, 225);
    CCar car2;
    /* code */
    return 0;
}
