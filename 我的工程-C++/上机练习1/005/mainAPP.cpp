#include<iostream>
#include<iomanip>//��ʽ�����
#include"trandom.h"
using namespace std;

int main()
{
	int a[54];
	for(int i=0;i<54;i++)
        a[i]=i;
	TRandom sRand;//�������
	for(int i=0;i<54;i++)
	{
        int temp;
        int n=sRand.Integer(0,53);
        temp=a[n];
        a[n]=a[i];
        a[i]=temp;
	}
	for(int i = 0; i < 54; i += 6)
	{
		cout <<setiosflags(ios::left)<<setw(5) << a[i] << setw(5) << a[i + 1] << setw(5) << a[i + 2];
		cout <<setw(5) << a[i + 3] <<setw(5) << a[i + 4] <<setw(5) << a[i + 5] << endl;
	}
	return 0;
}
