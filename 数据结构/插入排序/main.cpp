#include <iostream>
#define min -9999
using namespace std;



int main()
{
    int *item,n;
    cout<<"�����������Ԫ�ظ���:";
    cin>>n;
    item=new int[n+1];
    item[0]=min;                //�趨һ����С�ı�Ƿ�ֹ��������Խ�������j>0���ж�
    cout<<"������"<<n<<"��Ԫ��:"<<endl;
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
