#include<stdio.h>
void tongji(char a[],int n);

void main()
{
	char ch[]="abc  AB 123 &&**";
	int n;
	n=sizeof(ch)/sizeof(char);
	tongji(ch,n);
}




void tongji(char ch[],int n){
	int i=0,a=0,b=0,c=0,d=0,e=0;
	char *iptr=ch;
	while(i<n)
	{
		if(iptr[i]>='A'&&iptr[i]<='Z')
			a++;
		else if(iptr[i]>='a'&&iptr[i]<='z')
			b++;
		else if(iptr[i]==' ')
			c++;
		else if(iptr[i]>='0'&&iptr[i]<='9')
			d++;
		else 
			e++;
		i++;
	}
	printf("��д��ĸ��%d��!\nСд��ĸ��%d��!\n�ո���%d��!\n������%d��!\n�����ַ���%d��!\n",a,b,c,d,e-1);
	/***********e-1������'\0'��ռ��һ���ַ�λ*******************/
}