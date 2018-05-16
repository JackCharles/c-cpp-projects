#ifndef Tree_H_INCLUDED
#define Tree_H_INCLUDED

typedef struct TreeNode
{
    char data;
    TreeNode*FChild;
    TreeNode*NBrother;

    TreeNode(char ch, TreeNode*F = NULL, TreeNode*N = NULL)
    {
        data = ch;
        FChild = F;
        NBrother = N;
    }
    TreeNode()
    {
        FChild = NBrother = NULL;
    }
} TN, *pTN;


class Tree
{
public:
    Tree() {}
    ~Tree() {}

    void CreateTree();
    void PreOrderRec();//µÝ¹érecursion
    void PreOrderIte();//µü´úiteration
    void PostOrderRec();
    void PostOrderIte();
    void LevelOrder();
private:

    pTN root;
};


class Forest
{
public:
    Forest(int n);
    void CreateForest();
    void PreOrderRec();//µÝ¹érecursion
    void PreOrderIte();//µü´úiteration
    void PostOrderRec();
    void PostOrderIte();
    void LevelOrder();
private:
    Tree *trees;
    int count;
};

#endif // Tree_H_INCLUDED
