#include<stdio.h>
char *p[2][3]={"abc","defgh","ijkl","mnopqr","stuvw","xyz"};
void main(){
	printf("%s\n",**(p+1));
	printf("%c\n",**p[0]);
	printf("%c\n",(*(*(p+1)+1))[4]);	
	printf("%c\n",*(p[1][2]+2));
	printf("%s\n",**(p+1));
}
