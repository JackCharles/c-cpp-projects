#include<iostream>
using namespace std;


int max21(int a, int b)
{
	return a > b ? a : b;
}

int& max22(int& a, int& b)
{
	return a > b ? a : b;
}

const int& max23(int& a,  int& b)
{
	return a > b ? a : b;
}

const int& max24(const int& a, const int& b)
{
	return a > b ? a:b;
}

int main()
{
	int a = 3;
	int b = 4;
	int m1 = max21(a, b);
	cout << a << b << m1 << endl; //���344������ֵ

	int m2 = max22(a, b);
	cout << a << b << m2 << endl; //���344��������

	max22(a, b) = 5;////int &�����ͷ��أ�����[����]b���൱��b=5��
	m2 = max22(a, b);////�൱��m2=b
	cout << a << b << m2 << endl; //���355

	//max23(a, b) = 6;               //����,const int&�Ƿ���һ����ֵ���ñ��������Ǳ���������ͨ��const�޶��ı����޸�

	int m3 = max23(a, b);
	cout << a << b << m3 << endl; //���355��b��ֵ�ڵ������������޸�

	//max24(a, b) = 7;               //���󣬴���ͬ��

	int m4 = max24(a, b);
	cout << a << b << m4 << endl; //���355��b��ֵ�ڵ������������޸�

	return 0;
}



