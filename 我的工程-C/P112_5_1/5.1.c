#include<stdio.h>
#include<math.h>
float p(float);                                  //p(u)����ԭ��
float y(float);                                  //y(x)����ԭ��
float x;                                         //����ȫ�ֱ���
void main(){
	float a;
	printf("Please input a number(x):");
	scanf("%f",&x);
	a=y(x);                                      //����y(x)
	printf("�����:%f\n",a);
}
float f(float v,float w){                        //����f(v,w)
	float a;
	a=(v+w)/(7*v);
	return a;
}
float p(float u){                                 //����p(u)
	float a;
	a=(f(u*0.3,x+u)+u/2)/(2*x);                   //����f(x)
	return a;
}
float y(float x){                                 //����y(x)
	float a;
	a=(((p(x)*p(x))+5*x)/(p(x+5)-sqrt(x)))*p(x+2);//����p(u)
	return a;
}