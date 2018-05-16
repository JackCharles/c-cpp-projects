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
    system("title �ļ�����ϵͳ");
    cout << " ---------------��ӭʹ�û�ϼ���ϵͳ--------------- " << endl;
    cout << "����������������������������������������������������" << endl;
    cout << "��Powered by: WangQi WangShiying Zhongjie HouJunze��" << endl;
    cout << "��Program version : 2.0.1                         ��" << endl;
    cout << "��All Rights Reserved.                            ��" << endl;
    cout << "����������������������������������������������������" << endl;

    char n;
    cout << "����������������������������������������������������" << endl;
    cout << "�� ��ѡ����Ҫ���еĲ���                           ��" << endl;
    cout << "�� <E/e>       �����ļ�                           ��" << endl;
    cout << "�� <D/d>       �����ļ�                           ��" << endl;
    cout << "�� <M/m>       MD5 У��                           ��" << endl;
    cout << "�� <K/k>       ������Կ                           ��" << endl;
    cout << "�� <H/h>       �������                           ��" << endl;
    cout << "�� < 0 >       �˳�����                           ��" << endl;
    cout << "����������������������������������������������������" << endl << endl;
    cin.get(n);

    while(n != '0')
    {

        if(n == 'E' || n == 'e')
        {
            char plainfile[40] = {0};
            char cipherfile[40] = {0};
            char key[8], IV[8], *md5;
            long long cipherText[8];

            cout << "������<�������ļ���>��<Ŀ���ļ���>:" << endl;
            cin >> plainfile;
            cin >> cipherfile;

            long t = clock();

            cout << "���ڶ���������ǩ��..." << endl << endl;
            md5 = MD5_file(plainfile, 16);
            RSA_Encrypt(md5, 16, "A-private.txt", "pTempFile");
            cout << "����ǩ���������!" << endl << endl;

            cout << "��������DES��Կ�ͳ�ʼ����..." << endl << endl;
            srand(time(NULL));
            for(int i = 0; i < 8; i++)
            {
                key[i] = rand() % 127;
                IV[i] = rand() % 123;
            }
            cout << "���ڼ���DES��Կ�ͳ�ʼ����..." << endl << endl;
            RSA_Encrypt(key, 8, "B-public.txt", cipherfile);
            RSA_Encrypt(IV, 8, "B-public.txt", cipherfile);
            cout << "DES��Կ��IV�����������!" << endl << endl;
            cout << "���ڼ������ĺ�ǩ��..." << endl << endl;

            FILE*pf = fopen(plainfile, "rb");
            FILE*cf = fopen(cipherfile, "ab");
            FILE*ptemp = fopen("pTempFile", "rb");    //���ǩ������
            FILE*cSig = fopen("signature.sig", "wb+"); //���ǩ������
            if(pf == NULL || cf == NULL || ptemp == NULL || cSig == NULL)
            {
                cout << "�򿪻򴴽��ļ�ʧ��,������һ��!" << endl << endl;
                goto Loop;
            }
            fputs("$$$$$$$$", cf);/////////////////////////////���ı��
            Encryption *E = new Encryption(key, IV);
            E->SetFilePointer(pf, cf);
            E->DesEncrypt();
            E->SetFilePointer(ptemp, cSig);
            E->DesEncrypt();
            fclose(ptemp);          //����ʹ������ɣ�shut down
            fclose(cSig);
            fclose(cf);
            fclose(pf);
            remove("pTempFile");   //ɾ��ǩ�����Ļ���
            cout << "���ĺ�ǩ���������!" << endl << endl;

            cout << "�ļ��������,������ʱ:" << (clock() - t) / 1000.0 << "s!" << endl << endl;
        }

        else if(n == 'D' || n == 'd')
        {
            char plainfile[40] = {0};
            char cipherfile[40] = {0};
            char KeyAndIV[17] = {0}, md5[17] = {0};

            cout << "������<�������ļ���>��<Ŀ���ļ���>:" << endl;
            cin >> cipherfile;
            cin >> plainfile;
            long t = clock();

            RSA_Decrypt(cipherfile, 16, "B-private.txt", KeyAndIV);
            FILE*pf = fopen(plainfile, "wb");
            FILE*cf = fopen(cipherfile, "rb");
            if(pf == NULL || cf == NULL)
            {
                cout << "�򿪻򴴽��ļ�ʧ��,������һ��!" << endl;
                goto Loop;
            }

            cout<<"���ڽ���..."<<endl<<endl;
            int s = 0;
            while(s < 8)
            {
                char ch = fgetc(cf);
                if(ch == '$')
                    s++;
                else
                    s = 0;
            }//����ǰ�����Կ��Ϣ$$$$$$$�Ǳ��
            Encryption* E = new Encryption(KeyAndIV, KeyAndIV + 8);
            E->SetFilePointer(pf, cf);
            E->DesDecrypt();
            fclose(pf);
            fclose(cf);
            cout << "�ļ��������,��ʱ:"<<(clock()-t)/1000.0<<"s"<<endl<<endl;
            cout<<"�Ƿ���Ҫ����ǩ��<Y/y>?" << endl;
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
                cout << "ǩ����Ϣ:" << md5 << endl << endl;
                remove("sTempFile");
                cout << "���ڽ���ָ����֤..." << endl << endl;
                char *md5n = MD5_file(plainfile, 16);
                bool flag = true;
                for(int i = 0; i < 16; i++)
                {
                    if(md5[i] != md5n[i])
                    {
                        flag = false;
                        cout << "ָ��ƥ��ʧ��,�ļ����ܱ��۸�!" << endl << endl;
                        break;
                    }
                }
                if(flag)
                    cout << "��ϲ��,ָ��У��ɹ�,�ļ����!" << endl << endl;
            }

        }

        else if(n == 'm' || n == 'M')
        {
            cout << "������<����MD5>���ļ���:" << endl;
            char plain[20] = {0};
            cin >> plain;
            int md5Len = 16;
            char *md5;
            md5 = MD5_file(plain, md5Len);
            cout << "MD5:" << md5 << endl;
            cout << "�Ƿ���Ҫ����һ�ļ��ȶ�MD5?<Y/y>��,<����>��:";
            cin >> n;
            if(n == 'Y' || n == 'y')
            {
                cout << "������<��һ�ļ���>:";
                cin >> plain;
                char *md52 = MD5_file(plain, md5Len);
                cout << "MD5:" << md52 << endl;
                bool flag = true;
                for(int i = 0; i < md5Len; i++)
                {
                    if(md5[i] != md52[i])
                    {
                        flag = false;
                        cout << "MD5ƥ��ʧ��,�ļ����ܱ��۸�!" << endl;
                        break;
                    }
                }
                if(flag)
                    cout << "��ϲ��,MD5У��ɹ�!" << endl;
            }
        }

        else if(n == 'K' || n == 'k')
        {
            cout << "����������Կ..." << endl;
            CreateRsaKey();
            cout << endl << "��Կ�������,�ڵ�ǰ·��������A-public.txt���ļ���,�벻Ҫ�޸�!" << endl << endl;
        }

        else if(n == 'H' || n == 'h')
        {
            cout << "1.������ǳ���ʹ�øó�����û��RSA��Կ,����Ҫ��������RSA��Կ,��K/k����." << endl;
            cout << "2.����ܶ�DOS���ļ�·������Ϥ,������ǽ����㽫�������ļ��뱾�������ͬһ" << endl;
            cout << "  �ļ�����,������Ϳ���ֻ�����ļ���(����׺)���������ȷ����."             << endl;
            cout << "3.�ó������DES���ļ����ĺ�ǩ������,DES��Կ�ͳ�ʼ������ϵͳ�������."     << endl;
            cout << "4.DES��Կ�ͳ�ʼ������RSA���ܲ������Ķ�Ӧ����д��ͬһ�ļ�,�������."       << endl;
            cout << "5.�ó��򻹲�������ǩ����DES���ܲ�����ڵ�ǰĿ¼��signature.sig�ļ���.    "<< endl;
            cout << "6.ֻҪ����������ܵ��ļ�,���ۺ�ʱ�ε�ֻ�����˽Կ�ͷ��ͷ��Ĺ�Կ���ɽ���." << endl;
        }

        else
        {
            cout << "�������,��������!" << endl;
        }
Loop:
        system("pause");
        cin.get();
        system("cls");
        cout << "����������������������������������������������������" << endl;
        cout << "�� ��ѡ����Ҫ���еĲ���                           ��" << endl;
        cout << "�� <E/e>       �����ļ�                           ��" << endl;
        cout << "�� <D/d>       �����ļ�                           ��" << endl;
        cout << "�� <M/m>       MD5 У��                           ��" << endl;
        cout << "�� <K/k>       ������Կ                           ��" << endl;
        cout << "�� <H/h>       �������                           ��" << endl;
        cout << "�� < 0 >       �˳�����                           ��" << endl;
        cout << "����������������������������������������������������" << endl << endl;

        cin.get(n);
    }
    cout << "��ӭ�´�ʹ��..." << endl << endl;
    system("pause");

    return 0;
}
