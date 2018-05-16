#include <iostream>
using namespace std;

void replace(char *str)
{
	if(str==NULL)
		return;
	
	int spaceCount = 0;
	int i;
	for(i=0; str[i]!=0;i++)
		if(str[i]==' ')
			++ spaceCount;
	int p1 = i + spaceCount*2;
	int p2 = i;
	while(p2>-1)
	{
		if(str[p2]!=' ')
			str[p1--] = str[p2--];
		else
		{
			str[p1--] = '0';
			str[p1--] = '2';
			str[p1--] = '%';
			--p2;
		}
		
	}
	
}

int main()
{
	char a[20] = "we are happy!";//前提得有空闲内存O(n)
	replace(a);
	cout<<a;
	
	return 0;
}