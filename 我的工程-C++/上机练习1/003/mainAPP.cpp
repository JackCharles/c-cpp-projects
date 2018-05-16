#include<iostream>
#include"a.h"
#include"b.h"
using namespace std;
int main(int argc, char * argv[])
{
	A aA;
    B bB(aA);
	if(argc > 1)
	{
		aA.Display(argv[1]);
	}
	else
	{
		aA.Display();
	}

	cout << sizeof(A) << endl;///结果输出1，A类本身不占空间，编译器至少分配1字节

	bB.Func();

	return 0;
}
