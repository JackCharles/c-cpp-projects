#include<stdio.h>


void paixu(int n,int a[]){
	int i,j,k,temp;

	for(i=1;i<n;i++){
		for(j=0;j<n;j++)
			if(a[i]<a[j]){
				temp=a[i];
				for(k=i;k>=j;k--)
					a[k]=a[k-1];
				a[j]=temp;
				break;
			}
	}
}


void main(){
	int i,n,a[]={-5,265,3,63,5,25,2,35,2,96,52,45,12};


	n=sizeof(a)/sizeof(int);
	//sizeof(a)ָ���������ڴ�ռ䳤�ȣ�����Ԫ�ظ�����(a��һ��ָ���׵�ַ����ָ�룬sizeof(a)�����������鳤�ȣ������ٸ��ֽ�)
	//�����á������ڴ�ռ䳤�ȡ�/��ÿ��Ԫ����ռ���ڴ�ռ䳤�ȡ�����Ԫ�ظ�����
	paixu(n,a);
	for(i=0;i<n;i++)
		printf("%3d",a[i]);
	printf("\n");
}
