#include <stdio.h>
#include <math.h>
void main (){
	char A;
	int n,sum ,i,j;
	sum =0;
	i=0;
	printf ("������һ���ַ���������E/eʱ����:\n");
	A=getchar ();
	do{	
		getchar();//����ǰһ���س����������临�Ƹ�����������
		if (A>='0'&&A<='9'){//                             ��
			n=(int)A-48;//                                 �� 
			j=pow(10,i);//10^n,nΪ������powҪ��math����    ��     
			sum =sum +n*j;//                               ��
			i=i+1;//                                       ��
		}//                                                ��
		printf ("��������һ���ַ���������E/eʱ����:\n");// ��
		A=getchar ();//������������������������������������-
		}while (A!='E'&&A!='e');
	printf ("sum =%d\n",sum);
	}