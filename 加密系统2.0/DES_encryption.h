#ifndef DES_ENCRYPTION_H_INCLUDED
#define DES_ENCRYPTION_H_INCLUDED

#include <cstdio>
using namespace std;

typedef bool BIT;//以bool类型记录二进制

class Encryption
{
public:
    Encryption(char k[8],char iv[8]);
private:
    void ChangeCharToBit(char ASCII[8],BIT bit[64]);      //将ASCII码转换成二进制
    void CreateChildKey();                                //产生16个子秘钥
    void InitPerm(BIT text[64]);                          //初始置换(IP)64bit
    void InInitPerm(BIT text[64]);                        //逆初始置换64bit

    void E_Premutation(BIT text[32], BIT tText[48]);      //E盒扩展32bit->48bit
    void ExclusiveOR(BIT tText[48], int turn);            //异或48bit&轮数
    void S_Premutation(BIT tText[48], BIT text[32]);      //S盒代换48bit->32bit
    void P_Premutation(BIT text[32]);                     //P置换32bit
    void OneTurnEncrypt(BIT text[64],int turn);           //轮结构

public:
    void SetFilePointer(FILE*pf, FILE*cf);
    void DesEncrypt();   //DES总加密过程
    void DesDecrypt();    //解密
    void GetDesKey(char key[]);

private:
    char key[8];              //加密秘钥
    BIT bitKey[64];            //加密秘钥二进制形式
    BIT ChildKey[16][48];      //每一轮子秘钥
    char IV[8];
    FILE* pFile;                //明文文件
    FILE* cFile;                //密文文件
    int offset;
};

#endif // DES_ENCRYPTION_H_INCLUDED
