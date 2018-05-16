#include<iostream>
#include"random.h"
using namespace std;

class Dice
{
	public:
		int Cast();//随机掷一次返回的点数
		void Other(int);//其他面点数
		TRandom random;//TRandom对象random，产生随机数
	private:
		int a, b, c; //骰子互相垂直的三个面
};

int main()
{
	Dice dice1;
	int n = dice1.Cast();
	dice1.Other(n);
	int num, sum = 0;
	cout<<"请输入骰子数:";
	cin >> num;
	for(int i = 0; i < num; i++)
		sum += dice1.Cast();
	cout << "总点数是:" << sum << endl;
	return 0;
}

int Dice::Cast()
{
	a = random.Integer(1,6);
	cout << "当前掷的点数是:" << a << endl;
	return a;
}

void Dice::Other(int n)
{
	cout << "上面是:" << n << "  " << "下面是:" << 7 - n << endl;

	b = random.Integer(1,6);
	while(b == n || b == 7 - n)
	{
		b = random.Integer(1,6);
	}
	cout << "前面是:" << b << "  " << "后面是:" << 7 - b << endl;

	for(c = 1; c < 7; c++)
	{
		if(c != n && c != 7 - n && c != b && c != 7 - b)
			break;
	}
	cout << "左面是:" << c << "  " << "右面是:" << 7 - c << endl;
}
