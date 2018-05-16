#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

struct SLNode
{
    int data;
    struct SLNode* next;
    SLNode(SLNode*nextNode = NULL)
    {
        next = nextNode;
    }
    SLNode(int item, SLNode*nextNode = NULL)
    {
        data = item;
        next = nextNode;
    }
};


class SLList
{
public:
    SLList();
    ~SLList();

    void CreatList();
    bool Find(int& item);
    void Search();
    void Delete(int&item);
    void Insert();
    void OutPut();

private:
    int size;
    SLNode*head;
    SLNode*rear;
    SLNode*cuur;//µ±«∞÷∏’Î
};


#endif // HEADER_H_INCLUDED
