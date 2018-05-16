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
    cout<<"请输入密钥(长整形秘钥):";
    cin>>key;
    cout<<"请输入待加密字符串："<<endl;
    cin>>data;
    cout<<"对应密文是:";
    Coder(data,strlen(data),sRand,key);
    cout<<"你要解密吗(Y/N)?"<<endl;
    char flag;
    cin>>flag;
    if(flag=='Y')
    {
        cout<<"解得明文是:";
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
        Cipher[j]=data[j] xor nRand[j];//异或
    Cipher[len]='\0';
    cout<<Cipher<<endl;
}
