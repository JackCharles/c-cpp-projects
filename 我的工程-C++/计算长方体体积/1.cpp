#include<iostream>
using namespace std;

class Cuboid
{
	public:
		void Input_data(int i);
		void Calculate_volume(int i);
	private:
		float length;
		float width;
		float height;

};
Cuboid V[3];///定义3个长方体对象
int main()
{
	for(int i = 0; i < 3; i++)
	{
		V[i].Input_data(i);
		V[i].Calculate_volume(i);
	}
	return 0;
}

void Cuboid::Input_data(int i)//定义成员函数，在定义成员函数时千万不要和外部对象（该类型的变量）扯上关系，这只是对内部函数的操作
{
	cout << "请输入第" << i + 1 << "个长方体的长宽高!" << endl;
	cin >> length;
	cin >> width;
	cin >> height;
}

void Cuboid::Calculate_volume(int i)//定义成员函数，如果有该类型的多个变量，则在定义对象时在考虑数组或多个变量
{
	cout << "第" << i + 1 << "个长方体体积是:" << height*length*width << endl;
}
