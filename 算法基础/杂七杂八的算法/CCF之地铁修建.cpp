#include <iostream>
using namespace std;

class A
{
public:
	virtual void a()
	{
		cout << "A" << endl;
	}
	virtual void b()
	{
		cout << "B" << endl;
	}
	virtual void c()
	{
		cout << "C" << endl;
	}

private:
	int q = 3;
	char s[50]="你好，世界";
};


int main()
{
	typedef void(*pfun)(void);//定义一个函数指针类型
	A a;
	cout << (char*)((int*)(&a) + 2) << endl;//访问权限失效
	pfun f = (pfun)(*((int*)*(int*)(&a)+1));
	/*
		(&a):取对象a的首地址，也就是vptr
		(int*)(&a):将这个地址转换为int*型，以便解指针
		*(int*)(&a):解指针，获取vtable的首地址
		(int*)*(int*)(&a):将vtable首地址转换成int*，以便解指针
		*(int*)*(int*)(&a):解指针,获取a函数地址
		(pfun)*(int*)*(int*)(&a):强制转型为函数指针
		(pfun)(*((int*)*(int*)(&a)+1)):在第二次解指针之前+1,转到下一个存b函数入口的地址
	*/
	(*f)();
	void(*aa[10])(void);
	for (int i = 0; i < 10; ++i)
	{
		aa[i] = f;
		aa[i]();
	}
	
	return 0;
}