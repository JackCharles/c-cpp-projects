#include<stdio.h>
#include<math.h>
int SDGX(float,float,float,float,float,float);//判读三点是否共线(函数原型)
int ZJSJ(float,float,float,float,float,float);//判断是否为直角三角形(函数原型)
void main(){
	float a,b,c,d,e,f;
	printf("这是一个判断三角形的程序!\n请输入三个个坐标:");
	scanf("%f%f%f%f%f%f",&a,&b,&c,&d,&e,&f);
	if(SDGX(a,b,c,d,e,f)==-1)
		printf("这三点不能构成三角形!\n");
	else{
		if(ZJSJ(a,b,c,d,e,f)==1)
			printf("这三点构成直角三角形!\n");
		if(ZJSJ(a,b,c,d,e,f)==-1)
			printf("这三点构成普通三角形!\n");
		}
}
float LDJL(float a,float b,float c,float d){//计算两点之间距离的平方，防止开方精度损失(定义函数)
	float i;
	i=(a-c)*(a-c)+(b-d)*(b-d);
	return i;
}
int SDGX(float a,float b,float c,float d,float e,float f){//判读三点是否共线(定义函数)
	int i,j,k;
	if(a==c){//斜率不存在
		if(e==c)
			return -1;//三点在一条竖线上
		else
			return 1;
	}
	else{//斜率存在
		k=(b-d)/(a-c);//斜率
		j=b-k*a;//截距
		if(f-k*e-j<1e-8)//避免精度损失引发的错误
			return -1;
		else
			return 1;
	}
}
int ZJSJ(float a,float b,float c,float d,float e,float f){//判断是否为直角三角形(函数定义)
	if(LDJL(a,b,c,d)+LDJL(a,b,e,f)-LDJL(c,d,e,f)<1e-10||
	   LDJL(a,b,c,d)+LDJL(c,d,e,f)-LDJL(a,b,e,f)<1e-10||
	   LDJL(a,b,e,f)+LDJL(c,d,e,f)-LDJL(a,b,c,d)<1e-10)
		return 1;
	else
		return -1;
}
