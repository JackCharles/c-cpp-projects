#ifndef DATE_H
#define DATE_H


class Date
{
public:
    //构造函数
    Date(int y, int m, int d);
    //取得当前日期days天前的日期
    Date prevDate(int days = 1) const;
    //取得当前日期days天后的日期
    Date nextDate(int days = 1) const;
    //取得当前日期与指定日期之间的天数差
    int daysTo(const Date & date) const;
    int daysTo(int y,int m,int d) const;
    //比较两个日期，由于运算符重载还没有讲解，这里已给出实现
    bool operator<(const Date & date) const;
    //比较当前日期和和传入日期的先后
    int CheckYear() const;
    //检查当前年份是否为闰年
    int getYear()  const { return year; }
    int getMonth() const { return month;}
    int getDay() const   { return day;}
    //获取当前日期
private:
    int year;
    int month;
    int day;
};

#endif
