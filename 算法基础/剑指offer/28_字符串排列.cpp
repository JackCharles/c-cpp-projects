#include <iostream>
#include <cstring>
using namespace std;


void PrintStr(char *str, int index)
{
	//index代表该确定第几个字符
	if (index == strlen(str))
		cout << str << endl;
	else
	{
		//首先确定第一个字母，所有字母都可以是第一个，因此和他后面的所有字符交换
		for (int i = index; str[i] != '\0'; i++)
		{
			//注意字符串中可能有重复字符，当遇到重复字符时应跳过交换
			//让index自身和自身交换一次是保证字符串本身是能够输出
			//否则如遇到aa这样的，就会跳出循环而无法输出
			if(i!=index && str[i]==str[index])
				continue;
			char t = str[i];
			str[i] = str[index];
			str[index] = t;
			//递归确定后半部分
			PrintStr(str, index + 1);
		}
	}
}

void Permutation(char *str)
{
	if (str == NULL)
		return;
	PrintStr(str, 0);
}


int main()
{
	char a[] = "abc";
	Permutation(a);
	return 0;
}