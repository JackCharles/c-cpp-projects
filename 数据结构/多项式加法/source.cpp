#include<iostream>
#include"header.h"
using namespace std;

SLList::SLList()
{
    head = rear = cuur = new SLNode(0 , 0, NULL);
}

SLList::~SLList()
{
    while(head != NULL)
    {
        SLNode*p = head;
        head = head->next;
        delete p;
    }
}

void SLList::CreatList()
{
    cout << "请输入待创建多项式项数:";
    cin >> size;
    for(int i = 0; i < size; ++i)
    {
        int xi, zh;
        cout << "第" << i + 1 << "项系数和指数:";
        cin >> xi >> zh;
        SLNode*p = new SLNode(xi, zh, NULL);
        rear->next = p;
        rear = p;
    }
    rear->next = NULL;
}


void SLList::OutPut()
{
    SLNode*p = head->next;
    if(p->zh == 1)//输出头结点(第一项)
    {
        if(p->xi == 1)
            cout << "x";
        else if(p->xi == -1)
            cout << "-x";
        else
            cout << p->xi << "x";
    }
    else if(p->zh == 0)
    {
        cout << p->xi;
    }
    else
    {
        if(p->xi == 1)
            cout << "x^" << p->zh;
        else if(p->xi == -1)
            cout << "-x^" << p->zh;
        else
            cout << p->xi << "x^" << p->zh;
    }
    p = p->next;

    while(p != NULL)//输出其他部分
    {
        if(p->zh == 1)
        {
            if(p->xi == 1)
                cout << "+x";
            else if(p->xi == -1)
                cout << "-x";
            else
                cout << "+" << p->xi << "x";
        }
        else if(p->zh == 0)
        {
            if(p->xi > 0)
                cout << "+" << p->xi;
            else
                cout << p->xi;
        }
        else
        {
            if(p->xi == 1)
                cout << "+x^" << p->zh;
            else if(p->xi == -1)
                cout << "-x^" << p->zh;
            else
                cout << "+" << p->xi << "x^" << p->zh;
        }
        p = p->next;
    }
    cout << endl;
}
