#include<stdio.h>
#include<string.h>
void main(){
	char H[7][7],E[7][7],L[7][7],O[7][7];//�˴�һ��6���ַ�������ϡ�\0��,������Ҫ����7���ռ�
	int i;
	memset(H,' ',sizeof(H));//���鸶��ֵ��ȫΪ�ո�;
	memset(H,' ',sizeof(E));
	memset(H,' ',sizeof(L));
	memset(H,' ',sizeof(O));
	for(i=0;i<3;i++)
		strcpy(H[i],"H    H");
	strcpy(H[3],"HHHHHH");
	for(i=4;i<7;i++)
		strcpy(H[i],"H    H");
	strcpy(E[0],"EEEEEE");
	strcpy(E[3],"EEEEEE");
	strcpy(E[6],"EEEEEE");
	for(i=1;i<3;i++)
		strcpy(E[i],"E     ");
	for(i=4;i<6;i++)
		strcpy(E[i],"E     ");
	for(i=0;i<6;i++)
		strcpy(L[i],"L     ");
	strcpy(L[6],"LLLLLL");
	strcpy(O[0],"OOOOOO");
	strcpy(O[6],"OOOOOO");
	for(i=1;i<6;i++)
		strcpy(O[i],"O    O");

	for(i=0;i<7;i++)
	printf("    %s   %s   %s   %s   %s\n",H[i],E[i],L[i],L[i],O[i]);
	printf("\n\n");

	
}