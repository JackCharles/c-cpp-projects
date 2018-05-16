#include<iostream>
#include<NTL/ZZ.h>
#include<ctime>
#include<string>
#include<cstdlib>
#include<fstream>
using namespace std;
using namespace NTL;

void RSA_Encrypt(char plainText[8],int Len, char KeyFile[], char Target[])
{
    ZZ n,e;
    ZZ plain[Len],cipher;
    for(int i=0;i<Len;i++)
    {
        plain[i]=plainText[i];
    }

   fstream key(KeyFile,ios::in);
   fstream tar(Target,ios::out|ios::app|ios::binary);
   key>>e;
   key>>n;
   for(int i=0;i<Len;i++)
   {
        cipher=PowerMod(plain[i],e,n);
        tar<<cipher<<endl;
   }

   key.close();
   tar.close();

}



void RSA_Decrypt(char cipherFile[],int cipherLen,char keyFile[],char plainText[])
{
    ZZ cipher,plain;
    ZZ n,d;

    fstream key(keyFile,ios::in);
    fstream cFile(cipherFile,ios::in|ios::binary);

    key>>d;
    key>>n;

    for(int i=0;i<cipherLen;i++)
    {
        cFile>>cipher;
        plain=PowerMod(cipher,d,n);
        int temp;
        conv(temp,plain);
        plainText[i]=(char)temp;
    }

    key.close();
    cFile.close();
}
