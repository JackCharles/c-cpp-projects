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
Cuboid V[3];///����3�����������
int main()
{
	for(int i = 0; i < 3; i++)
	{
		V[i].Input_data(i);
		V[i].Calculate_volume(i);
	}
	return 0;
}

void Cuboid::Input_data(int i)//�����Ա�������ڶ����Ա����ʱǧ��Ҫ���ⲿ���󣨸����͵ı��������Ϲ�ϵ����ֻ�Ƕ��ڲ������Ĳ���
{
	cout << "�������" << i + 1 << "��������ĳ����!" << endl;
	cin >> length;
	cin >> width;
	cin >> height;
}

void Cuboid::Calculate_volume(int i)//�����Ա����������и����͵Ķ�����������ڶ������ʱ�ڿ��������������
{
	cout << "��" << i + 1 << "�������������:" << height*length*width << endl;
}
