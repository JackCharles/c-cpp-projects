#include<iostream>
#include"person.h"
using namespace std;


int main(int argv,char *argc[])
{
    Thief t1(500),t2(800),t3(300),t4(1000);
    //Walker w(100);
    Polices p1(0),p2(0),p3(0);
    PoliceOffice S(100);
    //t1.Steal(w);

    p1.Arrest(S,t2);
    p1.Arrest(S,t3);
    p2.Arrest(S,t4);
    //cout<<"С͵��ǮΪ:"<<t1.GetMoney()<<endl;
   // cout<<"���˵�ǮΪ:"<<w.GetMoney()<<endl;
    cout<<"S������:"<<S.GetRep()<<endl;
    cout<<"p1�Ľ���:"<<p1.GetMoney()<<endl;
    cout<<"p2�Ľ���:"<<p2.GetMoney()<<endl;
    cout<<"p3�Ľ���:"<<p3.GetMoney()<<endl;

    return 0;
}
