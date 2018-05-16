#include <iostream>

using namespace std;

typedef struct Node
{
    char data;
    Node *left, *right;
    Node(char ch, Node*l = NULL, Node*r = NULL)
    {
        data = ch;
        left = l;
        right = r;
    }
    Node()
    {
        left = right = NULL;
    }
} SN, *pSN;

typedef struct StackNode
{
    pSN treeNode;
    int flag;
    StackNode *next;

    StackNode(pSN p, int f = 0, StackNode*n = NULL)
    {
        treeNode = p;
        flag = f;
        next = n;
    }

    StackNode()
    {
        next = NULL;
    }
} SSN, *pSSN;

void CreateTree(pSN &root)
{
    char temp;
    cin >> temp;
    if(temp == '#')
    {
        root = NULL;
        return;
    }
    else
    {
        root = new SN(temp);
        CreateTree(root->left);
        CreateTree(root->right);
    }
}

void InOrder(pSN root)
{
    if(root == NULL)
        return;
    else
    {
        InOrder(root->left);
        cout << root->data << " ";
        InOrder(root->right);
    }
}

void NInO(pSN root)///非递归中根遍历算法
{
    pSSN Stacktop = NULL;
    pSN p = root;

Loop:
    while(p != NULL)
    {
        pSSN q = new SSN(p);//压栈时一定要保留其左右子树的信息，下面弹栈(访问根节点)后还要对其右子树访问
        q->next = Stacktop;
        Stacktop = q;

        p = p->left;
    }//从根结点开始左子结点一路压栈

    if(Stacktop != NULL)
    {
        p = Stacktop->treeNode;
        pSSN q = Stacktop;
        Stacktop = Stacktop->next;
        delete q;//弹栈

        cout << p->data << " ";
        p = p->right;
        goto Loop;
    }//当栈不为空时弹一个，找其对应右子树进行上述相同操作,当栈为空时整棵树的根节点已被访问且右子树也在接下来的循环中被访问，程序结束
}

void NPrO(pSN root)///非先
{
    pSSN StackTop = NULL;
    pSN p = root;

Loop:
    while(p != NULL)
    {
        cout << p->data << " ";

        pSSN q = new SSN(p);
        q->next = StackTop;
        StackTop = q;

        p = p->left;
    }

    if(StackTop != NULL)
    {
        p = StackTop->treeNode;

        pSSN q = StackTop;
        StackTop = StackTop->next;
        delete q;

        p = p->right;
        goto Loop;
    }
}

void NPoO(pSN root)///非后
{
    int flag;
    pSSN StackTop = NULL;
    pSN p = NULL;

    if(root == NULL)
        return;

    pSSN q = new SSN(root, 0);
    q->next = StackTop;
    StackTop = q;//根结点入栈

    while(StackTop != NULL)
    {
        p = StackTop->treeNode;
        flag = StackTop->flag;

        if(flag == 0)
        {
            StackTop->flag = 1; //更改状态
            if(p->left != NULL)
            {
                q = new SSN(p->left, 0);
                q->next = StackTop;
                StackTop = q;
            }
        }
        else if(flag == 1)
        {
            StackTop->flag = 2;
            if(p->right != NULL)
            {
                q = new SSN(p->right, 0);
                q->next = StackTop;
                StackTop = q;
            }
        }
        else if(flag == 2)
        {
            q = StackTop;
            StackTop = StackTop->next;
            delete q;
            cout << p->data << " ";
        }
    }/*while*/
}

int main()
{
    pSN root = NULL;
    CreateTree(root);
    cout << "非递归先根遍历:";
    NPrO(root);
    cout << endl << "非递归中根遍历:";
    NInO(root);
    cout << endl << "非递归后根遍历:";
    NPoO(root);
    return 0;
}
