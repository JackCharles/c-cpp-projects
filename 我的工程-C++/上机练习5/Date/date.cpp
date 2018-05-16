#include"date.h"

/*-------------------------------------------------------------------*/

Date::Date(int y,int m,int d)
{
    year=y;
    month=m;
    day=d;
}

/*-------------------------------------------------------------------*/

Date Date::prevDate(int days) const
{
    Date* date=new Date(year,month,day);//创建新的零时对象

    if(days<0)
        *date=nextDate(-days);
    else
    {
        int mon[12]= {31,date->CheckYear(),31,30,31,30,31,31,30,31,30,31};
        for(int i=0; i<days; i++)
        {
            date->day--;
            if(date->day==0)
            {
                date->month--;
                if(date->month==0)
                {
                    date->year--;
                    date->month=12;
                    mon[1]=date->CheckYear();
                }//if
                date->day=mon[date->month-1];

            }//if
        }//for
    }//if
    return *date;
}

/*-------------------------------------------------------------------*/

Date Date::nextDate(int days) const
{
    Date* date=new Date(year,month,day);//创建新的零时对象
    if(days<0)
        *date=prevDate(-days);
    else
    {
        int mon[12]= {31,date->CheckYear(),31,30,31,30,31,31,30,31,30,31};
        for(int i=0; i<days; i++)
        {
            date->day++;
            if(date->day>mon[date->month-1])//下一月
            {
                date->month++;
                if(date->month>12)//下一年
                {
                    date->year++;
                    date->month=1;
                    mon[1]=date->CheckYear();
                }
                date->day=1;

            }
        }
    }
    return *date;
}

/*-------------------------------------------------------------------*/

int Date::daysTo(const Date&date)const
{
    int count=0;
    Date*date1=NULL,*date2=NULL;
    if(*this<date)//调用"<"运算符重载
    {
        date1=new Date(year,month,day);
        date2=new Date(date.year,date.month,date.day);
    }
    else
    {
        date2=new Date(year,month,day);
        date1=new Date(date.year,date.month,date.day);
    }
    while(date1->day!=date2->day||date1->month!=date2->month||date1->year!=date2->year)
    {
        *date1=date1->nextDate(1);
        count++;
    }
    delete date1;
    delete date2;
    return count;
}

/*-------------------------------------------------------------------*/

int Date::daysTo(int y,int m,int d) const
{
    int count=0;
    Date*tDate=new Date(y,m,d);
    count=daysTo(*tDate);
    delete tDate;
    return count;
}

/*-------------------------------------------------------------------*/

bool Date::operator<(const Date & date) const
{
    if(year != date.year)
    {
        return year < date.year;
    }
    if(month != date.month)
    {
        return month < date.month;
    }
    return day < date.day;
}

/*-------------------------------------------------------------------*/

int Date::CheckYear()const
{
    if((year%4==0&&year%100!=0)||year%400==0)
        return 29;
    else
        return 28;
}
