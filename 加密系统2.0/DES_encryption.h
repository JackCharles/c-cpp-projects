#ifndef DES_ENCRYPTION_H_INCLUDED
#define DES_ENCRYPTION_H_INCLUDED

#include <cstdio>
using namespace std;

typedef bool BIT;//��bool���ͼ�¼������

class Encryption
{
public:
    Encryption(char k[8],char iv[8]);
private:
    void ChangeCharToBit(char ASCII[8],BIT bit[64]);      //��ASCII��ת���ɶ�����
    void CreateChildKey();                                //����16������Կ
    void InitPerm(BIT text[64]);                          //��ʼ�û�(IP)64bit
    void InInitPerm(BIT text[64]);                        //���ʼ�û�64bit

    void E_Premutation(BIT text[32], BIT tText[48]);      //E����չ32bit->48bit
    void ExclusiveOR(BIT tText[48], int turn);            //���48bit&����
    void S_Premutation(BIT tText[48], BIT text[32]);      //S�д���48bit->32bit
    void P_Premutation(BIT text[32]);                     //P�û�32bit
    void OneTurnEncrypt(BIT text[64],int turn);           //�ֽṹ

public:
    void SetFilePointer(FILE*pf, FILE*cf);
    void DesEncrypt();   //DES�ܼ��ܹ���
    void DesDecrypt();    //����
    void GetDesKey(char key[]);

private:
    char key[8];              //������Կ
    BIT bitKey[64];            //������Կ��������ʽ
    BIT ChildKey[16][48];      //ÿһ������Կ
    char IV[8];
    FILE* pFile;                //�����ļ�
    FILE* cFile;                //�����ļ�
    int offset;
};

#endif // DES_ENCRYPTION_H_INCLUDED
