#include <iostream>
#include "header.h"
using namespace std;

int main()
{
    SLList*poly1 = new SLList();
    SLList*poly2 = new SLList();

    cout << "输入多项式1-->" << endl;
    poly1->CreatList();
    cout << "输入多项式2-->" << endl;
    poly2->CreatList();

    SLNode*pre1 = poly1->head;//poly1当前结点的前驱结点
    poly1->cuur = poly1->head->next;
    poly2->cuur = poly2->head->next;

    while(poly1->cuur != NULL && poly2->cuur != NULL)//遍历链表处理系数
    {
        if(poly1->cuur->zh == poly2->cuur->zh)//两项指数相等
        {
            poly1->cuur->xi = poly1->cuur->xi + poly2->cuur->xi;
            if(poly1->cuur->xi == 0)//系数之和为0的项直接删除
            {
                pre1->next = poly1->cuur->next;
                delete poly1->cuur;
                poly1->cuur = pre1->next;
            }
            else
            {
                poly1->cuur = poly1->cuur->next;//相加后第一个链表指针向后移位
                pre1 = pre1->next;
            }

            SLNode*p = poly2->cuur;//只要指数相等无论怎样都会删除链表2 的对应节点
            poly2->cuur = poly2->cuur->next;
            delete p;

        }
        else if(poly1->cuur->zh > poly2->cuur->zh)
        {
            poly1->cuur = poly1->cuur->next;
            pre1 = pre1->next;
        }
        else
        {
            SLNode*p = poly2->cuur->next;
            poly2->cuur->next = poly1->cuur;
            pre1->next = poly2->cuur;
            pre1 = poly2->cuur;
            poly2->cuur = p;
        }
    }

    if(poly1->cuur == NULL && poly2->cuur != NULL) //如果链表2后面的指数小于链表一，则直接将链表2后面部分接到链表1后面
    {
        pre1->next = poly2->cuur;
    }                                              //链表2只剩下一个哨位结点head,在析构函数中析构掉


    cout<<"结果是:";
    poly1->OutPut();

    return 0;
}
