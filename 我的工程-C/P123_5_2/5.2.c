#include<stdio.h>
#include<math.h>
float ln(float);//ln����ԭ��
void main(){
	float a,b,c,T;
	printf("������ʵ��a,b,c:");
	scanf("%f%f%f",&a,&b,&c);
	T=(4.25*(a+b)+ln(a+b))/(4.25+ln(c));//����ln����
	printf("T=%g\n",T);
}
float ln(float x){//����ln����
	float a;
	a=log(x+sqrt(x)+1/x);
	return a;
}