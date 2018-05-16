#include<stdio.h>
void main(){
	char a,b,c;
	int d,e,f,g,h;
	for(a='A';a<='F';a++){
		for(b=a;b<='I';b++)
			printf(" %c",b);
		for(c='A';c<=a-1;c++)
			printf(" %c",c);
	    for(d=1;d<='F'-a;d++)
			printf("  ");
		for(e=1;e<=2*a-2*'A'+1;e++)
			printf("%2c",a);
	    for(f=1;f<='F'-a;f++)
			printf("  ");
		for(g=a+1;g<='I';g++)
			printf("%2c",g);
		for(h='A';h<=a;h++)
			printf("%2c",h);
		printf("\n");
	}
	for(a='E';a>='A';a--){
		for(b=a;b<='I';b++)
			printf(" %c",b);
		for(c='A';c<=a-1;c++)
			printf(" %c",c);
        for(d=1;d<='F'-a;d++)
			printf("  ");
		for(e=1;e<=2*a-2*'A'+1;e++)
			printf("%2c",a);
	    for(f=1;f<='F'-a;f++)
			printf("  ");
		for(g=a+1;g<='I';g++)
			printf("%2c",g);
		for(h='A';h<=a;h++)
			printf("%2c",h);
		printf("\n");
	}
}