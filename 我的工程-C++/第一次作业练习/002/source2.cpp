#include <iostream>
using namespace std;

class A
{
	public:
		enum WeekDay ///ʵ�ʴ��������
		{
			MON = 1,
			TUE,
			WED,
			THU,
			FIR,
			SAT,
			SUN = 0
		};
};
class B
{
	public:
		enum Planet
		{
			MOON,
			SUN
		};
};

const char * Names[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
void Show(int day)
{
	cout << "The Day is " << Names[day] << endl;
}
int main()
{
    A Day;///�����class���൱��struct��ʱ������Ҫ������󣨱����������в�����Ҫ������ʵ�ʶ��󣨱�����֮�ϣ���ͽṹ������ֻ��������һ�����Ӧ���е����ԺͲ�����������ʵ�ʽ��ж�������Ȳ�����������������пռ䣩
	Show(Day.FIR);
	Show(Day.TUE);
	Show(Day.SUN);
	return 0;
}
