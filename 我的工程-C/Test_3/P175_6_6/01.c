#include<stdio.h>
#define n 6
void shanchu(int a[]){
	int m,i,j,k=0;
	for(i=0;i<n-k;i++)
		for(j=i+1;j<n-k; ){
			if(a[i]==a[j]){
				for(m=j;m<n-k;m++)
					a[j]=a[j+1];
				k++;//�˴���Ҫ������ɾȥ��ͬ���ĩβ�����������ѭ���ĸ��ţ���n-kֻ��ǰ��Чn-k����в�������
				j=i+1;//�����i��͵�i+1��ȣ����i+1�ʼ��ǰ��һλ����������i+1�ʼ��⣬��ֹi+1���Ժ�i����ȶ������
			}
			else    
				j++;//��i+1���i����ʱ�����ж�i+2����Ժ�
		}
	for(i=0;i<=n-k;i++)
	printf("%3d",a[i]);
} 
void main(){
	int a[n],i;
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	shanchu(a);
	printf("\n");
}