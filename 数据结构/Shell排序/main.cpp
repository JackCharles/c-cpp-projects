#include <iostream>

using namespace std;

int main()
{
    int *R,n;
    cout<<"���������Ԫ�ظ���:";
    cin>>n;
    R=new int[n];
    for(int i=0;i<n;i++)
        cin>>R[i];

    int L=8;//��ʼ������С���Ժ��𽥳���2

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

    delete[] R;//����R
    return 0;
}
