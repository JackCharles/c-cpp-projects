#include <iostream>
#include "function.h"
using namespace std;


#define M_PI		3.14159265358979323846
int main() {
    const int MAXLEN = 30;
	const double PI_VALUE = M_PI;
	ContinueFraction * pi = new ContinueFraction(PI_VALUE, MAXLEN);
	cout.precision(16);

	cout<<"PI="<<PI_VALUE<<endl<<endl;
	long fz, fm;
	for(int i= 1; i<=8;i++) {
		pi->GetFzFm(fz, fm, i);
		cout << "前"<<i<<"项为";pi->Display(i);
		cout << "前"<<i<<"项对应分数为" << fz << "/" << fm << endl;
		cout << "前"<<i<<"项对应分数的值为" << (double(fz)) / fm  << endl;
		cout << "前"<<i<<"项对应分数与"<<PI_VALUE<<"的差为" << PI_VALUE - (double(fz)) / fm << endl << endl;
	}
	delete pi;

	cout << "....." << endl;
	return 0;
}
