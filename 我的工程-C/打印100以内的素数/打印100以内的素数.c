#include<stdio.h>
void main(){
	int i,j,flag;
	for(i=2;i<=100;i++){
		flag=1;	//假设为素数(此处flag不能放在for外面，如果在外面，当i=4时flag=0，此后无论是不是素数flag=0恒成立，即永远不输出，放在for里面每次都对flag赋为1，然后判断是否用0取代)
		for(j=i/2;j>=2;j--)
			if(i%j==0)
				flag=0;
		if(flag==1)
			printf("%5d",i);
	}printf("\n");
}