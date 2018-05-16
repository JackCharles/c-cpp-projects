#include "stdafx.h"
#include"GlobalVars.h"

char Buff[10000];

int buffPos = 0;
int lineno = 1;
bool wordAnalyzeError;
int errorLineno;
bool isFirstOutputWordError;

//求取Tokenlist的函数
bool getTokenlist()
{
	memset(Buff, 0, 10000*sizeof(char));
	buffPos = 0;
	lineno = 1;
	wordAnalyzeError = false;
	errorLineno = 0;
	isFirstOutputWordError = true;

	ReadFromFile(Buff);
	TokenNode *headNode;//链表的头节点
	TokenNode *tailNode;//尾节点
	TokenNode *currentNode;//链表的当前节点
	TokenNode currentToken;//存放当前节点的token
	headNode = currentNode = tailNode = new TokenNode();
	currentNode->next = NULL;
	char tokenString[20] = { 0 };

	do
	{
		int	state = START;
		int tokenStringIndex = 0;

		//用于判定当前字符是否要写入tokenString;
		bool save;
		bool Error = false;

		while (state != DONE)
		{
			char c = getChar();
			save = true;
			switch (state)
			{
				case START:
				{
					if (isDigit(c))
						state = INNUM;
					else if (isalpha(c))
						state = INID;
					else if (c == ':')
						state = INASSIGN;
					else if (c == '.')
						state = INRANGE;
					else if (c == '\'')
					{
						save = false;
						state = INCHAR;
					}
					else if ((c == ' ') || (c == '\n') || (c == '\t'))
						save = false;
					else if (c == '{')
					{
						save = false;
						state = INCOMMIT;

					}
					else
					{
						state = DONE;
						switch (c)
						{
							/* 当前字符c为EOF,字符存储标志save设置为FALSE,无需存储     *
							* 当前识别单词返回值currentToken设置为文件结束单词ENDFILE */
							case EOF:
								save = false;
								currentToken.lex = ENDFILE;
								break;

								/* 当前字符c为"=",当前识别单词返回值currentToken设置为等号单词EQ */
							case '=':
								currentToken.lex = EQ;
								break;

								/* 当前字符c为"<",当前识别单词返回值currentToken设置为小于单词LT */
							case '<':
								currentToken.lex = LT;
								break;

								/* 当前字符c为"+",当前识别单词返回值currentToken设置为加号单词PLUS */
							case '+':
								currentToken.lex = PLUS;
								break;

								/* 当前字符c为"-",当前识别单词返回值currentToken设置为减号单词MINUS */
							case '-':
								currentToken.lex = MINUS;
								break;

								/* 当前字符c为"*",当前识别单词返回值currentToken设置为乘号单词TIMES */
							case '*':
								currentToken.lex = TIMES;
								break;

								/* 当前字符c为"/",当前识别单词返回值currentToken设置为除号单词OVER */
							case '/':
								currentToken.lex = OVER;
								break;

								/* 当前字符c为"(",当前识别单词返回值currentToken设置为左括号单词LPAREN */
							case '(':
								currentToken.lex = LPAREN;
								break;

								/* 当前字符c为")",当前识别单词返回值currentToken设置为右括号单词RPAREN */
							case ')':
								currentToken.lex = RPAREN;
								break;

								/* 当前字符c为";",当前识别单词返回值currentToken设置为分号单词SEMI */
							case ';':
								currentToken.lex = SEMI;
								break;
								/* 当前字符c为",",当前识别单词返回值currentToken设置为逗号单词COMMA */
							case ',':
								currentToken.lex = COMMA;
								break;
								/* 当前字符c为"[",当前识别单词返回值currentToken设置为左中括号单词LMIDPAREN */
							case '[':
								currentToken.lex = LMIDPAREN;
								break;

								/* 当前字符c为"]",当前识别单词返回值currentToken设置为右中括号单词RMIDPAREN */
							case ']':
								currentToken.lex = RMIDPAREN;
								break;

								/* 当前字符c为其它字符,当前识别单词返回值currentToken设置为错误单词 */
							default:
								currentToken.lex = ERRORX;
								Error = true;
								break;
						}
					}
					break;
				}

				case INCOMMIT:
					save = false;
					if (c == EOF)
					{
						state = DONE;
						currentToken.lex = ENDFILE;
					}
					else if (c == '}')
						state = START;
					break;

				case INASSIGN:
					state = DONE;
					if (c == '=')
						currentToken.lex = ASSIGN;
					else
					{
						ungetNextchar();
						save = false;
						currentToken.lex = ERRORX;
						Error = true;
					}
					break;

				case INRANGE:
					state = DONE;
					if (c == '.')
						currentToken.lex = UNDERANGE;
					else
					{
						ungetNextchar();
						save = false;
						currentToken.lex = DOT;
					}
					break;


				case INNUM:
					if (!isDigit(c))
					{
						ungetNextchar();
						save = false;
						state = DONE;
						currentToken.lex = INTC;
					}
					break;
				case INCHAR:
					if (isalnum(c))
					{
						int c1 = getNextchar();
						if (c1 == '\'')
						{
							save = true;
							state = DONE;
							currentToken.lex = CHARC;
						}
						else
						{
							ungetNextchar();
							ungetNextchar();
							state = DONE;
							currentToken.lex = ERRORX;
							Error = true;
						}
					}
					else
					{
						ungetNextchar();
						state = DONE;
						Error = true;
						currentToken.lex = ERRORX;

					}
					break;

				case INID:
					if (!isalnum(c))  //判断c是否为字母或者数字；
					{
						ungetNextchar();
						save = false;
						state = DONE;
						currentToken.lex = ID;
					}
					break;

				case DONE:
					break;


				default:
					Error = true;
					state = DONE;
					currentToken.lex = ERRORX;
					break;

			}//switch
			if (save)
				tokenString[tokenStringIndex++] = c;
			if (state == DONE)
			{
				tokenString[tokenStringIndex] = '\0';
				if (currentToken.lex == ID)
					currentToken.lex = reversedLookup(tokenString);
			}//if
		}//while

		currentNode->line = lineno;
		currentNode->lex = currentToken.lex;
		if (currentToken.lex == ERRORX)//标记词法出错
		{ 
			wordAnalyzeError = true;
			errorLineno = lineno;
			CString  t,s;
			if(isFirstOutputWordError)
			{ 
				t = "";
				isFirstOutputWordError = false;
			}
			else
				synbox.GetWindowText(t);
			s.Format("在第 %d 行发现词法错误，请检查...\r\n",lineno);
			t += s;
			synbox.SetWindowText(t);
		}
		if (currentToken.lex == ENDFILE)
			strcpy(currentNode->sem, "file_end");
		else
			strcpy(currentNode->sem, tokenString);

		currentNode = new TokenNode();
		currentNode->next = NULL;
		tailNode->next = currentNode;
		tailNode = currentNode;

	} while (currentToken.lex != ENDFILE);

	ChainToList(headNode);
	if (wordAnalyzeError)
	{
		CString  t;
		synbox.GetWindowText(t);
		synbox.SetWindowText(t+"词法分析出错，语法分析将不会进行。");
		return false;
	}
	else
		return true;
}

//是否是数字
bool isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}
//是否是字母
bool isalpha(char c)
{
	if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z')
		return true;
	else
		return false;


}
//是否是数字或者字母
bool isalnum(char c)
{
	if (isalpha(c) || isDigit(c))
		return true;
	else
		return false;
}
//查找给定字符串映射的保留字
LexType reversedLookup(char *s)
{
	int i = 0;
	for (i = 0; i < 21; i++)
	{
		if (strcmp(s, reservedWords[i].str) == 0)
			return reservedWords[i].tok;
	}
	return ID;
}
//将保存在链表中的Token写入文件中；
void ChainToList(TokenNode* head)
{
	CString tokenlist = "";
	CString temp;
	TokenNode *currentNode = head;
	FILE *fp = fopen("TokenList.txt", "w+");
	if (fp == NULL)return;
	while (currentNode->next != NULL)
	{
		if(currentNode==head)
		{
			fprintf(fp, "%d ", currentNode->line);
			temp.Format("line: %-3d ", currentNode->line);
			tokenlist.Append(temp);
		}
		else
		{
			fprintf(fp, "\n%d ", currentNode->line);
			temp.Format("\r\nline: %-3d ", currentNode->line);
			tokenlist.Append(temp);
		}
		fprintf(fp, "%d ", currentNode->lex);
		temp.Format("lex: %-3d ", currentNode->lex);
		tokenlist.Append(temp);
		fprintf(fp, "%s", currentNode->sem);
		temp.Format("sem: %s", currentNode->sem);
		tokenlist.Append(temp);
		currentNode = currentNode->next;
		tokenbox.SetWindowText(tokenlist);
	}
	fclose(fp);	
}

bool flag = true;
int getChar()
{
	if (Buff[buffPos] == '\r')
		buffPos++;
	if (Buff[buffPos] == '\n')
		lineno++;
	return Buff[buffPos++];
}

int getNextchar()
{
	return Buff[++buffPos];
}

void ungetNextchar(void)
{
	buffPos--;
	if (Buff[buffPos] == '\n')
		lineno--;
}

void ReadFromFile(char *buff) {
	
	editbox.GetWindowText(source_text);
	strcpy(buff, source_text);
	buff[source_text.GetLength()] = -1;
}