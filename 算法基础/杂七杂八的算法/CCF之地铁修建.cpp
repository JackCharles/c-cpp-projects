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
	char s[50]="��ã�����";
};


int main()
{
	typedef void(*pfun)(void);//����һ������ָ������
	A a;
	cout << (char*)((int*)(&a) + 2) << endl;//����Ȩ��ʧЧ
	pfun f = (pfun)(*((int*)*(int*)(&a)+1));
	/*
		(&a):ȡ����a���׵�ַ��Ҳ����vptr
		(int*)(&a):�������ַת��Ϊint*�ͣ��Ա��ָ��
		*(int*)(&a):��ָ�룬��ȡvtable���׵�ַ
		(int*)*(int*)(&a):��vtable�׵�ַת����int*���Ա��ָ��
		*(int*)*(int*)(&a):��ָ��,��ȡa������ַ
		(pfun)*(int*)*(int*)(&a):ǿ��ת��Ϊ����ָ��
		(pfun)(*((int*)*(int*)(&a)+1)):�ڵڶ��ν�ָ��֮ǰ+1,ת����һ����b������ڵĵ�ַ
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