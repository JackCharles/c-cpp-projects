#include<stdio.h>
void main(){
	char a,b,c;
	for(a='A';a<='F';a++){
		for(b=a;b<='I';b++)
			printf(" %c",b);
		for(c='A';c<=a-1;c++)
			printf(" %c",c);
		printf("\n");
	}
	for(a='E';a>='A';a--){
		for(b=a;b<='I';b++)
			printf(" %c",b);
		for(c='A';c<=a-1;c++)
			printf(" %c",c);
		printf("\n");
	}
}