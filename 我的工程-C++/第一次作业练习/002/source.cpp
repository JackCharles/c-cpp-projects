#include <iostream>
using namespace std;

enum WeekDay///ʵ�ʴ��������
{
	MON = 1,
	TUE,
	WED,
	THU,
	FIR,
	SAT,
	SUN = 0
};

const char * Names[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
void Show(WeekDay day)
{
	cout << "The Day is " << Names[day] << endl;
}
int main()
{
	Show(MON);
	Show(TUE);
	Show(SUN);
	return 0;
}
