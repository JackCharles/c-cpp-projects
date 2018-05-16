//main.cpp
#include <iostream>
using namespace std;
#include "user.h"
#include"user.cpp"
int main()
{
    User a(100);
    a.display("a");

    cout<<"执行拷贝构造:  User b(a); 后-----------------"<<endl;
    User b(a);
    a.display("a");
    b.display("b");

    cout<<"又执行拷贝构造:  User c(b); 后-----------------"<<endl;
    User c(b);
    a.display("a");
    b.display("b");
    c.display("c");

    cout<<"新建对象d和e：  User d(500),e(999); 后-----------------"<<endl;
    User d(500),e(999);
    d.display("d");
    e.display("e");

    cout<<"执行赋值语句：  d = b; 后-----------------"<<endl;
    d = b;
    a.display("a");
    b.display("b");
    c.display("c");
    d.display("d");
    e.display("e");

    cout<<"按Copy On Write执行修改语句：  c.setData(888);, 后-------"<<endl;
    c.setData(888);
    a.display("a");
    b.display("b");
    c.display("c");
    d.display("d");
    e.display("e");

    cout<<"按Copy On Write执行修改语句：  e.setData(250);, 后-------"<<endl;
    e.setData(250);
    a.display("a");
    b.display("b");
    c.display("c");
    d.display("d");
    e.display("e");


    cout<<"-------------Over--------------"<<endl;
    return 0;
}

