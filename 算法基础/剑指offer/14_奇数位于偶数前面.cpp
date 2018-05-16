#include <iostream>
using namespace std;

/*奇数---偶数*/

//规则函数
bool isOddNum(int num)
{
	return (num & 1) == 0;
}

void Recoder(int *pData, int len, bool(*func)(int))
{
	if(pData==NULL||len==0)
		return;
	int l = 0, r = len-1;
	while(l<r)
	{
		while(l<r && !func(pData[l]))//从前向后查找第一个不满足前半部分条件的数
			l++;
		while(l<r && func(pData[r]))//从后向前找第一个不满足后半部分条件（满足前半部分条件）的数
			r--;
		if(l<r)//找到了交换
		{
			int t = pData[l];
			pData[l] = pData[r];
			pData[r] = t;
		}
	}
}



int main()
{
	int a[5] = {1,2,3,4,5};
	Recoder(a, 5, isOddNum);
	
	for(int i=0;i<5;i++)
	{
		cout<<a[i]<<"\t";
	}
	
	return  0;
}