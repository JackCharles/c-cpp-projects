#include<iostream>
#include<stdio.h>
using namespace std;

int main()
{
    long n;
    int f;
    cout<<"************ʮ����ת������*************"<<endl;
    cout<<"������һ��ʮ������:";
    cin>>n;
    cout<<"��������Ҫת���Ľ���(������16):";
    cin>>f;
    int a[500];

    long c=f,y,s=n;
    int i=0;
    while(s!=0)
    {
		y=s%c;
        s=s/c;
		a[i]=y;
        i++;
    }
    for(i-=1;i>=0;i--)
	{

		if(a[i]>9){
			char chr;
			switch(a[i])
			{
			case 10: chr='A'; break;
			case 11: chr='B'; break;
			case 12: chr='C'; break;
			case 13: chr='D'; break;
			case 14: chr='E'; break;
			case 15: chr='F'; break;
			}
			cout<<chr<<" ";
		}
		else
			cout<<a[i]<<" ";
	}
    cout<<endl;
    return 0;
}
