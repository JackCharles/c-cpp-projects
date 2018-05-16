#include<iostream>
#include"header.h"

using namespace std;

SLList::SLList()
{
    head = rear = cuur = new SLNode(); //��λ���,��ʼ����ǰ���ָ��Ϊ��λ���
    size = 0;
}

void SLList::CreatList()
{
    cout << "���������������ĳ���:";
    cin >> size;
    cout << "������" << size << "��ֵ:";
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
        cout << "����Ϊ��!" << endl;
        return;
    }

    cout << "Ŀǰ������:";
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
    cout << "--��ѡ����뷽ʽ:" << endl;
    cout << "<1>��ǰ,<2>��λ,<3>��β:";
    int item;
    char n;
    cin >> n;
    switch(n)
    {
        case '1':
            cout << "������������ֵ:";
            cin >> item;
            cuur->next = new SLNode(item, cuur->next);
            if(cuur == rear)
            rear = cuur->next;
            size++;
            OutPut();
            break;
        case '2':
            cout << "������������ֵ:";
            cin >> item;
            if(head->next==NULL)//�ձ�
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
            cout << "������������ֵ:";
            cin >> item;
            rear->next=new SLNode(item,NULL);
            rear=rear->next;
            size++;
            OutPut();
            break;
        default:
            cout<<"�������!"<<endl;
    }
}

void SLList::Delete(int& item)
{
    cout << "--��ѡ��ɾ����ʽ:" << endl;
    cout << "<1>��ǰ���,<2>��λ���,<3>��β:";
    char n;
    cin >> n;
    switch(n)
    {
        case '1':
        {
            if(cuur==rear||head->next==NULL)
            {
                cout<<"��ɾ����㲻���ڻ�����Ϊ��!"<<endl;
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
                cout<<"����Ϊ��!"<<endl;
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
                cout<<"����Ϊ��!"<<endl;
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
            cout<<"�������!"<<endl;
    }
}

bool SLList::Find(int& item)
{
    cout<<"ѡ���ȡ��ʽ:"<<endl;
    cout<<"<1>��ǰ���,<2>��k�����:";
    char n;
    cin>> n;
    switch (n)
    {
        case '1':
            if(cuur==head)
            {
                cout<<"��ǰ�������λ���,��ֵ��Ч!"<<endl;
                return false;
            }
            item=cuur->data;
            break;

        case '2':
            cout<<"���������ȡ����λ��k:";
            int k;
            cin>>k;
            if(k < 1|| k>size)
            {
                cout << "kֵ���Ϸ�!" << endl;
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
            cout<<"�������!"<<endl;
    }
    OutPut();
    return true;
}

void SLList::Search()
{
    if(head->next==NULL)
    {
        cout<<"����Ϊ��!"<<endl;
        return;
    }

    int item,i = 0,flag=0;
    cout<<"����������ҵ�ֵ:";
    cin>>item;
    SLNode*p = head;
    OutPut();
    while(p != NULL)
    {
        if(p->data==item)
        {
            cout<<item<<"�������е�"<<i<<"��λ��!"<<endl;
            flag=1;
        }
        p = p->next;
        i++;
    }
    if(flag==0)
        cout << "��Ҫ���ҵ�ֵ������!" << endl;
}
