#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

//求10的n次方
int PowerBase10(int n)
{
	int result = 1;
	for(int i = 0; i<n;i++)
		result *= 10;
	return result;
}

//求一个字符串数字中的应包含1的个数(递归调用)
int NumOf1(const char* strN)
{
	//条件检查
	if(strN==NULL || *strN < '0' || *strN > '9' || *strN == '\0')
		return 0;
	
	int first = *strN - '0';//取数字的最高位
	unsigned int length = strlen(strN);
	if(length==1 && first==0)//如果数字只有一位且为0
		return 0;
	if(length==1 && first>0)//一位且大于0，包含且只包含1
		return 1;

	int numFirstDigit = 0;//最高位包含的1的数目
	if(first > 1)//如果第一位大于1则，最高位包含1xxxx...-19999...共10^(len-1)个1
		numFirstDigit = PowerBase10(length-1);
	else if(first==1)//如果第一位为1，如1xyz...，最高位共出现xyz+1次1，从1000...-1xyz...
		numFirstDigit = atoi(strN+1)+1;//将除最高位的子串转换为整数+1
	
	//最高位数量级中除第一位，其他几位中1出现的次数，根据排列组合求得
	int numOtherDigits = first * (length-1) * PowerBase10(length-2);
	//递归求除第一位，剩余数量级的1出现的次数
	int numRecursive = NumOf1(strN+1);
	
	return numFirstDigit + numOtherDigits + numRecursive;
	
}

int NumberOfBetween1AndN(int n)
{
	if(n <= 0)
		return 0;
	
	char strN[50];
	sprintf(strN, "%d", n);
	return NumOf1(strN);
}

int main()

{
	cout<<NumberOfBetween1AndN(1314);
	
	return 0;
}