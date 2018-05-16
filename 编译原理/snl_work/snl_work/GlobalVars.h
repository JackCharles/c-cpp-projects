#ifndef GLOBALVARS_H_INCLUDED
#define GLOBALVARS_H_INCLUDED
#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
using namespace std;

/* ���峣��FALSEΪ0 */
#ifndef FALSE
#define FALSE 0
#endif

/* ���峣��TRUEΪ1 */
#ifndef TRUE
#define TRUE 1
#endif


/* ���屣������������MAXRESERVEDΪ21 */
#define MAXRESERVED 21


/* MAXTOKENLENΪ������󳤶ȶ���Ϊ40 */
#define MAXTOKENLEN 40

/*��ʼ�����ű��б�����ƫ��*/
#define INITOFF 7

/* SCOPESIZEΪ���ű�scopeջ�Ĵ�С*/
#define SCOPESIZE 1000

/*����token�ĳ���*/
#define TOKENLEN sizeof (TokenType)

/*��������ڵ�ĳ���*/
#define CHAINNODELEN sizeof (TokeNode) 


enum
{
	Program, ProgramHead, ProgramName, DeclarePart, TypeDecpart, TypeDec,
	TypeDecList, TypeDecMore, TypeId, TypeDef, BaseType, StructureType,
	ArrayType, Low, Top, RecType, FieldDecList, FieldDecMore, IdList, IdMore,
	VarDecpart, VarDec, VarDecList, VarDecMore, VarIdList, VarIdMore,
	ProcDecpart, ProcDec, ProcDecMore, ProcName, ParamList, ParamDecList,
	ParamMore, Param, FormList, FidMore, ProcDecPart, ProcBody, ProgramBody,
	StmList, StmMore, Stm, AssCall, AssignmentRest, ConditionalStm,
	LoopStm, InputStm, InVar, OutputStm, ReturnStm, CallStmRest, ActParamList,
	ActParamMore, RelExp, OtherRelE, Exp, OtherTerm, Term, OtherFactor, Factor,
	Variable, VariMore, FieldVar, FieldVarMore, CmpOp, AddOp, MultOp
};//���ռ���67��

typedef enum
{
	//���ǵ��ʷ���
	ENDFILE=67, ERRORX,
	//������
	PROGRAM, PROCEDURE, TYPE, VAR, IF, THEN, ELSE, FI, WHILE, DO, ENDWH, BEGIN, //
	END, READ, WRITE, ARRAY, OF, RECORD, RETURN, INTEGER, CHARX,
	//���ַ����ʷ���
	ID, INTC, CHARC,
	//�������
	ASSIGN/*:=*/, EQ/*=*/, LT/*<*/, PLUS/*+*/, MINUS/*-*/, TIMES/***/, OVER/*/*/,
	LPAREN/*(*/, RPAREN, DOT, COLON/*:*/, SEMI/*;*/, COMMA/*,*/, LMIDPAREN/*[*/,
	RMIDPAREN, UNDERANGE/*..*/, EMPTY/*��*/
}LexType;//�ռ���43��


typedef struct production
{
    int left;
    int *right;
    int rLen;
} PDT;

typedef struct tokenode
{
	int line;
	int lex;
	char sem[20] = {0};
	tokenode* next;
}TOKEN,TokenNode;

void initGrammar(PDT pdt[]);
void initLL1Table(int lt[][110]);

/*�﷨�����ڵ�ProK,����ͷ���PheadK���������ͽڵ�DecK,
��־�ӽ�㶼�����������Ľ��TypeK,��־�ӽ�㶼�Ǳ��������Ľ��VarK,
�����������FuncDecK,������нڵ�StmLK,����������StmtK,
���ʽ���ExpK*/
typedef enum { ProK, PheadK, DecK, TypeK, VarK, ProcDecK, StmLK, StmtK, ExpK }
NodeKind;


/*��������Deckind ���͵�ö�ٶ��壺
��������ArrayK,�ַ�����CharK,
��������IntegerK,��¼����RecordK,
�����ͱ�ʶ����Ϊ���͵�IdK*/
typedef enum { ArrayK, CharK, IntegerK, RecordK, IdK }  DecKind;



/* �������StmtKind���͵�ö�ٶ���:			*
* �ж�����IfK,ѭ������WhileK				*
* ��ֵ����AssignK,������ReadK              *
* д����WriteK��������������CallK          */
typedef enum { IfK, WhileK, AssignK, ReadK, WriteK, CallK, ReturnK } StmtKind;


/* ���ʽ����ExpKind���͵�ö�ٶ���:         *
* ��������OpK,��������ConstK,��������VarK */
typedef enum { OpK, ConstK, VariK } ExpKind;


/* ��������VarKind���͵�ö�ٶ���:           *
* ��ʶ��IdV,�����ԱArrayMembV,���ԱFieldMembV*/
typedef enum { IdV, ArrayMembV, FieldMembV } VarKind;


/* ���ͼ��ExpType���͵�ö�ٶ���:           *
* ��Void,��������Integer,�ַ�����Char      */
typedef enum { Void, Integer, Boolean } ExpType;

/* ��������ParamType���͵�ö�ٶ��壺        *
* ֵ��valparamType,���varparamType        */
typedef enum { valparamType, varparamType } ParamType;

//ʶ�𵥴ʵ�DFA�ļ���״̬��
enum {
	START,//��ʼ״̬��
	INID,//��ʶ��
	INNUM,//����
	DONE,//���״̬
	INASSIGN,//��ֵ״̬
	INCOMMIT,//ע��״̬��
	INRANGE,//�����±����״̬
	INCHAR,//�ַ���־״̬
};

static struct
{
	char*   str;
	LexType tok;
} reservedWords[21]
= { { "program",PROGRAM },{ "type",TYPE },{ "var",VAR },{ "procedure",PROCEDURE }
,{ "begin",BEGIN },{ "end",END },{ "array",ARRAY },{ "of",OF },{ "record",RECORD }
,{ "if",IF },{ "then",THEN },{ "else",ELSE },{ "fi",FI },{ "while",WHILE }
,{ "do",DO },{ "endwh",ENDWH },{ "read",READ },{ "write",WRITE },{ "return",RETURN }
,{ "integer",INTEGER },{ "char",CHARX }};

void ReadFromFile(char *);
bool getTokenlist();
bool isDigit(char);
bool isalpha(char);
bool isalnum(char);
LexType reversedLookup(char *s);
void ChainToList(TokenNode *);
void ungetNextchar();
int getChar();
int getNextchar();

#endif // GLOBALVARS_H_INCLUDED
