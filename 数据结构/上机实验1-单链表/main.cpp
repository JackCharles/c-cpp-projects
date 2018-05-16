#include <iostream>
#include <cstdlib>
#include "header.h"

using namespace std;

int main()
{
    SLList*L=new SLList();
    int item;
    char ch;
    cout<<"刚开始需要创建链表!"<<endl;
    L->CreatList();
    system("pause");
    system("cls");


    cout<<"---选择操作---"<<endl;
    cout<<"<1>插入 <2>删除 <3>存取 <4>查找 <0>退出:";
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
                cout<<"删除的值是:"<<item<<endl;
                break;
            case '3':
                if(L->Find(item))
                    cout<<"所取值为:"<<item<<endl;
                else
                    cout<<"存取失败!"<<endl;
                break;
            case '4':
                L->Search();
                break;
            default:
                cout<<"输入错误!"<<endl;
        }
        system("pause");
        system("cls");
        cout<<"---选择操作---"<<endl;
        cout<<"<1>插入 <2>删除 <3>存取 <4>查找 <0>退出:";
        cin>>ch;
    }
    return 0;
}
