#include <iostream>

using namespace std;

int main()
{
    int *R, n;
    cout << "输入待排序元素个数:";
    cin >> n;
    R = new int[n];
    for(int i = 0; i < n; i++)
        cin >> R[i];

    int Bound=n-1;//最大限度减少循环次数
    while(Bound!=0)
    {
        int t=0;//t记录每次循环的交换的最大位置,此后只需要在小于t的部分排序即可,如果t=0表示无交换排序完成
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
