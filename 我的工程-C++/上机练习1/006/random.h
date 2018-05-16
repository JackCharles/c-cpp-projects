#ifndef RANDOM_H
#define RANDOM_H

#include <limits.h>	//����INT_MAX��ULONG_MAX����
#include <windows.h>	//����GetTickCount()����,�䷵�شӿ��������ھ����ĺ�����

class TRandom
{	
public:
	//ȱʡʹ��ϵͳʱ��(�����󾭹��ĺ�����)Ϊ����
	TRandom (long seed=0)   { mSeed=(seed?seed: GetTickCount());  } 

	//Ҳ���Զ����Լ�������
	void Seed(long seed=0)	{ mSeed=(seed?seed: GetTickCount( )); }     

	//ȡ��һ�����������
	int  Integer()  			  { return Next();}        

	//ȡ��һ����ָ����Χ�ڵ��������
	int  Integer(int min,int max) { return min+Next()%(max-min+1);} 

    	//ȡ��һ������ģ�0��1֮��ģ�С��
	double Real() 				{return double(Next())/double(INT_MAX);}
private:
    	//ʹ�õ����㷨
	void Change() 		{mSeed=(314159265*mSeed+13579)%ULONG_MAX;}

    	//ȡ��α�����������������������е���һ���������
	int  Next() { 
                int loops=mSeed%3;	
                for (int i=0;i<=loops;i++)  
                    Change ();
		return int(mSeed/2); 
            }
	unsigned long  mSeed;   //�����������������
};

#endif