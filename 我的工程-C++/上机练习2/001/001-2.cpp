#include<iostream>
#include"random.h"
using namespace std;

void Coder(char data[],int len,  TRandom& rand, unsigned long key);

char Cipher[100];
int main()
{
    TRandom sRand;
    int key,len=0;
    char data[100];
    cout<<"��������Կ(��������Կ):";
    cin>>key;
    cout<<"������������ַ�����"<<endl;
    cin>>data;
    cout<<"��Ӧ������:";
    Coder(data,strlen(data),sRand,key);
    cout<<"��Ҫ������(Y/N)?"<<endl;
    char flag;
    cin>>flag;
    if(flag=='Y')
    {
        cout<<"���������:";
        Coder(Cipher,strlen(data),sRand,key);
    }
    return 0;
}

void Coder(char data[],int len,TRandom& rand,unsigned long key)
{
    rand.Seed(key);
    int nRand[len];
    for(int i=0; i<len; i++)
        nRand[i]=rand.Integer(1,len);
    for(int j=0; j<len; j++)
        Cipher[j]=data[j] xor nRand[j];//���
    Cipher[len]='\0';
    cout<<Cipher<<endl;
}
