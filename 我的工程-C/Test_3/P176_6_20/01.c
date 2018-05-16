void panduan(int x){
int n=2,i,j=1,a[1000],flag;
	a[0]=1;
	if(x==a[0])
		printf("YES!\n");
	else{
		flag=-1;
		while (x>=n){
		for (i=0;i<=j-1;i++)
			if ((n==a[i]*2+1)||(n==a[i]*3+1)){
			j++;
			a[j-1]=n;
			if(x==n){
				printf("YES!\n");
				flag=1;}
			break;}
		n++;}
		if(flag==-1)
			printf("NO!\n");
	}
	
}