#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<time.h>
#include"DES_encryption.h"
#include"md5.h"
#include"RSAkey.cpp"
#include"RSA.cpp"
using namespace std;

int main()
{
    system("color 1E");
    system("title 文件加密系统");
    cout << " ---------------欢迎使用混合加密系统--------------- " << endl;
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃Powered by: WangQi WangShiying Zhongjie HouJunze┃" << endl;
    cout << "┃Program version : 2.0.1                         ┃" << endl;
    cout << "┃All Rights Reserved.                            ┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;

    char n;
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃ 请选择您要进行的操作                           ┃" << endl;
    cout << "┃ <E/e>       加密文件                           ┃" << endl;
    cout << "┃ <D/d>       解密文件                           ┃" << endl;
    cout << "┃ <M/m>       MD5 校验                           ┃" << endl;
    cout << "┃ <K/k>       生成秘钥                           ┃" << endl;
    cout << "┃ <H/h>       程序帮助                           ┃" << endl;
    cout << "┃ < 0 >       退出程序                           ┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl << endl;
    cin.get(n);

    while(n != '0')
    {

        if(n == 'E' || n == 'e')
        {
            char plainfile[40] = {0};
            char cipherfile[40] = {0};
            char key[8], IV[8], *md5;
            long long cipherText[8];

            cout << "请输入<待加密文件名>和<目标文件名>:" << endl;
            cin >> plainfile;
            cin >> cipherfile;

            long t = clock();

            cout << "正在对明文生成签名..." << endl << endl;
            md5 = MD5_file(plainfile, 16);
            RSA_Encrypt(md5, 16, "A-private.txt", "pTempFile");
            cout << "明文签名产生完成!" << endl << endl;

            cout << "正在生成DES秘钥和初始向量..." << endl << endl;
            srand(time(NULL));
            for(int i = 0; i < 8; i++)
            {
                key[i] = rand() % 127;
                IV[i] = rand() % 123;
            }
            cout << "正在加密DES秘钥和初始向量..." << endl << endl;
            RSA_Encrypt(key, 8, "B-public.txt", cipherfile);
            RSA_Encrypt(IV, 8, "B-public.txt", cipherfile);
            cout << "DES秘钥和IV向量加密完毕!" << endl << endl;
            cout << "正在加密明文和签名..." << endl << endl;

            FILE*pf = fopen(plainfile, "rb");
            FILE*cf = fopen(cipherfile, "ab");
            FILE*ptemp = fopen("pTempFile", "rb");    //存放签名明文
            FILE*cSig = fopen("signature.sig", "wb+"); //存放签名密文
            if(pf == NULL || cf == NULL || ptemp == NULL || cSig == NULL)
            {
                cout << "打开或创建文件失败,请再试一次!" << endl << endl;
                goto Loop;
            }
            fputs("$$$$$$$$", cf);/////////////////////////////密文标记
            Encryption *E = new Encryption(key, IV);
            E->SetFilePointer(pf, cf);
            E->DesEncrypt();
            E->SetFilePointer(ptemp, cSig);
            E->DesEncrypt();
            fclose(ptemp);          //它的使命已完成，shut down
            fclose(cSig);
            fclose(cf);
            fclose(pf);
            remove("pTempFile");   //删除签名明文缓存
            cout << "明文和签名加密完成!" << endl << endl;

            cout << "文件加密完毕,加密用时:" << (clock() - t) / 1000.0 << "s!" << endl << endl;
        }

        else if(n == 'D' || n == 'd')
        {
            char plainfile[40] = {0};
            char cipherfile[40] = {0};
            char KeyAndIV[17] = {0}, md5[17] = {0};

            cout << "请输入<待解密文件名>和<目标文件名>:" << endl;
            cin >> cipherfile;
            cin >> plainfile;
            long t = clock();

            RSA_Decrypt(cipherfile, 16, "B-private.txt", KeyAndIV);
            FILE*pf = fopen(plainfile, "wb");
            FILE*cf = fopen(cipherfile, "rb");
            if(pf == NULL || cf == NULL)
            {
                cout << "打开或创建文件失败,请再试一次!" << endl;
                goto Loop;
            }

            cout<<"正在解密..."<<endl<<endl;
            int s = 0;
            while(s < 8)
            {
                char ch = fgetc(cf);
                if(ch == '$')
                    s++;
                else
                    s = 0;
            }//跳过前面的秘钥信息$$$$$$$是标记
            Encryption* E = new Encryption(KeyAndIV, KeyAndIV + 8);
            E->SetFilePointer(pf, cf);
            E->DesDecrypt();
            fclose(pf);
            fclose(cf);
            cout << "文件解密完成,用时:"<<(clock()-t)/1000.0<<"s"<<endl<<endl;
            cout<<"是否需要检验签名<Y/y>?" << endl;
            cin >> n;
            if(n == 'y' || n == 'Y')
            {
                FILE*sf = fopen("signature.sig", "rb");
                FILE*pf = fopen("sTempFile", "wb");
                Encryption E(KeyAndIV, KeyAndIV + 8);
                E.SetFilePointer(pf, sf);
                E.DesDecrypt();
                fclose(sf);
                fclose(pf);
                RSA_Decrypt("sTempFile", 16, "A-public.txt", md5);
                cout << "签名信息:" << md5 << endl << endl;
                remove("sTempFile");
                cout << "正在进行指纹验证..." << endl << endl;
                char *md5n = MD5_file(plainfile, 16);
                bool flag = true;
                for(int i = 0; i < 16; i++)
                {
                    if(md5[i] != md5n[i])
                    {
                        flag = false;
                        cout << "指纹匹配失败,文件可能被篡改!" << endl << endl;
                        break;
                    }
                }
                if(flag)
                    cout << "恭喜你,指纹校验成功,文件完好!" << endl << endl;
            }

        }

        else if(n == 'm' || n == 'M')
        {
            cout << "请输入<待求MD5>的文件名:" << endl;
            char plain[20] = {0};
            cin >> plain;
            int md5Len = 16;
            char *md5;
            md5 = MD5_file(plain, md5Len);
            cout << "MD5:" << md5 << endl;
            cout << "是否需要与另一文件比对MD5?<Y/y>是,<其他>否:";
            cin >> n;
            if(n == 'Y' || n == 'y')
            {
                cout << "请输入<另一文件名>:";
                cin >> plain;
                char *md52 = MD5_file(plain, md5Len);
                cout << "MD5:" << md52 << endl;
                bool flag = true;
                for(int i = 0; i < md5Len; i++)
                {
                    if(md5[i] != md52[i])
                    {
                        flag = false;
                        cout << "MD5匹配失败,文件可能被篡改!" << endl;
                        break;
                    }
                }
                if(flag)
                    cout << "恭喜你,MD5校验成功!" << endl;
            }
        }

        else if(n == 'K' || n == 'k')
        {
            cout << "正在生成秘钥..." << endl;
            CreateRsaKey();
            cout << endl << "秘钥产生完成,在当前路径下形如A-public.txt的文件中,请不要修改!" << endl << endl;
        }

        else if(n == 'H' || n == 'h')
        {
            cout << "1.你如果是初次使用该程序并且没有RSA秘钥,你需要产生两对RSA秘钥,按K/k产生." << endl;
            cout << "2.你可能对DOS下文件路径不熟悉,因此我们建议你将待加密文件与本程序放在同一" << endl;
            cout << "  文件夹下,这样你就可以只输入文件名(带后缀)程序便能正确运行."             << endl;
            cout << "3.该程序采用DES对文件正文和签名加密,DES秘钥和初始向量由系统随机生成."     << endl;
            cout << "4.DES秘钥和初始向量由RSA加密并与正文对应密文写入同一文件,方便管理."       << endl;
            cout << "5.该程序还采用数字签名由DES加密并存放于当前目录下signature.sig文件中.    "<< endl;
            cout << "6.只要经本程序加密的文件,无论何时何地只需你的私钥和发送方的公钥即可解密." << endl;
        }

        else
        {
            cout << "输入错误,重新输入!" << endl;
        }
Loop:
        system("pause");
        cin.get();
        system("cls");
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
        cout << "┃ 请选择您要进行的操作                           ┃" << endl;
        cout << "┃ <E/e>       加密文件                           ┃" << endl;
        cout << "┃ <D/d>       解密文件                           ┃" << endl;
        cout << "┃ <M/m>       MD5 校验                           ┃" << endl;
        cout << "┃ <K/k>       生成秘钥                           ┃" << endl;
        cout << "┃ <H/h>       程序帮助                           ┃" << endl;
        cout << "┃ < 0 >       退出程序                           ┃" << endl;
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl << endl;

        cin.get(n);
    }
    cout << "欢迎下次使用..." << endl << endl;
    system("pause");

    return 0;
}
