#include "stdafx.h"
#include "GlobalVars.h"

int k = 0;
void set(PDT pdt[], int A, int *B, int n)
{
	pdt[k].left = A;
	pdt[k].rLen = n;
	pdt[k].right = new int[n];
	for (int i = 0; i < n; i++)
		pdt[k].right[i] = B[i];
	k++;
}

//初始化104个产生式
void initGrammar(PDT pdt[])
{
	//1~3
	set(pdt, Program, new int[3]{ ProgramHead, DeclarePart, ProgramBody }, 3);
	set(pdt, ProgramHead, new int[2]{ PROGRAM, ProgramName }, 2);
	set(pdt, ProgramName, new int[1]{ ID }, 1);

	//4~11.程序声明，类型声明
	set(pdt, DeclarePart, new int[3]{ TypeDecpart, VarDecpart , ProcDecpart }, 3);
	set(pdt, TypeDecpart, new int[1]{ EMPTY }, 1);
	set(pdt, TypeDecpart, new int[1]{ TypeDec }, 1);
	set(pdt, TypeDec, new int[2]{ TYPE , TypeDecList }, 2);
	set(pdt, TypeDecList, new int[5]{ TypeId, EQ,TypeDef, SEMI, TypeDecMore }, 5);
	set(pdt, TypeDecMore, new int[1]{ EMPTY }, 1);
	set(pdt, TypeDecMore, new int[1]{ TypeDecList }, 1);
	set(pdt, TypeId, new int[1]{ ID }, 1);

	//12~29 类型
	set(pdt, TypeDef, new int[1]{ BaseType }, 1);
	set(pdt, TypeDef, new int[1]{ StructureType }, 1);
	set(pdt, TypeDef, new int[1]{ ID }, 1);
	set(pdt, BaseType, new int[1]{ INTEGER }, 1);
	set(pdt, BaseType, new int[1]{ CHARX }, 1);
	set(pdt, StructureType, new int[1]{ ArrayType }, 1);
	set(pdt, StructureType, new int[1]{ RecType }, 1);
	set(pdt, ArrayType, new int[8]{ ARRAY , LMIDPAREN, Low , UNDERANGE ,Top ,RMIDPAREN , OF , BaseType }, 8);  //有问题
	set(pdt, Low, new int[1]{ INTC }, 1);
	set(pdt, Top, new int[1]{ INTC }, 1);
	set(pdt, RecType, new int[3]{ RECORD, FieldDecList , END }, 3);
	set(pdt, FieldDecList, new int[4]{ BaseType , IdList , SEMI , FieldDecMore }, 4);
	set(pdt, FieldDecList, new int[4]{ ArrayType , IdList , SEMI , FieldDecMore }, 4);
	set(pdt, FieldDecMore, new int[1]{ EMPTY }, 1);
	set(pdt, FieldDecMore, new int[1]{ FieldDecList }, 1);
	set(pdt, IdList, new int[2]{ ID, IdMore }, 2);
	set(pdt, IdMore, new int[1]{ EMPTY }, 1);
	set(pdt, IdMore, new int[2]{ SEMI , IdList }, 1);

	//30~38变量声明
	set(pdt, VarDecpart, new int[1]{ EMPTY }, 1);
	set(pdt, VarDecpart, new int[1]{ VarDec }, 1);
	set(pdt, VarDec, new int[2]{ VAR, VarDecList }, 2);
	set(pdt, VarDecList, new int[4]{ TypeDef, VarIdList , SEMI , VarDecMore }, 4);
	set(pdt, VarDecMore, new int[1]{ EMPTY }, 1);
	set(pdt, VarDecMore, new int[1]{ VarDecList }, 1);
	set(pdt, VarIdList, new int[2]{ ID , VarIdMore }, 2);
	set(pdt, VarIdMore, new int[1]{ EMPTY }, 1);
	set(pdt, VarIdMore, new int[2]{ COMMA , VarIdList }, 2);


	//39~44 过程声明
	set(pdt, ProcDecPart, new int[1]{ EMPTY }, 1);
	set(pdt, ProcDecPart, new int[1]{ ProcDec }, 1);
	set(pdt, ProcDec, new int[9]{ PROCEDURE, ProcName, LPAREN, ParamList,RPAREN,SEMI, ProcDecPart,ProcBody,ProcDecMore }, 9);
	set(pdt, ProcDecMore, new int[1]{ EMPTY }, 1);
	set(pdt, ProcDecMore, new int[1]{ ProcDec }, 1);//书上为procDeclaration
	set(pdt, ProcName, new int[1]{ ID }, 1);

	//45~54 参数声明

	set(pdt, ParamList, new int[1]{ EMPTY }, 1);
	set(pdt, ParamList, new int[1]{ ParamDecList }, 1);
	set(pdt, ParamDecList, new int[2]{ Param,ParamMore }, 2);
	set(pdt, ParamMore, new int[1]{ EMPTY }, 1);
	set(pdt, ParamMore, new int[2]{ SEMI,ParamDecList }, 2);
	set(pdt, Param, new int[2]{ TypeDef, FormList }, 2);
	set(pdt, Param, new int[3]{ VAR,TypeDef , FormList }, 3);
	set(pdt, FormList, new int[2]{ ID, FidMore }, 2);
	set(pdt, FidMore, new int[1]{ EMPTY }, 1);
	set(pdt, FidMore, new int[2]{ COMMA,FormList }, 2);


	//55~68
	set(pdt, ProcDecPart, new int[1]{ DeclarePart }, 1);
	set(pdt, ProcBody, new int[1]{ ProgramBody }, 1);
	set(pdt, ProgramBody, new int[3]{ BEGIN,StmList,END }, 3);
	set(pdt, StmList, new int[2]{ Stm,StmMore }, 2);
	set(pdt, StmMore, new int[1]{ EMPTY }, 1);
	set(pdt, StmMore, new int[2]{ SEMI,StmList }, 2);
	set(pdt, Stm, new int[1]{ ConditionalStm }, 1);
	set(pdt, Stm, new int[1]{ LoopStm }, 1);
	set(pdt, Stm, new int[1]{ InputStm }, 1);
	set(pdt, Stm, new int[1]{ OutputStm }, 1);
	set(pdt, Stm, new int[1]{ ReturnStm }, 1);
	set(pdt, Stm, new int[2]{ ID,AssCall }, 2);
	set(pdt, AssCall, new int[1]{ AssignmentRest }, 1);
	set(pdt, AssCall, new int[1]{ CallStmRest }, 1);

	//69~75 语句2
	set(pdt, AssignmentRest, new int[3]{ VariMore ,ASSIGN, Exp}, 3);
	set(pdt, ConditionalStm, new int[7]{ IF,RelExp,THEN,StmList,ELSE,StmList,FI }, 7);
	set(pdt, LoopStm, new int[5]{ WHILE,RelExp,DO,StmList,ENDWH }, 5);
	set(pdt, InputStm, new  int[4]{ READ,LPAREN,InVar ,RPAREN }, 4);
	set(pdt, InVar, new int[1]{ ID }, 1);
	set(pdt, OutputStm, new int[4]{ WRITE,LPAREN,Exp ,RPAREN }, 4);
	set(pdt, ReturnStm, new int[1]{ RETURN }, 1);


	//76~88 过程调用
	set(pdt, CallStmRest, new int[3]{ LPAREN,ActParamList ,RPAREN }, 3);
	set(pdt, ActParamList, new int[1]{ EMPTY }, 1);
	set(pdt, ActParamList, new int[2]{ Exp,ActParamMore }, 2);
	set(pdt, ActParamMore, new int[1]{ EMPTY }, 1);
	set(pdt, ActParamMore, new int[2]{ COMMA,ActParamList }, 2);
	set(pdt, RelExp, new int[2]{ Exp,OtherRelE }, 2);
	set(pdt, OtherRelE, new int[2]{ CmpOp,Exp }, 2);
	set(pdt, Exp, new int[2]{ Term,OtherTerm }, 2);
	set(pdt, OtherTerm, new int[1]{ EMPTY }, 1);
	set(pdt, OtherTerm, new int[2]{ AddOp,Exp }, 2);
	set(pdt, Term, new int[2]{ Factor,OtherFactor }, 2);
	set(pdt, OtherFactor, new int[1]{ EMPTY }, 1);
	set(pdt, OtherFactor, new int[2]{ MultOp,Term }, 2);

	//89~104 因子
	set(pdt, Factor, new int[3]{ LPAREN,Exp,RPAREN }, 3);
	set(pdt, Factor, new int[1]{ INTC }, 1);
	set(pdt, Factor, new int[1]{ Variable }, 1);
	set(pdt, Variable, new int[2]{ ID , VariMore }, 2);
	set(pdt, VariMore, new int[1]{ EMPTY }, 1);
	set(pdt, VariMore, new int[3]{ LMIDPAREN, Exp,RMIDPAREN }, 3);
	set(pdt, VariMore, new int[2]{ DOT, FieldVar }, 2);
	set(pdt, FieldVar, new int[2]{ ID, FieldVarMore }, 2);
	set(pdt, FieldVarMore, new int[1]{ EMPTY }, 1);
	set(pdt, FieldVarMore, new int[3]{ LMIDPAREN, Exp,RMIDPAREN }, 3);
	set(pdt, CmpOp, new int[1]{ LT }, 1);
	set(pdt, CmpOp, new int[1]{ EQ }, 1);
	set(pdt, AddOp, new int[1]{ PLUS }, 1);
	set(pdt, AddOp, new int[1]{ MINUS }, 1);
	set(pdt, MultOp, new int[1]{ TIMES }, 1);
	set(pdt, MultOp, new int[1]{ OVER }, 1);
}

void initLL1Table(int LL1Table[][110])
{
	LL1Table[Program][PROGRAM] = 1;

	LL1Table[ProgramHead][PROGRAM] = 2;

	LL1Table[ProgramName][ID] = 3;

	LL1Table[DeclarePart][TYPE] = 4;
	LL1Table[DeclarePart][VAR] = 4;
	LL1Table[DeclarePart][PROCEDURE] = 4;
	LL1Table[DeclarePart][BEGIN] = 4;

	LL1Table[TypeDecpart][VAR] = 5;
	LL1Table[TypeDecpart][PROCEDURE] = 5;
	LL1Table[TypeDecpart][BEGIN] = 5;

	LL1Table[TypeDecpart][TYPE] = 6;

	LL1Table[TypeDec][TYPE] = 7;

	LL1Table[TypeDecList][ID] = 8;

	LL1Table[TypeDecMore][VAR] = 9;
	LL1Table[TypeDecMore][PROCEDURE] = 9;
	LL1Table[TypeDecMore][BEGIN] = 9;


	LL1Table[TypeDecMore][ID] = 10;

	LL1Table[TypeId][ID] = 11;

	LL1Table[TypeDef][INTEGER] = 12;
	LL1Table[TypeDef][CHARX] = 12;

	LL1Table[TypeDef][ARRAY] = 13;
	LL1Table[TypeDef][RECORD] = 13;

	LL1Table[TypeDef][ID] = 14;

	LL1Table[BaseType][INTEGER] = 15;

	LL1Table[BaseType][CHARX] = 16;

	LL1Table[StructureType][ARRAY] = 17;

	LL1Table[StructureType][RECORD] = 18;

	LL1Table[ArrayType][ARRAY] = 19;

	LL1Table[Low][INTC] = 20;

	LL1Table[Top][INTC] = 21;

	LL1Table[RecType][RECORD] = 22;

	LL1Table[FieldDecList][INTEGER] = 23;
	LL1Table[FieldDecList][CHARX] = 23;

	LL1Table[FieldDecList][ARRAY] = 24;

	LL1Table[FieldDecMore][END] = 25;

	LL1Table[FieldDecMore][INTEGER] = 26;
	LL1Table[FieldDecMore][CHARX] = 26;
	LL1Table[FieldDecMore][ARRAY] = 26;

	LL1Table[IdList][ID] = 27;

	LL1Table[IdMore][SEMI] = 28;

	LL1Table[IdMore][COMMA] = 29;

	LL1Table[VarDecpart][PROCEDURE] = 30;
	LL1Table[VarDecpart][BEGIN] = 30;

	LL1Table[VarDecpart][VAR] = 31;

	LL1Table[VarDec][VAR] = 32;

	LL1Table[VarDecList][INTEGER] = 33;
	LL1Table[VarDecList][CHARX] = 33;
	LL1Table[VarDecList][ARRAY] = 33;
	LL1Table[VarDecList][RECORD] = 33;
	LL1Table[VarDecList][ID] = 33;

	LL1Table[VarDecMore][PROCEDURE] = 34;
	LL1Table[VarDecMore][BEGIN] = 34;


	LL1Table[VarDecMore][INTEGER] = 35;
	LL1Table[VarDecMore][CHARX] = 35;
	LL1Table[VarDecMore][ARRAY] = 35;
	LL1Table[VarDecMore][RECORD] = 35;
	LL1Table[VarDecMore][ID] = 35;

	LL1Table[VarIdList][ID] = 36;

	LL1Table[VarIdMore][SEMI] = 37;

	LL1Table[VarIdMore][COMMA] = 38;

	LL1Table[ProcDecpart][BEGIN] = 39;

	LL1Table[ProcDecpart][PROCEDURE] = 40;

	LL1Table[ProcDec][PROCEDURE] = 41;

	LL1Table[ProcDecMore][BEGIN] = 42;

	LL1Table[ProcDecMore][PROCEDURE] = 43;

	LL1Table[ProcName][ID] = 44;

	LL1Table[ParamList][RPAREN] = 45;

	LL1Table[ParamList][INTEGER] = 46;
	LL1Table[ParamList][CHARX] = 46;
	LL1Table[ParamList][ARRAY] = 46;
	LL1Table[ParamList][RECORD] = 46;
	LL1Table[ParamList][ID] = 46;
	LL1Table[ParamList][VAR] = 46;

	LL1Table[ParamDecList][INTEGER] = 47;
	LL1Table[ParamDecList][CHARX] = 47;
	LL1Table[ParamDecList][ARRAY] = 47;
	LL1Table[ParamDecList][RECORD] = 47;
	LL1Table[ParamDecList][ID] = 47;
	LL1Table[ParamDecList][VAR] = 47;

	LL1Table[ParamMore][RPAREN] = 48;

	LL1Table[ParamMore][SEMI] = 49;

	LL1Table[Param][INTEGER] = 50;
	LL1Table[Param][CHARX] = 50;
	LL1Table[Param][ARRAY] = 50;
	LL1Table[Param][RECORD] = 50;
	LL1Table[Param][ID] = 50;

	LL1Table[Param][VAR] = 51;

	LL1Table[FormList][ID] = 52;

	LL1Table[FidMore][SEMI] = 53;
	LL1Table[FidMore][RPAREN] = 53;

	LL1Table[FidMore][COMMA] = 54;

	LL1Table[ProcDecPart][TYPE] = 55;
	LL1Table[ProcDecPart][VAR] = 55;
	LL1Table[ProcDecPart][PROCEDURE] = 55;
	LL1Table[ProcDecPart][BEGIN] = 55;

	LL1Table[ProcBody][BEGIN] = 56;

	LL1Table[ProgramBody][BEGIN] = 57;

	LL1Table[StmList][ID] = 58;
	LL1Table[StmList][IF] = 58;
	LL1Table[StmList][WHILE] = 58;
	LL1Table[StmList][RETURN] = 58;
	LL1Table[StmList][READ] = 58;
	LL1Table[StmList][WRITE] = 58;

	LL1Table[StmMore][END] = 59;
	LL1Table[StmMore][ENDWH] = 59;
	LL1Table[StmMore][ELSE] = 59;
	LL1Table[StmMore][FI] = 59;

	LL1Table[StmMore][SEMI] = 60;

	LL1Table[Stm][IF] = 61;

	LL1Table[Stm][WHILE] = 62;

	LL1Table[Stm][READ] = 63;

	LL1Table[Stm][WRITE] = 64;

	LL1Table[Stm][RETURN] = 65;

	LL1Table[Stm][ID] = 66;

	LL1Table[AssCall][ASSIGN] = 67;
	LL1Table[AssCall][LMIDPAREN] = 67;
	LL1Table[AssCall][DOT] = 67;


	LL1Table[AssCall][LPAREN] = 68;

	LL1Table[AssignmentRest][ASSIGN] = 69;
	LL1Table[AssignmentRest][LMIDPAREN] = 69;
	LL1Table[AssignmentRest][DOT] = 69;

	LL1Table[ConditionalStm][IF] = 70;


	LL1Table[LoopStm][WHILE] = 71;

	LL1Table[InputStm][READ] = 72;

	LL1Table[InVar][ID] = 73;

	LL1Table[OutputStm][WRITE] = 74;

	LL1Table[ReturnStm][RETURN] = 75;

	LL1Table[CallStmRest][LPAREN] = 76;

	LL1Table[ActParamList][RPAREN] = 77;

	LL1Table[ActParamList][ID] = 78;
	LL1Table[ActParamList][INTC] = 78;
	LL1Table[ActParamList][LPAREN] = 78;

	LL1Table[ActParamMore][RPAREN] = 79;

	LL1Table[ActParamMore][COMMA] = 80;

	LL1Table[RelExp][LPAREN] = 81;
	LL1Table[RelExp][INTC] = 81;
	LL1Table[RelExp][ID] = 81;

	LL1Table[OtherRelE][LT] = 82;
	LL1Table[OtherRelE][EQ] = 82;

	LL1Table[Exp][LPAREN] = 83;
	LL1Table[Exp][INTC] = 83;
	LL1Table[Exp][ID] = 83;

	LL1Table[OtherTerm][LT] = 84;
	LL1Table[OtherTerm][EQ] = 84;
	LL1Table[OtherTerm][THEN] = 84;
	LL1Table[OtherTerm][DO] = 84;
	LL1Table[OtherTerm][RPAREN] = 84;
	LL1Table[OtherTerm][END] = 84;
	LL1Table[OtherTerm][SEMI] = 84;
	LL1Table[OtherTerm][COMMA] = 84;
	LL1Table[OtherTerm][ENDWH] = 84;
	LL1Table[OtherTerm][ELSE] = 84;
	LL1Table[OtherTerm][FI] = 84;
	LL1Table[OtherTerm][RMIDPAREN] = 84;


	LL1Table[OtherTerm][PLUS] = 85;
	LL1Table[OtherTerm][MINUS] = 85;

	LL1Table[Term][LPAREN] = 86;
	LL1Table[Term][INTC] = 86;
	LL1Table[Term][ID] = 86;

	LL1Table[OtherFactor][PLUS] = 87;
	LL1Table[OtherFactor][MINUS] = 87;
	LL1Table[OtherFactor][LT] = 87;
	LL1Table[OtherFactor][EQ] = 87;
	LL1Table[OtherFactor][THEN] = 87;
	LL1Table[OtherFactor][ELSE] = 87;
	LL1Table[OtherFactor][FI] = 87;
	LL1Table[OtherFactor][DO] = 87;
	LL1Table[OtherFactor][ENDWH] = 87;
	LL1Table[OtherFactor][RPAREN] = 87;
	LL1Table[OtherFactor][END] = 87;
	LL1Table[OtherFactor][SEMI] = 87;
	LL1Table[OtherFactor][COMMA] = 87;
	LL1Table[OtherFactor][RMIDPAREN] = 87;

	LL1Table[OtherFactor][TIMES] = 88;
	LL1Table[OtherFactor][OVER] = 88;

	LL1Table[Factor][LPAREN] = 89;

	LL1Table[Factor][INTC] = 90;

	LL1Table[Factor][ID] = 91;

	LL1Table[Variable][ID] = 92;

	LL1Table[VariMore][ASSIGN] = 93;
	LL1Table[VariMore][TIMES] = 93;
	LL1Table[VariMore][OVER] = 93;
	LL1Table[VariMore][PLUS] = 93;
	LL1Table[VariMore][MINUS] = 93;
	LL1Table[VariMore][LT] = 93;
	LL1Table[VariMore][EQ] = 93;
	LL1Table[VariMore][THEN] = 93;
	LL1Table[VariMore][ELSE] = 93;
	LL1Table[VariMore][FI] = 93;
	LL1Table[VariMore][DO] = 93;
	LL1Table[VariMore][ENDWH] = 93;
	LL1Table[VariMore][RPAREN] = 93;
	LL1Table[VariMore][END] = 93;
	LL1Table[VariMore][SEMI] = 93;
	LL1Table[VariMore][COMMA] = 93;
	LL1Table[VariMore][RMIDPAREN] = 93;

	LL1Table[VariMore][LMIDPAREN] = 94;

	LL1Table[VariMore][DOT] = 95;

	LL1Table[FieldVar][ID] = 96;

	LL1Table[FieldVarMore][ASSIGN] = 97;
	LL1Table[FieldVarMore][TIMES] = 97;
	LL1Table[FieldVarMore][OVER] = 97;
	LL1Table[FieldVarMore][PLUS] = 97;
	LL1Table[FieldVarMore][MINUS] = 97;
	LL1Table[FieldVarMore][LT] = 97;
	LL1Table[FieldVarMore][EQ] = 97;
	LL1Table[FieldVarMore][THEN] = 97;
	LL1Table[FieldVarMore][ELSE] = 97;
	LL1Table[FieldVarMore][FI] = 97;
	LL1Table[FieldVarMore][DO] = 97;
	LL1Table[FieldVarMore][ENDWH] = 97;
	LL1Table[FieldVarMore][RPAREN] = 97;
	LL1Table[FieldVarMore][END] = 97;
	LL1Table[FieldVarMore][SEMI] = 97;
	LL1Table[FieldVarMore][COMMA] = 97;

	LL1Table[FieldVarMore][LMIDPAREN] = 98;

	LL1Table[CmpOp][LT] = 99;

	LL1Table[CmpOp][EQ] = 100;

	LL1Table[AddOp][PLUS] = 101;

	LL1Table[AddOp][MINUS] = 102;

	LL1Table[MultOp][TIMES] = 103;

	LL1Table[MultOp][OVER] = 104;
}
