#include <iostream>
#include <stack>
#include <queue>
#include "forest.h"
using namespace std;

void Create(pTN &root)//递归创建树
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

void Tree::CreateTree()//创建树
{
    Create(root);   //构造函数调用创建树
}

void PreRec(pTN root)
{
    if(root == NULL)
        return;
    cout << root->data << " ";
    PreRec(root->FChild);
    PreRec(root->NBrother);
}

void Tree::PreOrderRec()//先根递归
{
    PreRec(root);   //对需要传参数的先根遍历函数进行封装
}

void Tree::PreOrderIte()//先根迭代
{
    stack<pTN> S;
    pTN p = root;//申请栈空间，及初始化

    while(p != NULL || !S.empty())//当栈为空并且最后一个兄弟结点也访问完毕(p=NULL)时退出
    {
        while(p != NULL)//访问p并将p的大孩子结点全部压栈
        {
            cout << p->data << " ";
            S.push(p);
            p = p->FChild;
        }

        p = S.top();    //从下到上一次访问每一个大孩子结点的右兄弟子树,并对子树以同样的方法处理，有回溯的思想
        S.pop();
        p = p->NBrother;//每个节点都要充当一次根节点,所以会全部遍历
    }
}

void PostRec(pTN root)
{
    if(root == NULL)
        return;
    else
    {
        PostRec(root->FChild);
        cout << root->data << " "; //不同于二叉树，此处大孩子结点为空时他就是对应二叉树里面的叶节点（但其右兄弟指针不为空）
        PostRec(root->NBrother); //此时应输出它本身再考虑右兄弟遍历，否则继续遍历右兄弟则会同一层倒序输出

    }
}

void Tree::PostOrderRec()//后根递归
{
    PostRec(root);
}

void Tree::PostOrderIte()//后根迭代
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
        cout << p->data << " ";//思想和先跟迭代一样,只是访问位置不同
        p = p->NBrother;
    }
}

void Tree::LevelOrder()//层次遍历
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





/***********************华丽的分割线-以下为森林的操作***************************/




Forest::Forest(int n)//构造函数
{
    trees = new Tree[n];
    count = n;
}

void Forest::CreateForest()//创建森林
{

    for(int i = 0; i < count; i++)
    {
        trees[i].CreateTree();
    }
}

void Forest::PreOrderRec()//先根递归
{
    for(int i = 0; i < count; i++)
    {
        cout << "Tree[" << i + 1 << "]:";
        trees[i].PreOrderRec();
        cout << endl;
    }
}
void Forest::PreOrderIte()//先根迭代
{
    for(int i = 0; i < count; i++)
    {
        cout << "Tree[" << i + 1 << "]:";
        trees[i].PreOrderIte();
        cout << endl;
    }
}

void Forest::PostOrderRec()//后根递归
{
    for(int i = 0; i < count; i++)
    {
        cout << "Tree[" << i + 1 << "]:";
        trees[i].PostOrderRec();
        cout << endl;
    }
}

void Forest::PostOrderIte()//后根迭代
{
    for(int i = 0; i < count; i++)
    {
        cout << "Tree[" << i + 1 << "]:";
        trees[i].PostOrderIte();
        cout << endl;
    }
}

void Forest::LevelOrder()//层次遍历
{
    for(int i = 0; i < count; i++)
    {
        cout << "Tree[" << i + 1 << "]:";
        trees[i].LevelOrder();
        cout << endl;
    }
}

