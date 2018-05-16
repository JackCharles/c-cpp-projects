#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

struct SLNode
{
    int xi;
    int zh;
    struct SLNode* next;
    SLNode(SLNode*nextNode = NULL)
    {
        next = nextNode;
    }
    SLNode(int xis, int zhs, SLNode*nextNode = NULL)
    {
        xi = xis;
        zh = zhs;
        next = nextNode;
    }
};


class SLList
{
public:
    SLList();
    ~SLList();

    void CreatList();
    //bool Find(int& item);
    //void Search();
    //void Delete(int&item);
    //void Insert();
    void OutPut();
public:
    int size;
    SLNode*head;
    SLNode*rear;
    SLNode*cuur;//µ±«∞÷∏’Î
};


#endif // HEADER_H_INCLUDED
