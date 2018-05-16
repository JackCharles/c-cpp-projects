#include<stdio.h>
long long jc(long);//声明函数原型
void main(){
	int m,n;
	double a;
	printf("请输入两正整数m,n(m>=n):");
	scanf("%d%d",&m,&n);
	if(m>=0&&n>=0&&m>=n){
		a=jc(m)/(jc(m-n)*jc(n));//注意此处要进行数据类型强制转化
		printf("结果是:%lf\n",a);
	}
	else
		printf("输入错误!\n");	     
}
long long jc(long x){//定义阶乘函数
	long a=1,i;
	if(x!=0){
		for(i=1;i<=x;i++)
			a=a*i;
	}
	else 
		a=1;
	return a;
}

/*注意在c语言中，一个变量的数据类型在整个程序中必须一致，
如果定义与使用类型不一致则在编译、链接环节不会出错，但无法运行；
比如定义int a(整形)，但输出的是%f(浮点型)，则运行会出错。*/
