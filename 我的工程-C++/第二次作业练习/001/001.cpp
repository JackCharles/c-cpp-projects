#include<iostream>
using namespace std;

class City
{
public:
	City(int index): customIndex(index) {}
	int Spend(int days) const//��Ա������������Ĭ��������thisָ�룬ָ��ǰ��������const��
	{
		//ʵ�Ƕ�thisָ������Σ���ʾ�ú������ڲ��ܶԵ�ǰ�������κ��޸�
		return days * customIndex;
	}
private:
	int  customIndex;  //����ָ��

};

int main()
{
	int cost_way1 = 0;
	int cost_way2 = 0;
	const City A(120), B(80), C(70), D(100); //��ͨ������Ե��ó���Ա��������ͨ�������ȣ���������ֻ�ܵ��ó���Ա����
	cost_way1 = A.Spend(7) + B.Spend(6) + C.Spend(5) + D.Spend(4);
	cost_way2 = A.Spend(4) + B.Spend(5) + C.Spend(6) + D.Spend(7);
	cout << "��·һ����:" << cost_way1 << "Ԫ��" << endl;
	cout << "��·������:" << cost_way2 << "Ԫ��" << endl;
	return 0;
}
