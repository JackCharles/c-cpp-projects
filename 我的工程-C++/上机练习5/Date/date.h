#ifndef DATE_H
#define DATE_H


class Date
{
public:
    //���캯��
    Date(int y, int m, int d);
    //ȡ�õ�ǰ����days��ǰ������
    Date prevDate(int days = 1) const;
    //ȡ�õ�ǰ����days��������
    Date nextDate(int days = 1) const;
    //ȡ�õ�ǰ������ָ������֮���������
    int daysTo(const Date & date) const;
    int daysTo(int y,int m,int d) const;
    //�Ƚ��������ڣ�������������ػ�û�н��⣬�����Ѹ���ʵ��
    bool operator<(const Date & date) const;
    //�Ƚϵ�ǰ���ںͺʹ������ڵ��Ⱥ�
    int CheckYear() const;
    //��鵱ǰ����Ƿ�Ϊ����
    int getYear()  const { return year; }
    int getMonth() const { return month;}
    int getDay() const   { return day;}
    //��ȡ��ǰ����
private:
    int year;
    int month;
    int day;
};

#endif
