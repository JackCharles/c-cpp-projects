#include<iostream>
using namespace std;

void f(int n,int m)//申请动态二维数组：先申请一个大小为n指针数组（将首地址记为head），再在每个指针元素下申请大小为m的一维数组，
{                   //并将首地址返回给对应指针，这样就相当于有n个指针，每个指针下有m个数据，这样就构成一个动态二维数组

    int**head=new int*[n];//申请n个指向int型的连续指针(动态指针数组)，首地址记在head中，int**相当于(int*)*即指向整形指针的指针
    for(int i=0;i<m;i++)
        head[i]=new int[m];//在每个指针下申请m个连续的整形数据空间（长度为m的整形数组）


    int value=1;//赋值
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++,value++)
        head[i][j]=value;


    cout<<"按行统计:"<<endl;
    for(int i=0;i<n;i++)
    {
        int count_h=0;//统计一行
        for(int j=0;j<m;j++)
            count_h+=head[i][j];
        cout<<count_h<<endl;
    }


    cout<<"按列统计:"<<endl;
    for(int j=0;j<m;j++)
    {
        int count_l=0;//统计一列
        for(int i=0;i<n;i++)
            count_l+=head[i][j];

        cout<<count_l<<endl;
    }

    for(int i=0;i<n;i++)
        delete [] head[i];//单独解散每一个指针下对应的m个数据空间
    delete [] head;       //解散n个整形指针

}

int main()
{
    f(3,3);
}
