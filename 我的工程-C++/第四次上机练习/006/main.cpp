//main.cpp
#include <iostream>
using namespace std;
#include "user.h"
#include"user.cpp"
int main()
{
    User a(100);
    a.display("a");

    cout<<"ִ�п�������:  User b(a); ��-----------------"<<endl;
    User b(a);
    a.display("a");
    b.display("b");

    cout<<"��ִ�п�������:  User c(b); ��-----------------"<<endl;
    User c(b);
    a.display("a");
    b.display("b");
    c.display("c");

    cout<<"�½�����d��e��  User d(500),e(999); ��-----------------"<<endl;
    User d(500),e(999);
    d.display("d");
    e.display("e");

    cout<<"ִ�и�ֵ��䣺  d = b; ��-----------------"<<endl;
    d = b;
    a.display("a");
    b.display("b");
    c.display("c");
    d.display("d");
    e.display("e");

    cout<<"��Copy On Writeִ���޸���䣺  c.setData(888);, ��-------"<<endl;
    c.setData(888);
    a.display("a");
    b.display("b");
    c.display("c");
    d.display("d");
    e.display("e");

    cout<<"��Copy On Writeִ���޸���䣺  e.setData(250);, ��-------"<<endl;
    e.setData(250);
    a.display("a");
    b.display("b");
    c.display("c");
    d.display("d");
    e.display("e");


    cout<<"-------------Over--------------"<<endl;
    return 0;
}

