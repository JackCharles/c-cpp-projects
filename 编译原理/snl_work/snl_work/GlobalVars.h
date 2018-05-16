#ifndef GLOBALVARS_H_INCLUDED
#define GLOBALVARS_H_INCLUDED
#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
using namespace std;

/* 定义常量FALSE为0 */
#ifndef FALSE
#define FALSE 0
#endif

/* 定义常量TRUE为1 */
#ifndef TRUE
#define TRUE 1
#endif


/* 定义保留字数量常量MAXRESERVED为21 */
#define MAXRESERVED 21


/* MAXTOKENLEN为单词最大长度定义为40 */
#define MAXTOKENLEN 40

/*初始化符号表中变量的偏移*/
#define INITOFF 7

/* SCOPESIZE为符号表scope栈的大小*/
#define SCOPESIZE 1000

/*定义token的长度*/
#define TOKENLEN sizeof (TokenType)

/*定义链表节点的长度*/
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
};//非终极符67个

typedef enum
{
	//簿记单词符号
	ENDFILE=67, ERRORX,
	//保留字
	PROGRAM, PROCEDURE, TYPE, VAR, IF, THEN, ELSE, FI, WHILE, DO, ENDWH, BEGIN, //
	END, READ, WRITE, ARRAY, OF, RECORD, RETURN, INTEGER, CHARX,
	//多字符单词符号
	ID, INTC, CHARC,
	//特殊符号
	ASSIGN/*:=*/, EQ/*=*/, LT/*<*/, PLUS/*+*/, MINUS/*-*/, TIMES/***/, OVER/*/*/,
	LPAREN/*(*/, RPAREN, DOT, COLON/*:*/, SEMI/*;*/, COMMA/*,*/, LMIDPAREN/*[*/,
	RMIDPAREN, UNDERANGE/*..*/, EMPTY/*空*/
}LexType;//终极符43个


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

/*语法树根节点ProK,程序头结点PheadK，声明类型节点DecK,
标志子结点都是类型声明的结点TypeK,标志子结点都是变量声明的结点VarK,
函数声明结点FuncDecK,语句序列节点StmLK,语句声明结点StmtK,
表达式结点ExpK*/
typedef enum { ProK, PheadK, DecK, TypeK, VarK, ProcDecK, StmLK, StmtK, ExpK }
NodeKind;


/*声明类型Deckind 类型的枚举定义：
数组类型ArrayK,字符类型CharK,
整数类型IntegerK,记录类型RecordK,
以类型标识符作为类型的IdK*/
typedef enum { ArrayK, CharK, IntegerK, RecordK, IdK }  DecKind;



/* 语句类型StmtKind类型的枚举定义:			*
* 判断类型IfK,循环类型WhileK				*
* 赋值类型AssignK,读类型ReadK              *
* 写类型WriteK，函数调用类型CallK          */
typedef enum { IfK, WhileK, AssignK, ReadK, WriteK, CallK, ReturnK } StmtKind;


/* 表达式类型ExpKind类型的枚举定义:         *
* 操作类型OpK,常数类型ConstK,变量类型VarK */
typedef enum { OpK, ConstK, VariK } ExpKind;


/* 变量类型VarKind类型的枚举定义:           *
* 标识符IdV,数组成员ArrayMembV,域成员FieldMembV*/
typedef enum { IdV, ArrayMembV, FieldMembV } VarKind;


/* 类型检查ExpType类型的枚举定义:           *
* 空Void,整数类型Integer,字符类型Char      */
typedef enum { Void, Integer, Boolean } ExpType;

/* 参数类型ParamType类型的枚举定义：        *
* 值参valparamType,变参varparamType        */
typedef enum { valparamType, varparamType } ParamType;

//识别单词的DFA的几个状态；
enum {
	START,//开始状态；
	INID,//标识符
	INNUM,//数字
	DONE,//完成状态
	INASSIGN,//赋值状态
	INCOMMIT,//注释状态；
	INRANGE,//数组下标界限状态
	INCHAR,//字符标志状态
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
