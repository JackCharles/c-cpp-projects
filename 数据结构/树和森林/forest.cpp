#include <iostream>
#include <stack>
#include <queue>
#include "forest.h"
using namespace std;

void Create(pTN &root)//�ݹ鴴����
{
    char ch;
    int n;
    cin >> ch;
    root = new TN(ch);
    cin >> n;
    if(n > 0)
    {
        Create(root->FChild);
        pTN p = root->FChild;

        for(int i = 1; i < n; i++)
        {
            Create(p->NBrother);
            p = p->NBrother;
        }
    }
}

void Tree::CreateTree()//������
{
    Create(root);   //���캯�����ô�����
}

void PreRec(pTN root)
{
    if(root == NULL)
        return;
    cout << root->data << " ";
    PreRec(root->FChild);
    PreRec(root->NBrother);
}

void Tree::PreOrderRec()//�ȸ��ݹ�
{
    PreRec(root);   //����Ҫ���������ȸ������������з�װ
}

void Tree::PreOrderIte()//�ȸ�����
{
    stack<pTN> S;
    pTN p = root;//����ջ�ռ䣬����ʼ��

    while(p != NULL || !S.empty())//��ջΪ�ղ������һ���ֵܽ��Ҳ�������(p=NULL)ʱ�˳�
    {
        while(p != NULL)//����p����p�Ĵ��ӽ��ȫ��ѹջ
        {
            cout << p->data << " ";
            S.push(p);
            p = p->FChild;
        }

        p = S.top();    //���µ���һ�η���ÿһ�����ӽ������ֵ�����,����������ͬ���ķ��������л��ݵ�˼��
        S.pop();
        p = p->NBrother;//ÿ���ڵ㶼Ҫ�䵱һ�θ��ڵ�,���Ի�ȫ������
    }
}

void PostRec(pTN root)
{
    if(root == NULL)
        return;
    else
    {
        PostRec(root->FChild);
        cout << root->data << " "; //��ͬ�ڶ��������˴����ӽ��Ϊ��ʱ�����Ƕ�Ӧ�����������Ҷ�ڵ㣨�������ֵ�ָ�벻Ϊ�գ�
        PostRec(root->NBrother); //��ʱӦ����������ٿ������ֵܱ�������������������ֵ����ͬһ�㵹�����

    }
}

void Tree::PostOrderRec()//����ݹ�
{
    PostRec(root);
}

void Tree::PostOrderIte()//�������
{
    pTN stack[100], p = root;
    int top = -1;

    while(p != NULL || top != -1)
    {
        while(p != NULL)
        {

            top++;
            stack[top] = p;
            p = p->FChild;
        }

        p = stack[top];
        top--;
        cout << p->data << " ";//˼����ȸ�����һ��,ֻ�Ƿ���λ�ò�ͬ
        p = p->NBrother;
    }
}

void Tree::LevelOrder()//��α���
{
    queue<pTN> Q;
    pTN p = root;
    Q.push(p);

    while(!Q.empty())
    {
        p = Q.front();
        Q.pop();
        while(p != NULL)
        {
            cout << p->data << " ";
            if(p->FChild != NULL)
                Q.push(p->FChild);
            p = p->NBrother;
        }
    }
}





/***********************�����ķָ���-����Ϊɭ�ֵĲ���***************************/




Forest::Forest(int n)//���캯��
{
    trees = new Tree[n];
    count = n;
}

void Forest::CreateForest()//����ɭ��
{

    for(int i = 0; i < count; i++)
    {
        trees[i].CreateTree();
    }
}

void Forest::PreOrderRec()//�ȸ��ݹ�
{
    for(int i = 0; i < count; i++)
    {
        cout << "Tree[" << i + 1 << "]:";
        trees[i].PreOrderRec();
        cout << endl;
    }
}
void Forest::PreOrderIte()//�ȸ�����
{
    for(int i = 0; i < count; i++)
    {
        cout << "Tree[" << i + 1 << "]:";
        trees[i].PreOrderIte();
        cout << endl;
    }
}

void Forest::PostOrderRec()//����ݹ�
{
    for(int i = 0; i < count; i++)
    {
        cout << "Tree[" << i + 1 << "]:";
        trees[i].PostOrderRec();
        cout << endl;
    }
}

void Forest::PostOrderIte()//�������
{
    for(int i = 0; i < count; i++)
    {
        cout << "Tree[" << i + 1 << "]:";
        trees[i].PostOrderIte();
        cout << endl;
    }
}

void Forest::LevelOrder()//��α���
{
    for(int i = 0; i < count; i++)
    {
        cout << "Tree[" << i + 1 << "]:";
        trees[i].LevelOrder();
        cout << endl;
    }
}

