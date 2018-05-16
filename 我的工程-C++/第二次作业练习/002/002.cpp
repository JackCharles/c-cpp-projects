#include<iostream>
using namespace std;

int DownSum = 0;//ͳ���³�����

class Bus
{
	public:
        Bus(int maxCapacity);
		void Up(int num);
		void Down(int num);
		int GetIncome() const;
	private:
		const int capacity;
		int   passagers;
		int   income;
};

Bus::Bus(int maxCapacity): capacity(maxCapacity)
{
	passagers = 0;
}

void Bus::Up(int num)
{
	passagers += num;
	if(passagers >= 80)
		passagers = 80;
}

void Bus::Down(int num)
{
	if(num == 999)
		DownSum += passagers;
	else
	{
		passagers -= num;
		DownSum += num;
	}
}

int Bus::GetIncome() const
{
	cout << "������:" << DownSum * 2 << endl;
}


int main()
{
	Bus bus(80);

	bus.Up(40);//A(���)

	bus.Down(10);//B
	bus.Up(50);

	bus.Down(20);//C
	bus.Up(60);

	bus.Down(15);//D
	bus.Up(30);

	bus.Down(999);//E(�յ�)

	bus.GetIncome();//������
	return 0;
}
