#include<iostream>
#include<stdio.h>
#include"random.h"

using namespace std;
void Coder(char data[], int len,  unsigned long key);

char Ciphertext[100];

int main()
{
	int key;
	char data[100];
	cout << "��������Կ(����������):";
	cin >> key;
	cout << "������������ַ�����" << endl;
	cin >> data;
	cout << "��Ӧ������:";
	Coder(data, strlen(data), key);
	cout << "��Ҫ������(Y/N)?" << endl;
	char flag;
	cin >> flag;
	if(flag == 'Y' || flag == 'y')
	{
		cout << "���������:";
		Coder(Ciphertext, strlen(data), key);
	}
	return 0;
}


void Coder(char data[], int len,  unsigned long key)
{
	TRandom sRand;
	sRand.Seed(key);
	int rand[len];
	for(int i = 0; i < len; i++)
		rand[i] = sRand.Integer(1, len);
	for(int j = 0; j < len; j++)
		Ciphertext[j] = data[j] xor rand[j]; //���
	Ciphertext[len] = '\0';
	cout << Ciphertext << endl;
}
