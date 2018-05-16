#include <iostream>
#include <cstdio>
#include <cstring>
#include<ctime>
#include "DES_encryption.h"
#include "DES_Data.h"
using namespace std;

Encryption::Encryption(char *k,char *iv)
{
    for(int i = 0; i < 8; ++i)
    {
        key[i] = k[i]; //Ĭ��Ϊ9,8,7,6,5,4,3,2
        IV[i] = iv[i];
    }
}

/*****************���캯��***********************/

void Encryption::SetFilePointer(FILE*pf,FILE*cf)
{
    pFile=pf;
    cFile=cf;
}


void Encryption::ChangeCharToBit(char ASCII[], BIT bit[]) //����ת��ASCII->BIT
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 7; j > -1; j--)
        {
            bit[i * 8 + (7 - j)] = ((ASCII[i] >> j) & 1);//��ÿһλASCIIת����8��������λ(��λ����1��Ϊ����)
        }
    }
}

void Encryption::CreateChildKey()//����16������Կ
{
    BIT tKey[56];
    for(int i = 0; i < 56; i++)//��64λ��Կͨ��PC1�û����Ϊ56λ
    {
        tKey[i] = bitKey[PC1[i] - 1];
    }

    for(int i = 0; i < 16; i++)//����16������Կ
    {
        for(int j = 0; j < LSK[i]; j++) //ѭ������
        {
            BIT t1 = tKey[0], t2 = tKey[28];
            for(int k = 0; k < 27; k++)
            {
                tKey[k] = tKey[k + 1];
                tKey[k + 28] = tKey[k + 29];
            }
            tKey[27] = t1;
            tKey[55] = t2;
        }

        for(int j = 0; j < 48; j++) //PC2�û���Ϊ48λ
        {
            ChildKey[i][j] = tKey[PC2[j] - 1];
        }

    }
}

void Encryption::InitPerm(BIT text[])//��ʼIP�û�64bit
{
    BIT temp[64];
    for(int i = 0; i < 64; i++)
    {
        temp[i] = text[IP[i] - 1];
    }
    for(int i = 0; i < 64; i++)
        text[i] = temp[i];
}

void Encryption::InInitPerm(BIT text[])//���ʼ�û�64bit
{
    BIT temp[64];
    for(int i = 0; i < 64; i++)
    {
        temp[i] = text[FP[i] - 1];
    }
    for(int i = 0; i < 64; i++)
        text[i] = temp[i];
}

void Encryption::E_Premutation(BIT text[], BIT tText[]) //E����չ32->48
{
    for(int i = 0; i < 48; i++)
    {
        tText[i] = text[E[i] - 1];
    }
}

void Encryption::ExclusiveOR(BIT tText[], int turn) //���
{
    for(int i = 0; i < 48; i++)
    {
        tText[i] = tText[i] ^ ChildKey[turn][i];
    }
}

void Encryption::S_Premutation(BIT tText[], BIT text[]) //S��ѡ��48->32
{
    BIT s_in[6]; //s��6->4
    for(int i = 0; i < 8; i++) //��Ϊ8��
    {
        for(int j = 0; j < 6; j++)
        {
            s_in[j] = tText[i * 6 + j];
        }
        int raw = s_in[0] * 2 + s_in[5]; //ѡ����
        int col = s_in[1] * 8 + s_in[2] * 4 + s_in[3] * 2 + s_in[4]; //ѡ����
        int result = S[i][raw][col];

        for(int j = 0; j < 4; j++)
        {
            text[i * 4 + j] = ((result >> (3 - j)) & 1);
        }

    }
}

void Encryption::P_Premutation(BIT text[])//p�û�32bit
{
    BIT temp[32];
    for(int i = 0; i < 32; i++)
    {
        temp[i] = text[P[i] - 1];
    }
    for(int i = 0; i < 64; i++)
        text[i] = temp[i];
}

void Encryption::OneTurnEncrypt(BIT text[], int turn) //�ֽṹ64bit
{
    BIT LText[32], RText[32];
    for(int i = 0; i < 32; i++)
    {
        LText[i] = text[i];
        RText[i] = text[32 + i];
    }

    for(int i = 0; i < 32; i++)
    {
        text[i] = RText[i];
    }

    BIT tText[48] = {0};
    E_Premutation(RText, tText);
    ExclusiveOR(tText, turn);
    S_Premutation(tText, RText);
    P_Premutation(RText);

    for(int i = 0; i < 32; i++)
    {
        text[i + 32] = LText[i] ^ RText[i];
    }
}


void Encryption::DesEncrypt()
{
    BIT cipherPre[64];
    ChangeCharToBit(key, bitKey);
    ChangeCharToBit(IV, cipherPre);
    CreateChildKey();

    int bit[8] = {128, 64, 32, 16, 8, 4, 2, 1};   //������תʮ���Ƹ�������
    int fileLen, offset;                          //�ļ�����(��8�ֽ�Ϊһ��)�Ͳ�λ
    char tempText[8] = {0};                       //��ʱ�ַ���
    BIT text[64] = {0};                           //ÿ��64λ

    fseek(pFile, 0, SEEK_END);
    fileLen = ftell(pFile) / 8 ;                //�����ļ��Ŀ���
    if(ftell(pFile) % 8)
        fileLen += 1;
    offset = fileLen * 8 - ftell(pFile);        //���㲹λ����
    fwrite(&fileLen, sizeof(int), 1, cFile);   //���ļ�����д��Ŀ���ļ�
    fwrite(&offset, sizeof(int), 1, cFile);
    fseek(pFile, 0, SEEK_SET);                  //���ļ�ָ�븴ԭ

    while(fread(tempText, sizeof(char), 8, pFile))//fread����ֵ��������ȡ�ĸ���,����ȡ����Ϊ0�ǽ���,
    {
        //��Ч����feof��ɶ��һ�ε��鷳
        for(int i = 0; i < 8; i++)
            for(int j = 7; j > -1; j--)
            {
                text[i * 8 + (7 - j)] = ((tempText[i] >> j) & 1)^cipherPre[i * 8 + (7 - j)]; //��ÿһλת����8��������λ
            }

        InitPerm(text);//IP

        for(int i = 0; i < 16; i++)//16��
        {
            OneTurnEncrypt(text, i);
        }

        for(int i = 0; i < 32; i++)
        {
            BIT temp = text[i];
            text[i] = text[i + 32];
            text[i + 32] = temp;
        }

        InInitPerm(text);//IP���û�

        for(int i = 0; i < 8; i++)//������ת10����
        {
            tempText[i] = 0;
            for(int j = 0; j < 8; j++)
            {
                cipherPre[i * 8 + j]=text[i * 8 + j];
                tempText[i] += text[i * 8 + j] * bit[j];
            }
        }

        fwrite(tempText, sizeof(char), 8, cFile);
        memset(tempText, 0, 8);//����,�����8λ��0
    }
}


void Encryption::DesDecrypt()
{
    BIT cipherPre[64],cipherPreTemp[64];
    ChangeCharToBit(IV,cipherPre);
    ChangeCharToBit(key, bitKey);
    CreateChildKey();

    int bit[8] = {128, 64, 32, 16, 8, 4, 2, 1}; //������תʮ���Ƹ�������
    int fileLen, offset, time = 0;              //time��ȡ����
    char tempText[8] = {0};                     //��ʱ�ַ���
    BIT text[64] = {0};                          //ÿ��64λ

    fread(&fileLen, sizeof(int), 1, cFile);     //��ȡ�ļ�����
    fread(&offset, sizeof(int), 1, cFile);

    while(fread(tempText, sizeof(char), 8, cFile))
    {
        time++;
        for(int i = 0; i < 8; i++)
        {
            for(int j = 7; j > -1; j--)
            {
                cipherPreTemp[i * 8 + (7 - j)]=cipherPre[i * 8 + (7 - j)];
                text[i * 8 + (7 - j)] = ((tempText[i] >> j) & 1);//��ÿһλת����8��������λ
                cipherPre[i * 8 + (7 - j)]=text[i * 8 + (7 - j)];
            }
        }

        InitPerm(text);//IP

        for(int i = 0; i < 16; i++)//16��
        {
            OneTurnEncrypt(text, 15 - i);
        }

        for(int i = 0; i < 32; i++)//���ҽ���
        {
            BIT temp = text[i];
            text[i] = text[i + 32];
            text[i + 32] = temp;
        }

        InInitPerm(text);//IP���û�

        for(int i = 0; i < 8; i++)//������ת10����
        {
            tempText[i] = 0;
            for(int j = 0; j < 8; j++)
            {
                text[i * 8 + j]^=cipherPreTemp[i * 8 + j];
                tempText[i] += text[i * 8 + j] * bit[j];
            }
        }
        if(time == fileLen) //���һ�ִ���λ
            fwrite(tempText, sizeof(char), 8 - offset, pFile);
        else
            fwrite(tempText, sizeof(char), 8, pFile);

        memset(tempText, 0, 8);
    }
}


void Encryption::GetDesKey(char s_key[])
{
    for(int i = 0; i < 8; i++)
        s_key[i] = key[i];
}
