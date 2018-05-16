#include "stdafx.h"
#include"GlobalVars.h"

char Buff[10000];

int buffPos = 0;
int lineno = 1;
bool wordAnalyzeError;
int errorLineno;
bool isFirstOutputWordError;

//��ȡTokenlist�ĺ���
bool getTokenlist()
{
	memset(Buff, 0, 10000*sizeof(char));
	buffPos = 0;
	lineno = 1;
	wordAnalyzeError = false;
	errorLineno = 0;
	isFirstOutputWordError = true;

	ReadFromFile(Buff);
	TokenNode *headNode;//�����ͷ�ڵ�
	TokenNode *tailNode;//β�ڵ�
	TokenNode *currentNode;//����ĵ�ǰ�ڵ�
	TokenNode currentToken;//��ŵ�ǰ�ڵ��token
	headNode = currentNode = tailNode = new TokenNode();
	currentNode->next = NULL;
	char tokenString[20] = { 0 };

	do
	{
		int	state = START;
		int tokenStringIndex = 0;

		//�����ж���ǰ�ַ��Ƿ�Ҫд��tokenString;
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
							/* ��ǰ�ַ�cΪEOF,�ַ��洢��־save����ΪFALSE,����洢     *
							* ��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ�ļ���������ENDFILE */
							case EOF:
								save = false;
								currentToken.lex = ENDFILE;
								break;

								/* ��ǰ�ַ�cΪ"=",��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ�Ⱥŵ���EQ */
							case '=':
								currentToken.lex = EQ;
								break;

								/* ��ǰ�ַ�cΪ"<",��ǰʶ�𵥴ʷ���ֵcurrentToken����ΪС�ڵ���LT */
							case '<':
								currentToken.lex = LT;
								break;

								/* ��ǰ�ַ�cΪ"+",��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ�Ӻŵ���PLUS */
							case '+':
								currentToken.lex = PLUS;
								break;

								/* ��ǰ�ַ�cΪ"-",��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ���ŵ���MINUS */
							case '-':
								currentToken.lex = MINUS;
								break;

								/* ��ǰ�ַ�cΪ"*",��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ�˺ŵ���TIMES */
							case '*':
								currentToken.lex = TIMES;
								break;

								/* ��ǰ�ַ�cΪ"/",��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ���ŵ���OVER */
							case '/':
								currentToken.lex = OVER;
								break;

								/* ��ǰ�ַ�cΪ"(",��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ�����ŵ���LPAREN */
							case '(':
								currentToken.lex = LPAREN;
								break;

								/* ��ǰ�ַ�cΪ")",��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ�����ŵ���RPAREN */
							case ')':
								currentToken.lex = RPAREN;
								break;

								/* ��ǰ�ַ�cΪ";",��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ�ֺŵ���SEMI */
							case ';':
								currentToken.lex = SEMI;
								break;
								/* ��ǰ�ַ�cΪ",",��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ���ŵ���COMMA */
							case ',':
								currentToken.lex = COMMA;
								break;
								/* ��ǰ�ַ�cΪ"[",��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ�������ŵ���LMIDPAREN */
							case '[':
								currentToken.lex = LMIDPAREN;
								break;

								/* ��ǰ�ַ�cΪ"]",��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ�������ŵ���RMIDPAREN */
							case ']':
								currentToken.lex = RMIDPAREN;
								break;

								/* ��ǰ�ַ�cΪ�����ַ�,��ǰʶ�𵥴ʷ���ֵcurrentToken����Ϊ���󵥴� */
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
					if (!isalnum(c))  //�ж�c�Ƿ�Ϊ��ĸ�������֣�
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
		if (currentToken.lex == ERRORX)//��Ǵʷ�����
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
			s.Format("�ڵ� %d �з��ִʷ���������...\r\n",lineno);
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
		synbox.SetWindowText(t+"�ʷ����������﷨������������С�");
		return false;
	}
	else
		return true;
}

//�Ƿ�������
bool isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}
//�Ƿ�����ĸ
bool isalpha(char c)
{
	if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z')
		return true;
	else
		return false;


}
//�Ƿ������ֻ�����ĸ
bool isalnum(char c)
{
	if (isalpha(c) || isDigit(c))
		return true;
	else
		return false;
}
//���Ҹ����ַ���ӳ��ı�����
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
//�������������е�Tokenд���ļ��У�
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