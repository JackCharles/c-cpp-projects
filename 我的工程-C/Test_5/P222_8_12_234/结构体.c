#include<stdio.h>
#define m 2//mΪѧ������
#define n 3//nΪѧ����
struct onesub_ach{
	char sub_name[20];//ѧ������
	int mid_ach;//���гɼ�
	int final_ach;//��ĩ�ɼ�
	int usual_ach;//ƽʱ�ɼ�
	float sub_ach;//�γ̳ɼ�
	};
struct stu_ach{
	char name[20];//ѧ������
	int num;//ѧ��ѧ��
	struct onesub_ach sub[m];//ѧ����Ŀ��
	}stu[n];//ѧ�����˳ɼ���

void ach_input(struct onesub_ach sub[],int i){//����һ�Ƴɼ�
	printf("�������%dѧ������:",i+1);
	scanf("%s",sub[i].sub_name);
	printf("�������ѧ��ƽʱ�ɼ������гɼ�����ĩ�ɼ�:");
	scanf("%d%d%d",&(sub[i].usual_ach),&(sub[i].mid_ach),&(sub[i].final_ach));
	sub[i].sub_ach=0.1*(sub[i].usual_ach)+0.3*(sub[i].mid_ach)+0.6*(sub[i].final_ach);//����γ̳ɼ�
}

void input(struct stu_ach stu[],int i){//һ��ѧ������Ϣ
	int j;//ѧ������
	printf("\n�������%d��ѧ����������ѧ��:",i+1);
	scanf("%s%d",stu[i].name,&stu[i].num);
	for(j=0;j<m;j++)
		ach_input((stu[i].sub),j);
}

void output_onestu_achlist(struct stu_ach stu[],int i){//��ӡ��i��ѧ���ĳɼ�
	int j;
	printf("����:	%s\n",stu[i].name);
	printf("ѧ��:	%d\n",stu[i].num);
	printf("�γ̳ɼ�:\n");
	for(j=0;j<m;j++)
		printf("%s:	%f\n",(stu[i].sub[j].sub_name),(stu[i].sub[j].sub_ach));
}

void output_onesub_achlist(struct stu_ach stu[],int j){//��ӡ��j�ſγ̳ɼ���
	int i;
	printf("�γ�����:	%s\n",stu[1].sub[j].sub_name);//�ҵ��γ�����
	for(i=0;i<n;i++)
		printf("%s:	%f\n",stu[i].name,stu[i].sub[j].sub_ach);
}

void output_onesub_notpass(struct stu_ach stu[],int j){//��ӡ��j�ſγ̲�����ѧ���ɼ���
	int i,flag=1;
	for(i=0;i<n;i++)
		if(stu[i].sub[j].sub_ach<60){
			flag=-1;
			printf("%s:	%f\n",stu[i].name,stu[i].sub[j].sub_ach);
		}
		if(flag==1)
			printf("�ÿγ�û�в�����ͬѧ!\n");
}


	void main(){
		int i,flag;//iΪѧ������
		for(i=0;i<n;i++)
			input(stu,i);
		printf("\n\n��ѡ����Ҫ����ĳɼ���:\n1.ĳ��ѧ���ĳɼ���	2.ĳ�γ̵ĳɼ���	3.ĳ�γ̲�����ѧ������ɼ���\n");
		scanf("%d",&flag);
		if(flag==1){
			printf("��������Ҫ�鿴��ѧ������ţ���1��ʼ,����0������:");
			scanf("%d",&i);
			for( ;i!=0; ){
				if(i<=n&&i>0){
					output_onestu_achlist(stu,i-1);
					printf("�����������鿴,��������루��1��ʼ,����0������:");
				}
				else
					printf("�������ѧ����Ų����ڣ����������루��1��ʼ,����0������:");
				scanf("%d",&i);
			}
		}
		else if(flag==2){
			printf("��������Ҫ�鿴�Ŀ�Ŀ��ţ���1��ʼ,����0������:");
			scanf("%d",&i);
			for( ;i!=0; ){
				if(i<=m&&i>0){
					output_onesub_achlist(stu,i-1);
					printf("�����������鿴,��������루��1��ʼ,����0������:");
				}
				else
					printf("������Ŀ�Ŀ��Ų����ڣ����������루��1��ʼ,����0������:");
				scanf("%d",&i);
			}
		}
		else if(flag==3){
			printf("��������Ҫ�鿴�Ŀ�Ŀ��ţ���1��ʼ,����0������:");
			scanf("%d",&i);
			for( ;i!=0; ){
				if(i<=m&&i>0){
					output_onesub_notpass(stu,i-1);
					printf("�����������鿴,��������루��1��ʼ,����0������:");
				}
				else
					printf("������Ŀ�Ŀ��Ų����ڣ����������루��1��ʼ,����0������:");
				scanf("%d",&i);
			}
		}
		else
			printf("�������,ллʹ��!\n");
	}//main//