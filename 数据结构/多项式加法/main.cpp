#include <iostream>
#include "header.h"
using namespace std;

int main()
{
    SLList*poly1 = new SLList();
    SLList*poly2 = new SLList();

    cout << "�������ʽ1-->" << endl;
    poly1->CreatList();
    cout << "�������ʽ2-->" << endl;
    poly2->CreatList();

    SLNode*pre1 = poly1->head;//poly1��ǰ����ǰ�����
    poly1->cuur = poly1->head->next;
    poly2->cuur = poly2->head->next;

    while(poly1->cuur != NULL && poly2->cuur != NULL)//����������ϵ��
    {
        if(poly1->cuur->zh == poly2->cuur->zh)//����ָ�����
        {
            poly1->cuur->xi = poly1->cuur->xi + poly2->cuur->xi;
            if(poly1->cuur->xi == 0)//ϵ��֮��Ϊ0����ֱ��ɾ��
            {
                pre1->next = poly1->cuur->next;
                delete poly1->cuur;
                poly1->cuur = pre1->next;
            }
            else
            {
                poly1->cuur = poly1->cuur->next;//��Ӻ��һ������ָ�������λ
                pre1 = pre1->next;
            }

            SLNode*p = poly2->cuur;//ֻҪָ�����������������ɾ������2 �Ķ�Ӧ�ڵ�
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

    if(poly1->cuur == NULL && poly2->cuur != NULL) //�������2�����ָ��С������һ����ֱ�ӽ�����2���沿�ֽӵ�����1����
    {
        pre1->next = poly2->cuur;
    }                                              //����2ֻʣ��һ����λ���head,������������������


    cout<<"�����:";
    poly1->OutPut();

    return 0;
}
