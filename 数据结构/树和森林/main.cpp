#include <iostream>
#include "forest.h"
using namespace std;




int main()
{
    cout<<"��������ɭ��:"<<endl;

    Tree *T=new Tree();
    T->CreateTree();//������


    //Forest *T=new Forest(3);
    //T->CreateForest();//����ɭ��


    cout<<"�ȸ��ݹ����:";
    T->PreOrderRec();
    cout<<endl<<"�ȸ���������:";
    T->PreOrderIte();
    cout<<endl<<"����ݹ����:";
    T->PostOrderRec();
    cout<<endl<<"�����������:";
    T->PostOrderIte();
    cout<<endl<<"��  ��  ����:";
    T->LevelOrder();
    return 0;
}
