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
	cout << a << b << m1 << endl; //输出344正常传值

	int m2 = max22(a, b);
	cout << a << b << m2 << endl; //输出344正常引用

	max22(a, b) = 5;////int &引用型返回，返回[变量]b；相当于b=5；
	m2 = max22(a, b);////相当于m2=b
	cout << a << b << m2 << endl; //输出355

	//max23(a, b) = 6;               //错误,const int&是返回一个常值引用变量，他是变量但不能通过const限定的变量修改

	int m3 = max23(a, b);
	cout << a << b << m3 << endl; //输出355，b的值在第三个函数已修改

	//max24(a, b) = 7;               //错误，错误同上

	int m4 = max24(a, b);
	cout << a << b << m4 << endl; //输出355，b的值在第三个函数已修改

	return 0;
}



