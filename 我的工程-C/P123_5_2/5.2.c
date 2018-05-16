#include<stdio.h>
#include<math.h>
float ln(float);//ln函数原型
void main(){
	float a,b,c,T;
	printf("请输入实数a,b,c:");
	scanf("%f%f%f",&a,&b,&c);
	T=(4.25*(a+b)+ln(a+b))/(4.25+ln(c));//调用ln函数
	printf("T=%g\n",T);
}
float ln(float x){//定义ln函数
	float a;
	a=log(x+sqrt(x)+1/x);
	return a;
}