#include <stdio.h>
#define N 20
void main(){  
    char track[N],ch;
    int i=0,a=0,b=0,c=0;
    ch=getchar();
    while(ch!='\n'){
		//if*****************************************************************
		if(ch=='('||ch=='['||ch=='{'){//如果是左括号
			track[i]=ch;
			i++;
			if(ch=='(')  a++;
			else if(ch=='[')  b++;
			else if(ch=='{')  c++;
		}//if****************************************************************
		//else if************************************************************
		else if(ch==')'||ch==']'||ch=='}'){//如果是右括号
			//if*****************************************
			if(i>0){
			if(ch==')'&&track[i-1]!='(')	    
				printf("%c and %c is intersected\n",track[i-1],ch);
			else if(ch==']'&&track[i-1]!='[')	    
				printf("%c and %c is intersected\n",track[i-1],ch);
			else if(ch=='}'&&track[i-1]!='{')	    
				printf("%c and %c is intersected\n",track[i-1],ch);
	    }//if*********************************************
		 //if*********************************************
	    if(ch==')') {
			a--;
			if(a<0) 
				printf("先右括号)了\n");
		}//if*********************************************
	   	 //else if****************************************
	    else if(ch==']') {
			b--;
			if(b<0) 
				printf("先右括号]了\n");
		}//else if***************************************
		 //else if***************************************
	    else if(ch=='}'){
			c--;
			if(c<0) 
				printf("先右括号}了\n");
		}//else if***************************************
	}//else if****************************************************************
	 ch=getchar();
    }//*****************while循环至此结束
	if(a==0)
           printf("( and ) is matched1\n");
	else
	    printf("( and ) isn't matched1\n");
	//*************************************************
	if(b==0)
           printf("[ and ] is matched2\n");
	else
	    printf("[ and ] isn't matched2\n");
	//**************************************************
        if(c==0)
           printf("{ and } is matched3\n");
	else
	    printf("{ and } isn't matched3\n");
	
}
