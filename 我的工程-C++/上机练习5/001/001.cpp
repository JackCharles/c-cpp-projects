#include<iostream>

using namespace std;

class A
{
public:
    A(int num):data1(num){}
    ~A()
    {
        cout<<"Destory A"<<endl;
    }
    void f()const
    {
        cout<<"Excute A::g()"<<endl;
    }
protected:
    int data1;
};

class B:public A
{
public:
    B(int num1,int num2):A(num1),data2(num2){}
    ~B()
    {
        cout<<"Destory B"<<endl;
    }
    void f(int n) const
    {
        cout<<"Excute B::f(int)";
        cout<<"n="<<n;
        cout<<"data1="<<data1;
        cout<<"data2="<<data2<<endl;
    }
    void h()
    {
        cout<<"Excute B::h()"<<endl;
    }
private:
    int data2;
};


int main(int argc,char*argv[])
{
    B b(10,20);
    b.f(100);
    return 0;
}

