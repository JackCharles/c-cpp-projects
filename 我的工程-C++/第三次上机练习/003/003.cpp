#include<iostream>
using namespace std;

void f(int n,int m)//���붯̬��ά���飺������һ����СΪnָ�����飨���׵�ַ��Ϊhead��������ÿ��ָ��Ԫ���������СΪm��һά���飬
{                   //�����׵�ַ���ظ���Ӧָ�룬�������൱����n��ָ�룬ÿ��ָ������m�����ݣ������͹���һ����̬��ά����

    int**head=new int*[n];//����n��ָ��int�͵�����ָ��(��ָ̬������)���׵�ַ����head�У�int**�൱��(int*)*��ָ������ָ���ָ��
    for(int i=0;i<m;i++)
        head[i]=new int[m];//��ÿ��ָ��������m���������������ݿռ䣨����Ϊm���������飩


    int value=1;//��ֵ
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++,value++)
        head[i][j]=value;


    cout<<"����ͳ��:"<<endl;
    for(int i=0;i<n;i++)
    {
        int count_h=0;//ͳ��һ��
        for(int j=0;j<m;j++)
            count_h+=head[i][j];
        cout<<count_h<<endl;
    }


    cout<<"����ͳ��:"<<endl;
    for(int j=0;j<m;j++)
    {
        int count_l=0;//ͳ��һ��
        for(int i=0;i<n;i++)
            count_l+=head[i][j];

        cout<<count_l<<endl;
    }

    for(int i=0;i<n;i++)
        delete [] head[i];//������ɢÿһ��ָ���¶�Ӧ��m�����ݿռ�
    delete [] head;       //��ɢn������ָ��

}

int main()
{
    f(3,3);
}
