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
		int Cast(Dice&); //掷一次
		void MoreCast(Dice&);//掷多次
		void Cast_X(Dice&, int);//沿X轴转i次
		void Cast_Y(Dice&, int);
		void Cast_Z(Dice&, int);
		void Refresh()//每一次旋转后刷新与其对应面的数据
		{
			back_ = 7 - front_;
			right_ = 7 - left_;
			below_ = 7 - above_;
		}
};

int Dice::Cast(Dice& dice)
{
	TRandom sRand;
	switch(sRand.Integer() % 6)//xyz的旋转顺序不同结果不同，共有6中情况，每种情况都是随即出现的
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

void Dice::Cast_Y(Dice&dice, int i)        //Dice& 是返回值类型 Dice:: 是作用域 Cast_X函数名
{
	if(i == 1)
	{
		dice.front_ = dice.above_;//注意此处旋转后赋值顺序，将要把自己的值给别的变量的变量要最后赋值，防止覆盖
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
	cout << endl << "请输入要投掷的次数:";
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		temp = Cast(dice);
		sum += temp;
		cout << "第" << i + 1 << "次掷的点数为:" << temp << endl;
	}
	cout << "总点数为:" << sum << endl;
}
int main()
{
	Dice dice;
	cout << "当前掷的点数是:" << dice.Cast(dice) << endl << endl;
	cout << "上面是:" << dice.above_ << '\t' << "下面是:" << dice.below_ << endl;
	cout << "左面是:" << dice.left_ << '\t' << "右面是:" << dice.right_ << endl;
	cout << "前面是:" << dice.front_ << '\t' << "后面是:" << dice.back_ << endl;
	dice.MoreCast(dice);
	return 0;
}
