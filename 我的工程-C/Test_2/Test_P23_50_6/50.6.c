#include<stdio.h>
void main(){
	float x,b,c=1,sum;
	int n,a=1;
	printf("请输入x,n:");
	scanf("%f%d",&x,&n);
	b=x;
	sum=x;//，此处作用有二，一是不符合while条件，直接输出x，二是为while里的循环加上第一项x
	while(a<=n-1&&b/c>=1e-8){//此处判断用到a,b,c，因此三者都要赋初值
			b=b*x*x;
			c=2*a+1;
			sum=sum+b/c;//此处从第二项开始叠加，第一项已为sum赋为x
			a++;
		}
	printf("arch(x)=%f\n",sum);
}