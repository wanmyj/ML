#include <stdio.h>
#include <stdlib.h>
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
    //////////////////////////////////////////////////////
    //////////////////////////////////////////////////////

    return 0;
}
