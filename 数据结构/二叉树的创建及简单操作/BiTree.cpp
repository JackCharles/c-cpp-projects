#include<iostream>
#include<fstream>//c++�ļ��������
#include<string>
#include<cstdlib>
using namespace std;

string filename;
fstream tree;//����һ���ļ�������
char ch;

typedef struct Node
{
    char data;
    struct Node*left;
    struct Node*right;
    Node(char ch, Node*LeftChild = NULL, Node*RightChild = NULL)
    {
        data = ch;
        left = LeftChild;
        right = RightChild;
    }
    Node(Node*LeftChild = NULL, Node*RightChild = NULL)
    {
        left = LeftChild;
        right = RightChild;
    }
} SN, *pSN;

typedef struct QueueNode
{
    pSN TreeNode;
    struct QueueNode*next;
    QueueNode(pSN p, QueueNode*nextNode = NULL)
    {
        TreeNode = p;
        next = nextNode;
    }
} QN, *pQN;

void OpenFile(string &fn)
{
    tree.open(fn, ios::in); //���ļ�
    tree >> ch; //���ļ������ַ�
    while(ch != '$')
        tree >> ch;
}

void CreateTree(SN *&root)
{
    tree >> ch;
    if(ch == '\n')
        tree >> ch;
    if(ch == '#')
    {
        root = NULL;
    }
    else
    {
        root = new SN(ch);
        CreateTree(root->left);
        CreateTree(root->right);
    }
}

void PreOrder(pSN root)
{
    if(root != NULL)
    {
        cout << root->data << " ";
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void InOrder(pSN root)
{
    if(root != NULL)
    {
        InOrder(root->left);
        cout << root->data << " ";
        InOrder(root->right);
    }
}

void PostOrder(pSN root)
{
    if(root != NULL)
    {
        PostOrder(root->left);
        PostOrder(root->right);
        cout << root->data << " ";
    }
}

pSN FindNode(pSN root, char item) //����dataΪitem�Ľڵ㲢���أ������ȸ�����
{
    pSN p = NULL;
    if(root == NULL) //�����ڵ�(��)�Ƿ�Ϊ�ա��ݹ���ڡ�
    {
        return NULL;
    }
    if(root->data == item) //��鵱ǰ���ڵ��Ƿ�����������ݹ���ڡ�
    {
        return root;
    }

    p = FindNode(root->left, item); //���������������ϣ������������еݹ�Ѱ��
    if(p != NULL)               //����ҵ�����ֱ�ӷ��أ������ٱ���������
        return p;
    else                       //�����������û���ҵ��ٱ���������Ѱ�ң���û�Ҷ��򷵻�NULL
    {
        p = FindNode(root->right, item); //�˷���ֻ���ҵ��ȸ������д�������item���ֵĵ�һ�ε�λ�ã�����λ�ò��ټ��
        return p;
    }

}

pSN Father(pSN root, pSN p)
{
    pSN temp = NULL;

    if(root == NULL || p == NULL)
    {
        return NULL;
    }
    if(root->left == p || root->right == p)
    {
        return root;
    }
    //ͬFindNode����Ϊ�ݹ����
    temp = Father(root->left, p); //��root���������ݹ���������ϸ��ڵ��򷵻�
    if(temp != NULL)
        return temp;//����ҵ�����ִ���������ı���
    else            //���������û���ҵ�����ݹ����������Ѱ��
    {
        temp = Father(root->right, p);
        return temp;
    }

}

void LeveOrder(pSN root, pQN &head) //��α���,ע��head��Ҫ������ռ�,Ϊ��ֹ�����׵�ַ��ʧ,����ָ�������
{

    if(root != NULL)
    {
        head = new QN(root);
    }

    pQN p = head, rear = head; //p��ͷ��β����ÿһ������(������)���,������������ӽ���Ա����,rear�������β��ӽ��
    while(p != NULL)
    {
        if(p->TreeNode->left != NULL) //p������������ռ����
        {
            rear->next = new QN(p->TreeNode->left);
            rear = rear->next;
        }
        if(p->TreeNode->right != NULL)
        {
            rear->next = new QN(p->TreeNode->right);
            rear = rear->next;
        }
        p = p->next; //p�����λ
    }

}

bool IsCompleteTree(pQN head)//���ò�α���
{
    int flag = 1; //1����ȫ��������0����
    pQN p = head;
    while(p != NULL)
    {
        if(p->TreeNode->left == NULL && p->TreeNode->right != NULL) //1.������Ϊ����������Ϊ��
        {
            flag = 0;
            return false;
        }
        else if(p->TreeNode->right == NULL)//��һ�μ�⵽������Ϊ��
        {
            //2.��������,��������,��κ��ȫ��Ҷ�ӽڵ�
            pQN q = p->next;                                 //3.��ǰ��Ҷ�ӽڵ�,��κ��ȫ��Ҷ�ӽڵ�
            while(q != NULL)                                //ps:2&3�������ڵ���Ҷ�ӽڵ�֮��Ĺ��ɽڵ���������,���ۺ���һ��
            {
                if(q->TreeNode->left != NULL || q->TreeNode->right != NULL)
                {
                    flag = 0;
                    return false;
                }
                q = q->next;
            }/*-while-*/

            if(flag)//���p�Ժ�Ľڵ㶼��Ҷ�ӽڵ�,��ȫ��������������,�����ٽ�p�����,����ѭ��;
            {
                return true;
            }
        }/*-if-*/
        p = p->next;
    }/*-while-*/
}

void Del(pSN t)//ɾ����tΪ���Ķ�����,���tΪ�ӽ��,�򲻸�����t�ĸ�������Һ���ָ��
{
    if(t == NULL)
        return;
    else
    {
        Del(t->left);
        Del(t->right);
        delete t;
    }
}

void DST(pSN &root, pSN t)//ɾ��t��㼰����������
{
    if(t == NULL)
    {
        return;
    }
    else if(t == root)
    {
        Del(t);
        root = NULL;
        return ;
    }
    else
    {
        pSN father = Father(root, t);
        if(father->left == t)
            father->left = NULL;
        else
            father->right = NULL;
        Del(t);
    }
}



int main()
{
    pSN root = new SN();
    char item;
    /*----------------------------------------------------------*///����������
    cout << "�����������ڵ��ļ�����:";
    cin >> filename;
    OpenFile(filename);
    CreateTree(root);
    /*----------------------------------------------------------*///�ȸ�����
    cout << "�ȸ�����:";
    PreOrder(root);
    /*----------------------------------------------------------*///�и�����
    cout << endl << "�и�����:";
    InOrder(root);
    /*----------------------------------------------------------*///�������
    cout << endl << "�������:";
    PostOrder(root);
    cout << endl;
    /*----------------------------------------------------------*///����ĳ�����
    cout << "������Ҫ��λ���Ľ��:";
    cin >> item;
    pSN p = FindNode(root, item);
    if(p == NULL)
        cout << "û�з��ֽ��:" << item << endl;
    else
        cout << "�������ڵ�:" << p->data << endl;

    /*----------------------------------------------------------*///����ĳ�����ĸ����
    pSN father = Father(root, p);
    if(father != NULL)
        cout << "���" << p->data << "�ĸ������:" << father->data << endl;
    else
        cout << item << "û�и����,�����Ǹ����!" << endl;
    /*----------------------------------------------------------*///��α������������
    pQN head = NULL, q = NULL;
    LeveOrder(root, head); //����������α�������������ʽ������
    q = head;
    cout << "��α���Ϊ:";
    while(q != NULL)
    {
        cout << q->TreeNode->data << " ";
        q = q->next;
    }
    cout << endl;
    /*----------------------------------------------------------*///�ж��Ƿ�Ϊ��ȫ������
    if(IsCompleteTree(head))
    {
        cout << "��������ǡ���ȫ������!" << endl;
    }
    else
    {
        cout << "����������ǡ���ȫ������!" << endl;
    }
    /*----------------------------------------------------------*///ɾ��ĳ������������
    DST(root, p);
    if(root != NULL)
    {
        cout << "ɾ��������λ���Ľ�㼰������������,�ȸ�����Ϊ:";
        PreOrder(root);
    }
    else
        cout << "������Ϊ��!" << endl;
    /*----------------------------------------------------------*/
    return 0;

}
