#include<iostream>
#include"random.h"
using namespace std;


class Crypter
{
public:
    int key;
    int len;
    TRandom rand;
    void input()
    {
        cout<<"Enter the key:";
        cin>>key;
    }
    void Coder(char data[],int len,int key);

    void output(char data[])
    {
        cout<<data;
    }

};
