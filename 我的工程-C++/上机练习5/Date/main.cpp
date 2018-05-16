#include<iostream>
#include"date.h"
#include"date.cpp"
using namespace std;

int main()
{
    Date d1(2015, 1, 2);
    //输出 d1 = 2015-1-2
    cout << "d1 =" << d1.getYear() << "-" << d1.getMonth() << "-" << d1.getDay() << endl;

    Date d2 = d1.nextDate(2);
    //输出 d2 = 2015-1-4
    cout << "d2 =" << d2.getYear() << "-" << d2.getMonth() << "-" << d2.getDay() << endl;

    Date d3 = d1.nextDate(-2);
    //输出 d3 = 2014-12-31
    cout << "d3 =" << d3.getYear() << "-" << d3.getMonth() << "-" << d3.getDay() << endl;

    //输出 The Days From D3 To D2 = 4
    cout << "The Days From D3 To D2 = " << d3.daysTo(d2) << endl;
    return 0;
}
