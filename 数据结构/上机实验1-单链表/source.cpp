#include<iostream>
#include"header.h"

using namespace std;

SLList::SLList()
{
    head = rear = cuur = new SLNode(); //哨位结点,初始化当前结点指针为哨位结点
    size = 0;
}

void SLList::CreatList()
{
    cout << "请输入待创建链表的长度:";
    cin >> size;
    cout << "请输入" << size << "个值:";
    for(int i = 0; i < size; i++)
    {
        int temp;
        cin >> temp;
        SLNode*p = new SLNode(temp);
        rear->next = p;
        rear = p;
    }
    rear->next = NULL;
    OutPut();
}

void SLList::OutPut()
{
    if(head->next == NULL)
    {
        cout << "链表为空!" << endl;
        return;
    }

    cout << "目前链表是:";
    SLNode*p = head->next;
    while(p->next != NULL)
    {
        cout << "[" << p->data << "]->";
        p = p->next;
    }
    cout << "[" << p->data << "]" << endl << endl;
}

void SLList::Insert()
{
    cout << "--请选择插入方式:" << endl;
    cout << "<1>当前,<2>哨位,<3>表尾:";
    int item;
    char n;
    cin >> n;
    switch(n)
    {
        case '1':
            cout << "请输入待插入的值:";
            cin >> item;
            cuur->next = new SLNode(item, cuur->next);
            if(cuur == rear)
            rear = cuur->next;
            size++;
            OutPut();
            break;
        case '2':
            cout << "请输入待插入的值:";
            cin >> item;
            if(head->next==NULL)//空表
            {
                head->next=new SLNode(item,head->next);
                rear=head->next;
            }
            else
                head->next=new SLNode(item,head->next);
            size++;
            OutPut();
            break;
        case '3':
            cout << "请输入待插入的值:";
            cin >> item;
            rear->next=new SLNode(item,NULL);
            rear=rear->next;
            size++;
            OutPut();
            break;
        default:
            cout<<"输入错误!"<<endl;
    }
}

void SLList::Delete(int& item)
{
    cout << "--请选择删除方式:" << endl;
    cout << "<1>当前后继,<2>哨位后继,<3>表尾:";
    char n;
    cin >> n;
    switch(n)
    {
        case '1':
        {
            if(cuur==rear||head->next==NULL)
            {
                cout<<"待删除结点不存在或链表为空!"<<endl;
                break;
            }
            SLNode*p=cuur->next;
            cuur->next=p->next;
            item=p->data;
            if(rear==p)
                rear=cuur;
            delete p;
            size--;
            OutPut();
            break;
        }
        case '2':
        {
            if(head->next==NULL)
            {
                cout<<"链表为空!"<<endl;
                break;
            }
            SLNode*p=head->next;
            head->next=p->next;
            item=p->data;
            if(rear==p)
                rear=head;
            delete p;
            size--;
            OutPut();
            break;
        }
        case '3':
        {
            if(head->next==NULL)
            {
                cout<<"链表为空!"<<endl;
                break;
            }
            cuur=head;
            while(cuur->next!=rear)
                cuur=cuur->next;
            item=rear->data;
            cuur->next=NULL;
            delete rear;
            rear=cuur;
            size--;
            OutPut();
            break;
        }
        default:
            cout<<"输入错误!"<<endl;
    }
}

bool SLList::Find(int& item)
{
    cout<<"选择存取方式:"<<endl;
    cout<<"<1>当前结点,<2>第k个结点:";
    char n;
    cin>> n;
    switch (n)
    {
        case '1':
            if(cuur==head)
            {
                cout<<"当前结点是哨位结点,其值无效!"<<endl;
                return false;
            }
            item=cuur->data;
            break;

        case '2':
            cout<<"请输入待存取结点的位置k:";
            int k;
            cin>>k;
            if(k < 1|| k>size)
            {
                cout << "k值不合法!" << endl;
                return false;
            }
            else
            {
                SLNode*p = head;
                for(int i = 0; i < k; ++i)
                    p = p->next;
                item = p->data;
            }
            break;
        default:
            cout<<"输入错误!"<<endl;
    }
    OutPut();
    return true;
}

void SLList::Search()
{
    if(head->next==NULL)
    {
        cout<<"链表为空!"<<endl;
        return;
    }

    int item,i = 0,flag=0;
    cout<<"请输入待查找的值:";
    cin>>item;
    SLNode*p = head;
    OutPut();
    while(p != NULL)
    {
        if(p->data==item)
        {
            cout<<item<<"在链表中第"<<i<<"个位置!"<<endl;
            flag=1;
        }
        p = p->next;
        i++;
    }
    if(flag==0)
        cout << "你要查找的值不存在!" << endl;
}
