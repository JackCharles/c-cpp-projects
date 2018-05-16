#include <iostream>
#include <time.h>
#define N 100000000
using namespace std;

int main(int argc, char* argv[])
{
    int *num=new int[N];
    for(int i=0;i<N;i++)
    {
        num[i]=i;
    }
    clock_t t1 = clock();
    int maxNum = num[0];
    int minNum = num[0];
    for(int i=0; i<N; i++)
    {
        if(num[i]>maxNum)
            maxNum = num[i];
        else if(num[i]<minNum)
            minNum = num[i];
    }
    clock_t t2=clock();
    cout<<"max : "<<maxNum<<endl;
    cout<<"min : "<<minNum<<endl;
    cout<<"time:"<<(t2-t1)/1000.0<<endl;
    return 0;
}
