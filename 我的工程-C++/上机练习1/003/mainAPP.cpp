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

	cout << sizeof(A) << endl;///������1��A�౾��ռ�ռ䣬���������ٷ���1�ֽ�

	bB.Func();

	return 0;
}
