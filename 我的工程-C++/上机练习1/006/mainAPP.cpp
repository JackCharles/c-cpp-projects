#include<iostream>
#include"random.h"
using namespace std;

class Dice
{
	public:
		int Cast();//�����һ�η��صĵ���
		void Other(int);//���������
		TRandom random;//TRandom����random�����������
	private:
		int a, b, c; //���ӻ��ഹֱ��������
};

int main()
{
	Dice dice1;
	int n = dice1.Cast();
	dice1.Other(n);
	int num, sum = 0;
	cout<<"������������:";
	cin >> num;
	for(int i = 0; i < num; i++)
		sum += dice1.Cast();
	cout << "�ܵ�����:" << sum << endl;
	return 0;
}

int Dice::Cast()
{
	a = random.Integer(1,6);
	cout << "��ǰ���ĵ�����:" << a << endl;
	return a;
}

void Dice::Other(int n)
{
	cout << "������:" << n << "  " << "������:" << 7 - n << endl;

	b = random.Integer(1,6);
	while(b == n || b == 7 - n)
	{
		b = random.Integer(1,6);
	}
	cout << "ǰ����:" << b << "  " << "������:" << 7 - b << endl;

	for(c = 1; c < 7; c++)
	{
		if(c != n && c != 7 - n && c != b && c != 7 - b)
			break;
	}
	cout << "������:" << c << "  " << "������:" << 7 - c << endl;
}
