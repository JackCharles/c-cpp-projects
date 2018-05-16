#include <iostream>
using namespace std;

class A
{
	public:
		enum WeekDay ///实际存的是整数
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
    A Day;///如果用class（相当于struct）时，必须要申请对象（变量），所有操作都要建立在实际对象（变量）之上，类和结构体类型只是声明这一类对象应具有的属性和操作，但不能实际进行对类输出等操作，必须申请对象（有空间）
	Show(Day.FIR);
	Show(Day.TUE);
	Show(Day.SUN);
	return 0;
}
