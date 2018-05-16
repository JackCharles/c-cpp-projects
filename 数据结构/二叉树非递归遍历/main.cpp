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

void NInO(pSN root)///�ǵݹ��и������㷨
{
    pSSN Stacktop = NULL;
    pSN p = root;

Loop:
    while(p != NULL)
    {
        pSSN q = new SSN(p);//ѹջʱһ��Ҫ������������������Ϣ�����浯ջ(���ʸ��ڵ�)��Ҫ��������������
        q->next = Stacktop;
        Stacktop = q;

        p = p->left;
    }//�Ӹ���㿪ʼ���ӽ��һ·ѹջ

    if(Stacktop != NULL)
    {
        p = Stacktop->treeNode;
        pSSN q = Stacktop;
        Stacktop = Stacktop->next;
        delete q;//��ջ

        cout << p->data << " ";
        p = p->right;
        goto Loop;
    }//��ջ��Ϊ��ʱ��һ���������Ӧ����������������ͬ����,��ջΪ��ʱ�������ĸ��ڵ��ѱ�������������Ҳ�ڽ�������ѭ���б����ʣ��������
}

void NPrO(pSN root)///����
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

void NPoO(pSN root)///�Ǻ�
{
    int flag;
    pSSN StackTop = NULL;
    pSN p = NULL;

    if(root == NULL)
        return;

    pSSN q = new SSN(root, 0);
    q->next = StackTop;
    StackTop = q;//�������ջ

    while(StackTop != NULL)
    {
        p = StackTop->treeNode;
        flag = StackTop->flag;

        if(flag == 0)
        {
            StackTop->flag = 1; //����״̬
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
    cout << "�ǵݹ��ȸ�����:";
    NPrO(root);
    cout << endl << "�ǵݹ��и�����:";
    NInO(root);
    cout << endl << "�ǵݹ�������:";
    NPoO(root);
    return 0;
}
