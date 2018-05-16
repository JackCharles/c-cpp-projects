#include<iostream>
using namespace std;


  class A
  {
  public:
       A(int num):data(num) {}
       void AFuncs() {cout<<"This is A \'s public function!"<<endl;}
  protected:
       int data;
  };
  class B:public A
  {
  public:
       B(int num,int num2):value(num),A(num2){}
       void BFuncs() {cout<<"This is B \'s public function!"<<endl;}
  protected:
       int value;
  };

  class C:protected B
  {
  public:
       C(int num1,int num2,int y);
       void MyFuncs()
            {
              BFuncs();
              cout<<"This function call B::BFuncs() !"<<endl;
            }
  private:
       int yyy;
  };

C::C(int num1,int num2,int y):B(num1,num2),yyy(y){}
