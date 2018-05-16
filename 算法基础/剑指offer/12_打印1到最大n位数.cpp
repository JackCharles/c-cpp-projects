#include <iostream>
#include <string.h>
using namespace std;

void PrintNumber(char *number)
{
	bool begin = true;
	int len = strlen(number);
	
	for(int i=0;i<len;++i)
	{
		if(begin && number[i]!='0')
			begin = false;
		if(!begin)
			cout<<number[i];
	}
	cout<<endl;
}

void f(char *number, int len, int index)
{
	if(index == len-1)
	{
		PrintNumber(number);
		return;
	}
	
	for(int i=0; i<10; i++)
	{
		number[index+1] = i+'0';
		f(number, len, index+1);
	}
}

void PrintMaxNumber(int n)
{
	if(n<=0)
		return;
	char *number = new char[n+1];
	number[n] = 0;
	
	for(int i=0; i<10; i++)
	{
		number[0] = i+'0';
		f(number, n, 0);
	}
	
	delete[] number;
}

void PrintNumbers(int n)
{
	if(n<=0)
		return;
	char *num = new char[n];
	memset(num, 0, n);
	
	int carry = 0;
	while(1)
	{
		bool isEnd = false;//是否满位
		num[n-1] += 1;
		if(num[n-1]>=10)
		{
			carry = 1;
			num[n-1] = 0;
		}
		
		int i = n-2;
		while(carry)
		{
			num[i] += 1;
			if(num[i]>=10)
			{
				carry = 1;
				num[i] = 0;
				i--;
				if(i==-1)
					isEnd = true;
			}
			else
				carry = 0;
		}
		if(isEnd)
			break;
		
		int j;
		for(j=0; num[j]==0; j++);
		for(; j<n; j++)
			cout<<(char)(num[j]+48);
		cout<<endl;
	}
	
	delete[] num;
}

int main()
{
	
	//PrintMaxNumber(5);
	PrintNumbers(4);
	return 0;
}