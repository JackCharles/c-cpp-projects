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
	cout << "请输入密钥(长整形整数):";
	cin >> key;
	cout << "请输入待加密字符串：" << endl;
	cin >> data;
	cout << "对应密文是:";
	Coder(data, strlen(data), key);
	cout << "你要解密吗(Y/N)?" << endl;
	char flag;
	cin >> flag;
	if(flag == 'Y' || flag == 'y')
	{
		cout << "解得明文是:";
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
		Ciphertext[j] = data[j] xor rand[j]; //异或
	Ciphertext[len] = '\0';
	cout << Ciphertext << endl;
}
