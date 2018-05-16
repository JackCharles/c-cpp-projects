#include<stdio.h>
#include<math.h>
float p(float);                                  //p(u)函数原型
float y(float);                                  //y(x)函数原型
float x;                                         //声明全局变量
void main(){
	float a;
	printf("Please input a number(x):");
	scanf("%f",&x);
	a=y(x);                                      //调用y(x)
	printf("结果是:%f\n",a);
}
float f(float v,float w){                        //定义f(v,w)
	float a;
	a=(v+w)/(7*v);
	return a;
}
float p(float u){                                 //定义p(u)
	float a;
	a=(f(u*0.3,x+u)+u/2)/(2*x);                   //调用f(x)
	return a;
}
float y(float x){                                 //定义y(x)
	float a;
	a=(((p(x)*p(x))+5*x)/(p(x+5)-sqrt(x)))*p(x+2);//调用p(u)
	return a;
}