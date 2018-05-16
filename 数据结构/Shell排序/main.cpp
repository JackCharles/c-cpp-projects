#include <iostream>

using namespace std;

int main()
{
    int *R,n;
    cout<<"输入待排序元素个数:";
    cin>>n;
    R=new int[n];
    for(int i=0;i<n;i++)
        cin>>R[i];

    int L=8;//初始增量大小，以后逐渐除以2

    while(L>=1)
    {
        for(int i=0;i+L<n;i++)
        {
            if(R[i]>R[i+L])
            {
                int temp=R[i];
                R[i]=R[i+L];
                R[i+L]=temp;
            }
        }

        L/=2;
    }

    for(int i=0;i<n;i++)
        cout<<R[i]<<" ";

    delete[] R;//析构R
    return 0;
}
