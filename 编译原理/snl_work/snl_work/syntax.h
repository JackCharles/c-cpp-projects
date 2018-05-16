#pragma once
#include "GlobalVars.h"

using namespace std;

bool syntaxAnalyze(TOKEN* head, PDT* pdt, int table[][110]);

TOKEN* getTokenFromFile(char* filename);


union NodeKindX
{
    int dec;//��������
    int stmt;//�������
    int exp;//���ʽ����
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
    int op;//������
    int val;//��ֵ
    int varkind;//�������
    int type;//�������
};

struct AttrNode
{
    ArrayAttrNode ArrayAttr;
    ProcAttrNode ProcAttr;
    ExpAttrNode ExpAttr;
	string typeName;   //������,���Ϊ��������,��kindΪ���ͱ�ʾ��ʱ��Ч
};

typedef struct syn_node
{
    syn_node* child[3];//ָ�����﷨�����
    syn_node* brother; //ָ���ֵ��﷨�����
    int lineNo;        //�к�
    int nodeKind;      //�������
    NodeKindX kind;     //����������
    int idNum;         //��ʾ������
    string name[10];      //��ʾ������
    AttrNode attr;      //�﷨��������������
    syn_node()
    {
        for(int i=0;i<3;i++)
            child[i] = NULL;
        brother = NULL;
    }

}SYNODE;



void buildSyntaxTree(int num, TOKEN* p);//�����﷨��,�������ʽ���(�±�)

int Priosity(int op);

void printTree(SYNODE *tree);

void initialOutBuffer();