#include <iostream>

using namespace std;

int main()
{
    int *R, n;
    cout << "���������Ԫ�ظ���:";
    cin >> n;
    R = new int[n];
    for(int i = 0; i < n; i++)
        cin >> R[i];

    int Bound=n-1;//����޶ȼ���ѭ������
    while(Bound!=0)
    {
        int t=0;//t��¼ÿ��ѭ���Ľ��������λ��,�˺�ֻ��Ҫ��С��t�Ĳ������򼴿�,���t=0��ʾ�޽����������
        for(int i=0;i<Bound;i++)
        {
            if(R[i]>R[i+1])
            {
                int temp=R[i+1];
                R[i+1]=R[i];
                R[i]=temp;
                t=i;
            }
        }
        Bound=t;
    }

    for(int i=0;i<n;i++)
        cout<<R[i]<<" ";

    delete[] R;
    return 0;
}
