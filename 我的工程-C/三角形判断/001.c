#include<stdio.h>
#include<math.h>
int SDGX(float,float,float,float,float,float);//�ж������Ƿ���(����ԭ��)
int ZJSJ(float,float,float,float,float,float);//�ж��Ƿ�Ϊֱ��������(����ԭ��)
void main(){
	float a,b,c,d,e,f;
	printf("����һ���ж������εĳ���!\n����������������:");
	scanf("%f%f%f%f%f%f",&a,&b,&c,&d,&e,&f);
	if(SDGX(a,b,c,d,e,f)==-1)
		printf("�����㲻�ܹ���������!\n");
	else{
		if(ZJSJ(a,b,c,d,e,f)==1)
			printf("�����㹹��ֱ��������!\n");
		if(ZJSJ(a,b,c,d,e,f)==-1)
			printf("�����㹹����ͨ������!\n");
		}
}
float LDJL(float a,float b,float c,float d){//��������֮������ƽ������ֹ����������ʧ(���庯��)
	float i;
	i=(a-c)*(a-c)+(b-d)*(b-d);
	return i;
}
int SDGX(float a,float b,float c,float d,float e,float f){//�ж������Ƿ���(���庯��)
	int i,j,k;
	if(a==c){//б�ʲ�����
		if(e==c)
			return -1;//������һ��������
		else
			return 1;
	}
	else{//б�ʴ���
		k=(b-d)/(a-c);//б��
		j=b-k*a;//�ؾ�
		if(f-k*e-j<1e-8)//���⾫����ʧ�����Ĵ���
			return -1;
		else
			return 1;
	}
}
int ZJSJ(float a,float b,float c,float d,float e,float f){//�ж��Ƿ�Ϊֱ��������(��������)
	if(LDJL(a,b,c,d)+LDJL(a,b,e,f)-LDJL(c,d,e,f)<1e-10||
	   LDJL(a,b,c,d)+LDJL(c,d,e,f)-LDJL(a,b,e,f)<1e-10||
	   LDJL(a,b,e,f)+LDJL(c,d,e,f)-LDJL(a,b,c,d)<1e-10)
		return 1;
	else
		return -1;
}
