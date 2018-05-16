#include <stdio.h>
#include <math.h>
void main (){
	char A;
	int n,sum ,i,j;
	sum =0;
	i=0;
	printf ("请输入一个字符，当输入E/e时结束:\n");
	A=getchar ();
	do{	
		getchar();//读掉前一个回车符，不让其复制给→→→→→
		if (A>='0'&&A<='9'){//                             ↓
			n=(int)A-48;//                                 ↓ 
			j=pow(10,i);//10^n,n为变量，pow要有math声明    ↓     
			sum =sum +n*j;//                               ↓
			i=i+1;//                                       ↓
		}//                                                ↓
		printf ("请再输入一个字符，当输入E/e时结束:\n");// ↓
		A=getchar ();//←←←←←←←←←←←←←←←←←←-
		}while (A!='E'&&A!='e');
	printf ("sum =%d\n",sum);
	}