#include<iostream>
using namespace std;

class City
{
public:
	City(int index): customIndex(index) {}
	int Spend(int days) const//成员函数参数表中默认隐藏有this指针，指向当前对象，这里const其
	{
		//实是对this指针的修饰，表示该函数体内不能对当前对象有任何修改
		return days * customIndex;
	}
private:
	int  customIndex;  //消费指数

};

int main()
{
	int cost_way1 = 0;
	int cost_way2 = 0;
	const City A(120), B(80), C(70), D(100); //普通对象可以调用常成员函数（普通函数优先），常对象只能调用常成员函数
	cost_way1 = A.Spend(7) + B.Spend(6) + C.Spend(5) + D.Spend(4);
	cost_way2 = A.Spend(4) + B.Spend(5) + C.Spend(6) + D.Spend(7);
	cout << "线路一花费:" << cost_way1 << "元。" << endl;
	cout << "线路二花费:" << cost_way2 << "元。" << endl;
	return 0;
}
