#include <iostream>
#include <cstdlib>
#include "header.h"

using namespace std;

int main()
{
    SLList*L=new SLList();
    int item;
    char ch;
    cout<<"�տ�ʼ��Ҫ��������!"<<endl;
    L->CreatList();
    system("pause");
    system("cls");


    cout<<"---ѡ�����---"<<endl;
    cout<<"<1>���� <2>ɾ�� <3>��ȡ <4>���� <0>�˳�:";
    cin>>ch;
    while(ch!='0')
    {
        switch(ch)
        {
            case '1':
                L->Insert();
                break;
            case '2':
                L->Delete(item);
                cout<<"ɾ����ֵ��:"<<item<<endl;
                break;
            case '3':
                if(L->Find(item))
                    cout<<"��ȡֵΪ:"<<item<<endl;
                else
                    cout<<"��ȡʧ��!"<<endl;
                break;
            case '4':
                L->Search();
                break;
            default:
                cout<<"�������!"<<endl;
        }
        system("pause");
        system("cls");
        cout<<"---ѡ�����---"<<endl;
        cout<<"<1>���� <2>ɾ�� <3>��ȡ <4>���� <0>�˳�:";
        cin>>ch;
    }
    return 0;
}
