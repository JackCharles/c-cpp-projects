#include <iostream>
#include "forest.h"
using namespace std;




int main()
{
    cout<<"创建树或森林:"<<endl;

    Tree *T=new Tree();
    T->CreateTree();//创建树


    //Forest *T=new Forest(3);
    //T->CreateForest();//创建森林


    cout<<"先根递归遍历:";
    T->PreOrderRec();
    cout<<endl<<"先根迭代遍历:";
    T->PreOrderIte();
    cout<<endl<<"后根递归遍历:";
    T->PostOrderRec();
    cout<<endl<<"后根迭代遍历:";
    T->PostOrderIte();
    cout<<endl<<"层  次  遍历:";
    T->LevelOrder();
    return 0;
}
