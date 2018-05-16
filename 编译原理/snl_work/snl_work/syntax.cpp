#include "stdafx.h"
#include "syntax.h"

SYNODE* root = new SYNODE();//语法树根
stack<SYNODE**> treeStack;//语法树栈，用于保存3个孩子节点和兄弟结点的地址
stack<SYNODE*> opStack;//运算符栈
stack<SYNODE*> numStack;//运算数栈
SYNODE* curp = NULL;//当前节点
SYNODE* savep = NULL;
int *temp = NULL;
bool getExpResult = true;
int  getExpResult2 = false;
int  expflag = 0;

bool syntaxAnalyze(TOKEN * head, PDT * pdt, int table[][110])
{
	/*TODO: 初始化root和treeStack*/
	root->nodeKind = ProK;
	root->lineNo = head->line;
	treeStack.push(&(root->child[2]));
	treeStack.push(&(root->child[1]));
	treeStack.push(&(root->child[0]));//注意压栈顺序

	//LL1分析
	stack<int> s;
	s.push(DOT);
	s.push(Program);

	TOKEN* p = head;
	CString text = "";
	CString temp;
	while (!s.empty() && p != NULL)
	{
		int top = s.top();
		s.pop();

		temp.Format("%-3d  ", p->line);
		text.Append(temp);
		temp.Format("%-3d  ", top);
		text.Append(temp);
		temp.Format("%-3d  ", p->lex);
		text.Append(temp);
		
		if (top < 67)//非终极符
		{
			int n = table[top][p->lex] - 1;//产生式n查表s

			temp.Format("T[%-2d][%-3d] = %d\r\n", top, p->lex, n + 1);
			text.Append(temp);
			//构造语法树
			buildSyntaxTree(n, p);
			if (n == -1)
			{
				temp.Format("在第 %d 行发现语法错误，\r\n%s 不是期望的Token。\r\n语法分析终止...",p->line,p->sem);
				text.Append(temp);
				synbox.SetWindowText(text);
				treebox.SetWindowText("语法分析出错，请检查...");
				return false;
			}
			for (int i = pdt[n].rLen - 1; i >= 0; i--)//逆序压栈s！
				if (pdt[n].right[i] != EMPTY)
					s.push(pdt[n].right[i]);
		}
		else//栈顶是终极符
		{
			if (top != p->lex)
			{
				temp.Format("\r\n在第 %d 行发现语法错误，\r\n%s 不是期望的Token。\r\n语法分析终止...", p->line, p->sem);
				text.Append(temp);
				synbox.SetWindowText(text);
				treebox.SetWindowText("语法分析出错，请检查...");
				return false;
			}
			temp.Format("Match[%s]\r\n", p->sem);
			text.Append(temp);
			p = p->next;
		}
		synbox.SetWindowText(text);
	}

	if (s.empty() && p->lex == ENDFILE)
	{
		text.Append("语法分析完成，没有错误。");
		synbox.SetWindowText(text);
		printTree(root);
		return true;
	}
	else
	{
		text.Append("语法错误,未发现有效的文件结束符。");
		synbox.SetWindowText(text);
		treebox.SetWindowText("语法分析出错，请检查...");
		return false;
	}
}

TOKEN * getTokenFromFile(char * filename)
{
	fstream file(filename, ios::in);
	if (!file)
	{
		synbox.SetWindowText("打开文件失败。");
		return NULL;
	}
	TOKEN* head = NULL, *rear = NULL;
	while (!file.eof())
	{

		TOKEN* p = new TOKEN();
		file >> p->line >> p->lex >> p->sem;
		p->next = NULL;

		if (head == NULL)
			head = rear = p;
		else
		{
			rear->next = p;
			rear = rear->next;
		}
	}
	file.close();
	return head;
}


void buildSyntaxTree(int index, TOKEN* token)
{
	switch (index + 1)
	{
		case 2:
		{
			SYNODE** t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = PheadK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			*t = curp;
			break;
		}
		case 3:
		{
			curp->name[0] = token->sem;
			curp->idNum++;
			break;
		}
		case 7:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = TypeK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			*t = curp;
			treeStack.push(&(curp->brother));
			treeStack.push(&(curp->child[0]));
			break;
		}
		case 8:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = DecK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			*t = curp;
			treeStack.push(&(curp->brother));
			break;
		}
		case 9:
		{
			treeStack.pop();
			break;
		}
		case 11:
		{
			curp->name[0] = token->sem;
			curp->idNum++;
			break;
		}
		case 12:
		{
			temp = &(curp->kind.dec);
			break;
		}
		case 14:
		{
			curp->kind.dec = IdK;
			curp->attr.typeName = token->sem;
			break;
		}
		case 15:
		{
			*temp = IntegerK;
			break;
		}
		case 16:
		{
			*temp = CharK;
			break;
		}
		case 19:
		{
			curp->kind.dec = ArrayK;
			temp = &(curp->attr.ArrayAttr.childType);
			break;
		}
		case 20:
		{
			curp->attr.ArrayAttr.low = atoi(token->sem);
			break;
		}
		case 21:
		{
			curp->attr.ArrayAttr.up = atoi(token->sem);
			break;
		}
		case 22:
		{
			curp->kind.dec = RecordK;
			savep = curp;
			treeStack.push(&(curp->child[0]));
			break;
		}
		case 23:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = DecK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			temp = &(curp->kind.dec);
			*t = curp;
			treeStack.push(&(curp->brother));
			break;
		}
		case 24:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = DecK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			*t = curp;
			treeStack.push(&(curp->brother));
			break;
		}
		case 25:
		{
			treeStack.pop();
			curp = savep;
			break;
		}
		case 27:
		{
			curp->name[curp->idNum] = token->sem;
			curp->idNum++;
			break;
		}
		case 32:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = VarK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			*t = curp;
			treeStack.push(&(curp->brother));
			treeStack.push(&(curp->child[0]));
			break;
		}
		case 33:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = DecK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			*t = curp;
			treeStack.push(&(curp->brother));
			break;
		}
		case 34:
		{
			treeStack.pop();
			break;
		}
		case 36:
		{
			curp->name[curp->idNum] = token->sem;
			curp->idNum++;
			break;
		}
		case 41:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = ProcDecK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			*t = curp;
			treeStack.push(&(curp->brother));
			treeStack.push(&(curp->child[2]));
			treeStack.push(&(curp->child[1]));
			treeStack.push(&(curp->child[0]));
			break;
		}
		case 44:
		{
			curp->name[0] = token->sem;
			curp->idNum++;
			break;
		}
		case 45:
		{
			treeStack.pop();
			break;
		}
		case 48:
		{
			treeStack.pop();
			break;
		}
		case 50:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = DecK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->attr.ProcAttr.paramt = valparamType;
			*t = curp;
			treeStack.push(&(curp->brother));
			break;
		}
		case 51:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = DecK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->attr.ProcAttr.paramt = varparamType;
			*t = curp;
			treeStack.push(&(curp->brother));
			break;
		}
		case 52:
		{
			curp->name[curp->idNum] = token->sem;
			curp->idNum++;
			break;
		}
		case 57:
		{
			treeStack.pop();
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = StmLK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			*t = curp;
			treeStack.push(&(curp->child[0]));
			break;
		}
		case 59:
		{
			treeStack.pop();
			break;
		}
		case 61:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = StmtK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->kind.stmt = IfK;
			*t = curp;
			treeStack.push(&(curp->brother));
			break;
		}
		case 62:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = StmtK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->kind.stmt = WhileK;
			*t = curp;
			treeStack.push(&(curp->brother));
			break;
		}
		case 63:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = StmtK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->kind.stmt = ReadK;
			*t = curp;
			treeStack.push(&(curp->brother));
			break;
		}
		case 64:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = StmtK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->kind.stmt = WriteK;
			*t = curp;
			treeStack.push(&(curp->brother));
			break;
		}
		case 65:
		{
			SYNODE**t = treeStack.top();
			treeStack.pop();
			curp = new SYNODE();
			curp->nodeKind = StmtK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->kind.stmt = ReturnK;
			*t = curp;
			treeStack.push(&(curp->brother));
			break;
		}
		case 66:
		{
			curp = new SYNODE();
			curp->nodeKind = StmtK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->kind.stmt = AssignK;

			SYNODE*t1 = new SYNODE();
			t1->nodeKind = ExpK;
			t1->lineNo = token->line;
			t1->idNum = 0;
			t1->kind.exp = VariK;
			t1->attr.ExpAttr.varkind = IdV;
			t1->attr.ExpAttr.type = Void;
			t1->name[0] = token->sem;
			t1->idNum++;

			curp->child[0] = t1;

			SYNODE**t = treeStack.top();
			treeStack.pop();
			*t = curp;
			treeStack.push(&(curp->brother));
			break;
		}
		case 67:
		{
			curp->kind.stmt = AssignK;
			break;
		}
		case 68:
		{
			curp->child[0]->attr.ExpAttr.varkind = IdV;
			curp->kind.stmt = CallK;
			break;
		}
		case 69:
		{
			treeStack.push(&(curp->child[1]));
			curp = curp->child[0];
			SYNODE*t1 = new SYNODE();
			t1->nodeKind = ExpK;
			t1->lineNo = token->line;
			t1->idNum = 0;
			t1->kind.exp = OpK;
			t1->attr.ExpAttr.varkind = IdV;
			t1->attr.ExpAttr.type = Void;
			t1->attr.ExpAttr.op = END;
			opStack.push(t1);
			break;
		}
		case 70:
		{
			treeStack.push(&(curp->child[2]));
			treeStack.push(&(curp->child[1]));
			treeStack.push(&(curp->child[0]));
			break;
		}
		case 71:
		{
			treeStack.push(&(curp->child[1]));
			treeStack.push(&(curp->child[0]));
			break;
		}
		case 73:
		{
			curp->name[0] = token->sem;
			curp->idNum++;
			break;
		}
		case 74:
		{
			treeStack.push(&(curp->child[0]));
			SYNODE*t1 = new SYNODE();
			t1->nodeKind = ExpK;
			t1->lineNo = token->line;
			t1->idNum = 0;
			t1->kind.exp = OpK;
			t1->attr.ExpAttr.varkind = IdV;
			t1->attr.ExpAttr.type = Void;
			t1->attr.ExpAttr.op = END;
			opStack.push(t1);
			break;
		}
		case 76:
		{
			treeStack.push(&(curp->child[1]));
			break;
		}
		case 77:
		{
			treeStack.pop();
			break;
		}
		case 78:
		{
			SYNODE*t1 = new SYNODE();
			t1->nodeKind = ExpK;
			t1->lineNo = token->line;
			t1->idNum = 0;
			t1->kind.exp = OpK;
			t1->attr.ExpAttr.varkind = IdV;
			t1->attr.ExpAttr.type = Void;
			t1->attr.ExpAttr.op = END;
			opStack.push(t1);
			break;
		}
		case 80:
		{
			treeStack.push(&(curp->brother));
			break;
		}
		case 81:
		{
			SYNODE*t1 = new SYNODE();
			t1->nodeKind = ExpK;
			t1->lineNo = token->line;
			t1->idNum = 0;
			t1->kind.exp = OpK;
			t1->attr.ExpAttr.varkind = IdV;
			t1->attr.ExpAttr.type = Void;
			t1->attr.ExpAttr.op = END;
			opStack.push(t1);
			getExpResult = false;
			break;
		}
		case 82:
		{
			SYNODE*curp = new SYNODE();
			curp->nodeKind = ExpK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->kind.exp = OpK;
			curp->attr.ExpAttr.varkind = IdV;
			curp->attr.ExpAttr.type = Void;
			curp->attr.ExpAttr.op = token->lex;

			int optop = opStack.top()->attr.ExpAttr.op;
			while (Priosity(optop) >= Priosity(token->lex))
			{
				SYNODE* t = opStack.top();
				opStack.pop();
				SYNODE* r = numStack.top();
				numStack.pop();
				SYNODE* l = numStack.top();
				numStack.pop();
				t->child[1] = r;
				t->child[0] = l;
				numStack.push(t);

				optop = opStack.top()->attr.ExpAttr.op;
			}
			opStack.push(curp);
			getExpResult = true;
			break;
		}
		case 84:
		{
			if (token->lex == RPAREN&&expflag != 0)
			{
				while (opStack.top()->attr.ExpAttr.op != LPAREN)
				{
					SYNODE* t = opStack.top();
					opStack.pop();
					SYNODE* r = numStack.top();
					numStack.pop();
					SYNODE* l = numStack.top();
					numStack.pop();
					t->child[1] = r;
					t->child[0] = l;
					numStack.push(t);
				}
				opStack.pop();
				expflag--;
			}
			else
			{
				if (getExpResult || getExpResult2)
				{
					while (opStack.top()->attr.ExpAttr.op != END)
					{
						SYNODE* t = opStack.top();
						opStack.pop();
						SYNODE* r = numStack.top();
						numStack.pop();
						SYNODE* l = numStack.top();
						numStack.pop();
						t->child[1] = r;
						t->child[0] = l;
						numStack.push(t);
					}
					opStack.pop();
					curp = numStack.top();
					numStack.pop();

					SYNODE**t = treeStack.top();
					treeStack.pop();
					*t = curp;
					if (getExpResult2 == true)
						getExpResult2 = false;
				}
			}

			break;
		}
		case 85:
		{
			SYNODE*curp = new SYNODE();
			curp->nodeKind = ExpK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->kind.exp = OpK;
			curp->attr.ExpAttr.varkind = IdV;
			curp->attr.ExpAttr.type = Void;
			curp->attr.ExpAttr.op = token->lex;

			int optop = opStack.top()->attr.ExpAttr.op;
			while (Priosity(optop) >= Priosity(token->lex))
			{
				SYNODE* t = opStack.top();
				opStack.pop();
				SYNODE* r = numStack.top();
				numStack.pop();
				SYNODE* l = numStack.top();
				numStack.pop();
				t->child[1] = r;
				t->child[0] = l;
				numStack.push(t);

				optop = opStack.top()->attr.ExpAttr.op;
			}
			opStack.push(curp);
			break;
		}
		case 88:
		{
			SYNODE*curp = new SYNODE();
			curp->nodeKind = ExpK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->kind.exp = OpK;
			curp->attr.ExpAttr.varkind = IdV;
			curp->attr.ExpAttr.type = Void;
			curp->attr.ExpAttr.op = token->lex;

			int optop = opStack.top()->attr.ExpAttr.op;
			while (Priosity(optop) >= Priosity(token->lex))
			{
				SYNODE* t = opStack.top();
				opStack.pop();
				SYNODE* r = numStack.top();
				numStack.pop();
				SYNODE* l = numStack.top();
				numStack.pop();
				t->child[1] = r;
				t->child[0] = l;
				numStack.push(t);

				optop = opStack.top()->attr.ExpAttr.op;
			}
			opStack.push(curp);
			break;
		}
		case 89:
		{
			SYNODE*t = new SYNODE();
			t->nodeKind = ExpK;
			t->lineNo = token->line;
			t->idNum = 0;
			t->kind.exp = OpK;
			t->attr.ExpAttr.varkind = IdV;
			t->attr.ExpAttr.type = Void;
			t->attr.ExpAttr.op = token->lex;
			opStack.push(t);
			expflag++;
			break;
		}
		case 90:
		{
			SYNODE*t = new SYNODE();
			t->nodeKind = ExpK;
			t->lineNo = token->line;
			t->idNum = 0;
			t->kind.exp = ConstK;
			t->attr.ExpAttr.varkind = IdV;
			t->attr.ExpAttr.type = Void;
			t->attr.ExpAttr.val = atoi(token->sem);
			numStack.push(t);
			break;
		}
		case 92:
		{
			curp = new SYNODE();
			curp->nodeKind = ExpK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->kind.exp = VariK;
			curp->attr.ExpAttr.varkind = IdV;
			curp->attr.ExpAttr.type = Void;
			curp->name[0] = token->sem;
			curp->idNum++;
			numStack.push(curp);
			break;
		}
		case 93:
		{
			curp->attr.ExpAttr.varkind = IdV;
			break;
		}
		case 94:
		{
			curp->attr.ExpAttr.varkind = ArrayMembV;
			treeStack.push(&(curp->child[0]));
			SYNODE*t = new SYNODE();
			t->nodeKind = ExpK;
			t->lineNo = token->line;
			t->idNum = 0;
			t->kind.exp = OpK;
			t->attr.ExpAttr.varkind = IdV;
			t->attr.ExpAttr.type = Void;
			t->attr.ExpAttr.op = END;
			opStack.push(t);
			getExpResult2 = true;
			break;
		}
		case 95:
		{
			curp->attr.ExpAttr.varkind = FieldMembV;
			treeStack.push(&(curp->child[0]));
			break;
		}
		case 96:
		{
			curp = new SYNODE();
			curp->nodeKind = ExpK;
			curp->lineNo = token->line;
			curp->idNum = 0;
			curp->kind.exp = VariK;
			curp->attr.ExpAttr.varkind = IdV;
			curp->attr.ExpAttr.type = Void;
			curp->name[0] = token->sem;
			curp->idNum++;

			SYNODE**t = treeStack.top();
			treeStack.pop();
			*t = curp;
			break;
		}
		case 97:
		{
			curp->attr.ExpAttr.varkind = IdV;
			break;
		}
		case 98:
		{
			curp->attr.ExpAttr.varkind = ArrayMembV;
			treeStack.push(&(curp->child[0]));
			SYNODE*t = new SYNODE();
			t->nodeKind = ExpK;
			t->lineNo = token->line;
			t->idNum = 0;
			t->kind.exp = OpK;
			t->attr.ExpAttr.varkind = IdV;
			t->attr.ExpAttr.type = Void;
			t->attr.ExpAttr.op = END;
			opStack.push(t);
			getExpResult2 = true;
			break;
		}
	}
}


int  Priosity(int op)
{
	int  pri = 0;
	switch (op)
	{
		case END:
			pri = -1;
			break;//栈底标识，优先级最低
		case LPAREN:
			pri = 0;
		case LT:
		case EQ:
			pri = 1;
			break;
		case PLUS:
		case MINUS:
			pri = 2;
			break;
		case TIMES:
		case OVER:
			pri = 3;
			break;
		default:
			pri = -1;
	}
	return  pri;
}


/** 增量/减量缩进宏定义 **/
int indentno = 0;
#define INDENT indentno+=4
#define UNINDENT indentno-=4
bool Error = false;
CString treetext = "";
CString tstr;

void initialOutBuffer()
{
	Error = false;
	treetext = "";
	tstr;
	indentno = 0;
}

void printSpaces(void)
{
	int i;
	for (i = 0; i < indentno; i++)
		treetext+=" ";
}

void printTab(int n)
{
	for (int i = 0; i < n; i++)
		treetext += " ";
}

void printTree(SYNODE *tree)
{
	int i;

	/* 增量缩进宏,每次进入语法树节点都进行增量缩进 */
	INDENT;

	/* 函数参数给定语法树节点指针tree非NULL(空) */
	while (tree != NULL)
	{
		/*打印行号*/
		//if (tree->lineNo == 0)
		//	printTab(9);
		//else
		//	switch ((int)(tree->lineNo / 10))
		//	{
		//		case 0:
		//			tstr.Format("line:%-3d", tree->lineNo);
		//			treetext += tstr;
		//			printTab(3);
		//			break;
		//		case 1:
		//		case 2:
		//		case 3:
		//		case 4:
		//		case 5:
		//		case 6:
		//		case 7:
		//		case 8:
		//		case 9:
		//			tstr.Format("line:%-3d", tree->lineNo);
		//			treetext += tstr;
		//			printTab(2);
		//			break;
		//		default:
		//			tstr.Format("line:%-3d", tree->lineNo);
		//			treetext += tstr;
		//			printTab(1);
		//	}
		tstr.Format("line:%-3d", tree->lineNo);
			treetext += tstr;
		/* 调用函数printSpaces,打印相应的空格,进行缩进 */
		printSpaces();

		switch (tree->nodeKind)
		{
			case ProK:
				treetext += "ProK  ";
				break;
			case PheadK:
			{
				tstr.Format("PheadK  %s", tree->name[0].c_str());
				treetext += tstr;
			}
			break;
			case DecK:
			{
				if (tree->attr.ProcAttr.paramt == varparamType)
					treetext += "var param:  ";
				if (tree->attr.ProcAttr.paramt == valparamType)
					treetext += "value param:  ";
				switch (tree->kind.dec)
				{
					case  ArrayK:
					{
						tstr.Format("ArrayK  %d  %d  ", tree->attr.ArrayAttr.up, tree->attr.ArrayAttr.low);
						treetext += tstr;
						if (tree->attr.ArrayAttr.childType == CharK)
							treetext+="Chark  ";
						else if (tree->attr.ArrayAttr.childType == IntegerK)
							treetext+="IntegerK  ";
					};
					break;
					case  CharK:
						treetext+="CharK  ";
						
						break;
					case  IntegerK:
						treetext += "IntegerK  ";
						break;
					case  RecordK:
						treetext += "RecordK  ";
						break;
					case  IdK:
						tstr.Format("IdK  %s  ", tree->attr.typeName.c_str());
						treetext += tstr;
						break;
					default:
						treetext += "error1!  ";
						Error = true;
				};
				if (tree->idNum != 0)
					for (int i = 0; i < tree->idNum; i++)
					{
						treetext += tree->name[i].c_str();
						treetext+="  ";
					}
				else
				{
					treetext+= "wrong!no var!\r\n";
					Error = true;
				}
			}
			break;
			case TypeK:
				treetext += "TypeK  ";
				break;

			case VarK:
				treetext += "VarK  ";
				break;

			case ProcDecK:
				treetext += "ProcDecK  ";
				treetext += tree->name[0].c_str();
				break;

			case StmLK:
				treetext += "StmLk  ";
				break;

			case StmtK:
			{
				treetext += "StmtK  ";
				switch (tree->kind.stmt)
				{
					case IfK:
						treetext += "If  ";
						break;
					case WhileK:
						treetext += "While  ";
						break;

					case AssignK:
						treetext += "Assign  ";
						break;

					case ReadK:
						treetext += "Read  ";
						treetext += tree->name[0].c_str();
						break;

					case WriteK:
						treetext += "Write  ";
						break;

					case CallK:
						treetext += "Call  ";
						treetext += tree->name[0].c_str();
						break;

					case ReturnK:
						treetext += "Return  ";
						break;

					default:
						treetext += "error2!  ";
						Error = true;
				}
			};
			break;
			case ExpK:
			{
				treetext += "ExpK  ";
				switch (tree->kind.exp)
				{
					case OpK:
					{
						treetext += "Op  ";
						switch (tree->attr.ExpAttr.op)
						{
							case EQ:
								treetext += "=";
								break;
							case LT:
								treetext += "<";
								break;
							case PLUS:
								treetext += "+";
								break;
							case MINUS:
								treetext += "-";
								break;
							case TIMES:
								treetext += "*";
								break;
							case OVER:
								treetext += "/";
								break;
							default:
								treetext += "error3!";
								Error = true;
						}

						if (tree->attr.ExpAttr.varkind == ArrayMembV)
						{
							treetext += "ArrayMember  ";
							treetext += tree->name[0].c_str();
						}
					};
					break;
					case ConstK:
						treetext += "Const  ";
						switch (tree->attr.ExpAttr.varkind)
						{
							case IdV:
								treetext += "Id  ";
								treetext += tree->name[0].c_str();
								break;
							case FieldMembV:
								treetext += "FieldMember  ";
								treetext += tree->name[0].c_str();
								break;
							case ArrayMembV:
								treetext += "ArrayMember  ";
								treetext += tree->name[0].c_str();
								break;
							default:
								treetext += "var type error!";
								Error = true;
						}

						tstr.Format("%d", tree->attr.ExpAttr.val);
						treetext += tstr;
						break;
					case VariK:
						treetext += "Vari  ";
						switch (tree->attr.ExpAttr.varkind)
						{
							case IdV:
								treetext += "Id  ";
								treetext += tree->name[0].c_str();
								break;
							case FieldMembV:
								treetext += "FieldMember  ";
								treetext += tree->name[0].c_str();
								break;
							case ArrayMembV:
								treetext += "ArrayMember  ";
								treetext += tree->name[0].c_str();
								break;
							default:
								treetext += "var type error!";
								Error = true;
						}

						break;
					default:
						treetext += "error4!";
						Error = true;
				}
			};
			break;
			default:
				treetext += "error5!";
				Error = true;
		}

		treetext += "\r\n";

		/* 对语法树结点tree的各子结点递归调用printTree过程 */
		for (i = 0; i < 3; i++)
			printTree(tree->child[i]);

		/* 对语法树结点tree的兄弟节点递归调用printTree过程 */
		tree = tree->brother;
	}

	/* 减量缩进宏,每次退出语法树节点时减量缩进 */
	UNINDENT;
	treebox.SetWindowText(treetext);
}