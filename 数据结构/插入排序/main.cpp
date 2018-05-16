#include <iostream>
#define min -9999
using namespace std;



int main()
{
    int *item,n;
    cout<<"请输入待排序元素个数:";
    cin>>n;
    item=new int[n+1];
    item[0]=min;                //设定一个最小的标记防止数组向下越界代替了j>0的判断
    cout<<"请输入"<<n<<"个元素:"<<endl;
    for(int i=1;i<n+1;i++)
    {
        cin>>item[i];
    }


    for(int i=2;i<=n;i++)
    {
        int j=i-1;
        int temp=item[i];
        while(temp<item[j])
        {
            item[j+1]=item[j];
            j--;
        }
        item[j+1]=temp;
    }


    for(int i=1;i<=n;i++)
        cout<<item[i]<<" ";
    return 0;
}
