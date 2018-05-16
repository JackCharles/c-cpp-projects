#include<iostream>
#include"random.h"
using namespace std;

class Dice
{
	public:
		int front_ = 3;
		int above_ = 1;
		int left_ = 2;
		int back_ = 7 - front_;
		int right_ = 7 - left_;
		int below_ = 7 - above_;
		int Cast(Dice&); //��һ��
		void MoreCast(Dice&);//�����
		void Cast_X(Dice&, int);//��X��תi��
		void Cast_Y(Dice&, int);
		void Cast_Z(Dice&, int);
		void Refresh()//ÿһ����ת��ˢ�������Ӧ�������
		{
			back_ = 7 - front_;
			right_ = 7 - left_;
			below_ = 7 - above_;
		}
};

int Dice::Cast(Dice& dice)
{
	TRandom sRand;
	switch(sRand.Integer() % 6)//xyz����ת˳��ͬ�����ͬ������6�������ÿ����������漴���ֵ�
	{
		case 0:
		{
			Cast_X(dice, sRand.Integer() % 4);
			Cast_Y(dice, sRand.Integer() % 4);
			Cast_Z(dice, sRand.Integer() % 4);

		}
		case 1:
		{
			Cast_X(dice, sRand.Integer() % 4);
			Cast_Z(dice, sRand.Integer() % 4);
			Cast_Y(dice, sRand.Integer() % 4);

		}
		case 2:
		{
			Cast_Y(dice, sRand.Integer() % 4);
			Cast_Z(dice, sRand.Integer() % 4);
			Cast_X(dice, sRand.Integer() % 4);

		}
		case 3:
		{
			Cast_Y(dice, sRand.Integer() % 4);
			Cast_X(dice, sRand.Integer() % 4);
			Cast_Z(dice, sRand.Integer() % 4);

		}
		case 4:
		{
			Cast_Z(dice, sRand.Integer() % 4);
			Cast_Y(dice, sRand.Integer() % 4);
			Cast_X(dice, sRand.Integer() % 4);

		}
		case 5:
		{
			Cast_Z(dice, sRand.Integer() % 4);
			Cast_X(dice, sRand.Integer() % 4);
			Cast_Y(dice, sRand.Integer() % 4);
		}
	}
	return dice.above_;
}

void Dice::Cast_Y(Dice&dice, int i)        //Dice& �Ƿ���ֵ���� Dice:: �������� Cast_X������
{
	if(i == 1)
	{
		dice.front_ = dice.above_;//ע��˴���ת��ֵ˳�򣬽�Ҫ���Լ���ֵ����ı����ı���Ҫ���ֵ����ֹ����
		dice.above_ = dice.back_;
	}
	else if(i == 2)
	{
		dice.front_ = dice.back_;
		dice.above_ = dice.below_;
	}
	else if(i == 3)
	{
		dice.above_ = dice.front_;
		dice.front_ = dice.below_;
	}
	dice.Refresh();
}

void Dice::Cast_X(Dice&dice, int i)
{
	if(i == 1)
	{
		dice.left_ = dice.above_;
		dice.above_ = dice.right_;
	}
	else if(i == 2)
	{
		dice.left_ = dice.right_;
		dice.above_ = dice.below_;
	}
	else if(i == 3)
	{
		dice.above_ = dice.left_;
		dice.left_ = dice.below_;
	}
	dice.Refresh();
}

void Dice::Cast_Z(Dice&dice, int i)
{
	if(i == 1)
	{
		dice.front_ = dice.left_;
		dice.left_ = dice.back_;
	}
	else if(i == 2)
	{
		dice.front_ = dice.back_;
		dice.left_ = dice.right_;
	}
	else if(i == 3)
	{
		dice.left_ = dice.front_;
		dice.front_ = dice.right_;
	}
	dice.Refresh();
}

void Dice::MoreCast(Dice&dice)
{
	int n;
	int temp;
	int sum = 0;
	cout << endl << "������ҪͶ���Ĵ���:";
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		temp = Cast(dice);
		sum += temp;
		cout << "��" << i + 1 << "�����ĵ���Ϊ:" << temp << endl;
	}
	cout << "�ܵ���Ϊ:" << sum << endl;
}
int main()
{
	Dice dice;
	cout << "��ǰ���ĵ�����:" << dice.Cast(dice) << endl << endl;
	cout << "������:" << dice.above_ << '\t' << "������:" << dice.below_ << endl;
	cout << "������:" << dice.left_ << '\t' << "������:" << dice.right_ << endl;
	cout << "ǰ����:" << dice.front_ << '\t' << "������:" << dice.back_ << endl;
	dice.MoreCast(dice);
	return 0;
}
