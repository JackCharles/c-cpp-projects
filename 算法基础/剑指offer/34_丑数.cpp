#include <iostream>

using namespace std;

int Min(int a, int b, int c)
{
    int min = a>b?b:a;
    return min>c?c:min;
}

int GetUglyNumber(int index)
{
    if(index <= 0)
    { return 0; }

    int *pUglyNumbers = new int[index];
    pUglyNumbers[0] = 1;
    int nextUglyIndex = 1;

    int m2 = 0, m3 = 0, m5 = 0;

    while(nextUglyIndex < index)
    {
        int min = Min(pUglyNumbers[m2] * 2, pUglyNumbers[m3] * 3, pUglyNumbers[m5] * 5);
        pUglyNumbers[nextUglyIndex] = min;

        //ºËĞÄ£¬°´Ë³ĞòÕÒ
        while(pUglyNumbers[m2] * 2 <= pUglyNumbers[nextUglyIndex])
        { ++m2; }
        while(pUglyNumbers[m3] * 3 <= pUglyNumbers[nextUglyIndex])
        { ++m3; }
        while(pUglyNumbers[m5] * 5 <= pUglyNumbers[nextUglyIndex])
        { ++m5; }

        ++nextUglyIndex;
    }

    int res = pUglyNumbers[nextUglyIndex-1];
    delete[] pUglyNumbers;

    return res;
}

int main()
{
    cout<<GetUglyNumber(1500)<<endl;
}
