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
        key[i] = k[i]; //默认为9,8,7,6,5,4,3,2
        IV[i] = iv[i];
    }
}

/*****************构造函数***********************/

void Encryption::SetFilePointer(FILE*pf,FILE*cf)
{
    pFile=pf;
    cFile=cf;
}


void Encryption::ChangeCharToBit(char ASCII[], BIT bit[]) //数据转换ASCII->BIT
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 7; j > -1; j--)
        {
            bit[i * 8 + (7 - j)] = ((ASCII[i] >> j) & 1);//对每一位ASCII转换成8个二进制位(移位在用1作为掩码)
        }
    }
}

void Encryption::CreateChildKey()//产生16个子秘钥
{
    BIT tKey[56];
    for(int i = 0; i < 56; i++)//将64位秘钥通过PC1置换后变为56位
    {
        tKey[i] = bitKey[PC1[i] - 1];
    }

    for(int i = 0; i < 16; i++)//产生16组子秘钥
    {
        for(int j = 0; j < LSK[i]; j++) //循环左移
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

        for(int j = 0; j < 48; j++) //PC2置换变为48位
        {
            ChildKey[i][j] = tKey[PC2[j] - 1];
        }

    }
}

void Encryption::InitPerm(BIT text[])//初始IP置换64bit
{
    BIT temp[64];
    for(int i = 0; i < 64; i++)
    {
        temp[i] = text[IP[i] - 1];
    }
    for(int i = 0; i < 64; i++)
        text[i] = temp[i];
}

void Encryption::InInitPerm(BIT text[])//逆初始置换64bit
{
    BIT temp[64];
    for(int i = 0; i < 64; i++)
    {
        temp[i] = text[FP[i] - 1];
    }
    for(int i = 0; i < 64; i++)
        text[i] = temp[i];
}

void Encryption::E_Premutation(BIT text[], BIT tText[]) //E盒扩展32->48
{
    for(int i = 0; i < 48; i++)
    {
        tText[i] = text[E[i] - 1];
    }
}

void Encryption::ExclusiveOR(BIT tText[], int turn) //异或
{
    for(int i = 0; i < 48; i++)
    {
        tText[i] = tText[i] ^ ChildKey[turn][i];
    }
}

void Encryption::S_Premutation(BIT tText[], BIT text[]) //S盒选择48->32
{
    BIT s_in[6]; //s盒6->4
    for(int i = 0; i < 8; i++) //分为8组
    {
        for(int j = 0; j < 6; j++)
        {
            s_in[j] = tText[i * 6 + j];
        }
        int raw = s_in[0] * 2 + s_in[5]; //选择行
        int col = s_in[1] * 8 + s_in[2] * 4 + s_in[3] * 2 + s_in[4]; //选择列
        int result = S[i][raw][col];

        for(int j = 0; j < 4; j++)
        {
            text[i * 4 + j] = ((result >> (3 - j)) & 1);
        }

    }
}

void Encryption::P_Premutation(BIT text[])//p置换32bit
{
    BIT temp[32];
    for(int i = 0; i < 32; i++)
    {
        temp[i] = text[P[i] - 1];
    }
    for(int i = 0; i < 64; i++)
        text[i] = temp[i];
}

void Encryption::OneTurnEncrypt(BIT text[], int turn) //轮结构64bit
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

    int bit[8] = {128, 64, 32, 16, 8, 4, 2, 1};   //二进制转十进制辅助数组
    int fileLen, offset;                          //文件长度(以8字节为一块)和补位
    char tempText[8] = {0};                       //临时字符串
    BIT text[64] = {0};                           //每块64位

    fseek(pFile, 0, SEEK_END);
    fileLen = ftell(pFile) / 8 ;                //计算文件的块数
    if(ftell(pFile) % 8)
        fileLen += 1;
    offset = fileLen * 8 - ftell(pFile);        //计算补位长度
    fwrite(&fileLen, sizeof(int), 1, cFile);   //将文件块数写入目的文件
    fwrite(&offset, sizeof(int), 1, cFile);
    fseek(pFile, 0, SEEK_SET);                  //将文件指针复原

    while(fread(tempText, sizeof(char), 8, pFile))//fread返回值是真正读取的个数,当读取个数为0是结束,
    {
        //有效避免feof造成多读一次的麻烦
        for(int i = 0; i < 8; i++)
            for(int j = 7; j > -1; j--)
            {
                text[i * 8 + (7 - j)] = ((tempText[i] >> j) & 1)^cipherPre[i * 8 + (7 - j)]; //对每一位转换成8个二进制位
            }

        InitPerm(text);//IP

        for(int i = 0; i < 16; i++)//16轮
        {
            OneTurnEncrypt(text, i);
        }

        for(int i = 0; i < 32; i++)
        {
            BIT temp = text[i];
            text[i] = text[i + 32];
            text[i + 32] = temp;
        }

        InInitPerm(text);//IP逆置换

        for(int i = 0; i < 8; i++)//二进制转10进制
        {
            tempText[i] = 0;
            for(int j = 0; j < 8; j++)
            {
                cipherPre[i * 8 + j]=text[i * 8 + j];
                tempText[i] += text[i * 8 + j] * bit[j];
            }
        }

        fwrite(tempText, sizeof(char), 8, cFile);
        memset(tempText, 0, 8);//重置,最后不满8位补0
    }
}


void Encryption::DesDecrypt()
{
    BIT cipherPre[64],cipherPreTemp[64];
    ChangeCharToBit(IV,cipherPre);
    ChangeCharToBit(key, bitKey);
    CreateChildKey();

    int bit[8] = {128, 64, 32, 16, 8, 4, 2, 1}; //二进制转十进制辅助数组
    int fileLen, offset, time = 0;              //time读取次数
    char tempText[8] = {0};                     //临时字符串
    BIT text[64] = {0};                          //每块64位

    fread(&fileLen, sizeof(int), 1, cFile);     //读取文件长度
    fread(&offset, sizeof(int), 1, cFile);

    while(fread(tempText, sizeof(char), 8, cFile))
    {
        time++;
        for(int i = 0; i < 8; i++)
        {
            for(int j = 7; j > -1; j--)
            {
                cipherPreTemp[i * 8 + (7 - j)]=cipherPre[i * 8 + (7 - j)];
                text[i * 8 + (7 - j)] = ((tempText[i] >> j) & 1);//对每一位转换成8个二进制位
                cipherPre[i * 8 + (7 - j)]=text[i * 8 + (7 - j)];
            }
        }

        InitPerm(text);//IP

        for(int i = 0; i < 16; i++)//16轮
        {
            OneTurnEncrypt(text, 15 - i);
        }

        for(int i = 0; i < 32; i++)//左右交换
        {
            BIT temp = text[i];
            text[i] = text[i + 32];
            text[i + 32] = temp;
        }

        InInitPerm(text);//IP逆置换

        for(int i = 0; i < 8; i++)//二进制转10进制
        {
            tempText[i] = 0;
            for(int j = 0; j < 8; j++)
            {
                text[i * 8 + j]^=cipherPreTemp[i * 8 + j];
                tempText[i] += text[i * 8 + j] * bit[j];
            }
        }
        if(time == fileLen) //最后一轮处理补位
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
