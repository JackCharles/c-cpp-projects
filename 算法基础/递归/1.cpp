#include <iostream>
using namespace std;

int an(int n)
{
    if(n < 0)
    {
        return -1;
    }
    if(0 == n)
    {
        return 1;
    }
    return n*an(n-1);
}


int main()
{
    cout<<an(5)<<endl;

    return 0;
}
