#include<stdio.h>
void main(){
	int i,j,flag;
	for(i=2;i<=100;i++){
		flag=1;	//����Ϊ����(�˴�flag���ܷ���for���棬��������棬��i=4ʱflag=0���˺������ǲ�������flag=0�����������Զ�����������for����ÿ�ζ���flag��Ϊ1��Ȼ���ж��Ƿ���0ȡ��)
		for(j=i/2;j>=2;j--)
			if(i%j==0)
				flag=0;
		if(flag==1)
			printf("%5d",i);
	}printf("\n");
}