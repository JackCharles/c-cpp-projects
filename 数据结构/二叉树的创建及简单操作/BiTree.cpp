#include<iostream>
#include<fstream>//c++文件操作类库
#include<string>
#include<cstdlib>
using namespace std;

string filename;
fstream tree;//声明一个文件流对象
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
    tree.open(fn, ios::in); //打开文件
    tree >> ch; //从文件读入字符
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

pSN FindNode(pSN root, char item) //查找data为item的节点并返回，采用先根遍历
{
    pSN p = NULL;
    if(root == NULL) //检查根节点(树)是否为空【递归出口】
    {
        return NULL;
    }
    if(root->data == item) //检查当前根节点是否符合条件【递归出口】
    {
        return root;
    }

    p = FindNode(root->left, item); //上述条件都不符合，在其左子树中递归寻找
    if(p != NULL)               //如果找到了则直接返回，不用再遍历右子树
        return p;
    else                       //如果左子树中没有找到再遍历右子树寻找，都没找都则返回NULL
    {
        p = FindNode(root->right, item); //此方法只能找到先根序列中从左至右item出现的第一次的位置，后面位置不再检测
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
    //同FindNode以上为递归出口
    temp = Father(root->left, p); //从root的左子树递归遍历，符合父节点则返回
    if(temp != NULL)
        return temp;//如果找到了则不执行右子树的遍历
    else            //如果左子树没有找到，则递归遍历右子树寻找
    {
        temp = Father(root->right, p);
        return temp;
    }

}

void LeveOrder(pSN root, pQN &head) //层次遍历,注意head需要新申请空间,为防止链表首地址丢失,故用指针的引用
{

    if(root != NULL)
    {
        head = new QN(root);
    }

    pQN p = head, rear = head; //p从头到尾遍历每一个队列(二叉树)结点,检测有无左右子结点以便入队,rear用于向队尾添加结点
    while(p != NULL)
    {
        if(p->TreeNode->left != NULL) //p有左子树申请空间入队
        {
            rear->next = new QN(p->TreeNode->left);
            rear = rear->next;
        }
        if(p->TreeNode->right != NULL)
        {
            rear->next = new QN(p->TreeNode->right);
            rear = rear->next;
        }
        p = p->next; //p向后移位
    }

}

bool IsCompleteTree(pQN head)//采用层次遍历
{
    int flag = 1; //1是完全二叉树，0不是
    pQN p = head;
    while(p != NULL)
    {
        if(p->TreeNode->left == NULL && p->TreeNode->right != NULL) //1.左子树为空右子树必为空
        {
            flag = 0;
            return false;
        }
        else if(p->TreeNode->right == NULL)//第一次检测到右子树为空
        {
            //2.有左子树,无右子树,层次后继全是叶子节点
            pQN q = p->next;                                 //3.当前是叶子节点,层次后继全是叶子节点
            while(q != NULL)                                //ps:2&3就是满节点与叶子节点之间的过渡节点的两种情况,可综合在一起
            {
                if(q->TreeNode->left != NULL || q->TreeNode->right != NULL)
                {
                    flag = 0;
                    return false;
                }
                q = q->next;
            }/*-while-*/

            if(flag)//如果p以后的节点都是叶子节点,完全二叉树条件成立,无需再将p向后移,结束循环;
            {
                return true;
            }
        }/*-if-*/
        p = p->next;
    }/*-while-*/
}

void Del(pSN t)//删除以t为根的二叉树,如果t为子结点,则不负责处理t的父结点左右孩子指针
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

void DST(pSN &root, pSN t)//删除t结点及其左右子树
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
    /*----------------------------------------------------------*///创建二叉树
    cout << "请输入树所在的文件名称:";
    cin >> filename;
    OpenFile(filename);
    CreateTree(root);
    /*----------------------------------------------------------*///先根遍历
    cout << "先根遍历:";
    PreOrder(root);
    /*----------------------------------------------------------*///中根遍历
    cout << endl << "中根遍历:";
    InOrder(root);
    /*----------------------------------------------------------*///后根遍历
    cout << endl << "后根遍历:";
    PostOrder(root);
    cout << endl;
    /*----------------------------------------------------------*///查找某个结点
    cout << "请输入要定位到的结点:";
    cin >> item;
    pSN p = FindNode(root, item);
    if(p == NULL)
        cout << "没有发现结点:" << item << endl;
    else
        cout << "检索到节点:" << p->data << endl;

    /*----------------------------------------------------------*///查找某个结点的父结点
    pSN father = Father(root, p);
    if(father != NULL)
        cout << "结点" << p->data << "的父结点是:" << father->data << endl;
    else
        cout << item << "没有父结点,或者是根结点!" << endl;
    /*----------------------------------------------------------*///层次遍历并存入队列
    pQN head = NULL, q = NULL;
    LeveOrder(root, head); //将二叉树层次遍历，并存在链式队列中
    q = head;
    cout << "层次遍历为:";
    while(q != NULL)
    {
        cout << q->TreeNode->data << " ";
        q = q->next;
    }
    cout << endl;
    /*----------------------------------------------------------*///判断是否为完全二叉树
    if(IsCompleteTree(head))
    {
        cout << "这棵树【是】完全二叉树!" << endl;
    }
    else
    {
        cout << "这棵树【不是】完全二叉树!" << endl;
    }
    /*----------------------------------------------------------*///删除某结点的左右子树
    DST(root, p);
    if(root != NULL)
    {
        cout << "删除上述定位到的结点及其左右子树后,先根遍历为:";
        PreOrder(root);
    }
    else
        cout << "二叉树为空!" << endl;
    /*----------------------------------------------------------*/
    return 0;

}
