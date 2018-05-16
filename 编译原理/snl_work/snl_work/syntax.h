#pragma once
#include "GlobalVars.h"

using namespace std;

bool syntaxAnalyze(TOKEN* head, PDT* pdt, int table[][110]);

TOKEN* getTokenFromFile(char* filename);


union NodeKindX
{
    int dec;//声明类型
    int stmt;//语句类型
    int exp;//表达式类型
};

struct ArrayAttrNode
{
    int low;
    int up;
    int childType;
};

struct ProcAttrNode
{
    int paramt;
};

struct ExpAttrNode
{
    int op;//操作符
    int val;//数值
    int varkind;//变量类别
    int type;//检查类型
};

struct AttrNode
{
    ArrayAttrNode ArrayAttr;
    ProcAttrNode ProcAttr;
    ExpAttrNode ExpAttr;
	string typeName;   //类型名,结点为声明类型,且kind为类型标示符时有效
};

typedef struct syn_node
{
    syn_node* child[3];//指向子语法树结点
    syn_node* brother; //指向兄弟语法树结点
    int lineNo;        //行号
    int nodeKind;      //结点类型
    NodeKindX kind;     //结点具体类型
    int idNum;         //标示符个数
    string name[10];      //标示符名称
    AttrNode attr;      //语法树结点的其他属性
    syn_node()
    {
        for(int i=0;i<3;i++)
            child[i] = NULL;
        brother = NULL;
    }

}SYNODE;



void buildSyntaxTree(int num, TOKEN* p);//构造语法树,传入产生式编号(下标)

int Priosity(int op);

void printTree(SYNODE *tree);

void initialOutBuffer();