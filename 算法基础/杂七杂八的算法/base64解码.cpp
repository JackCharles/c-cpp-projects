#include <iostream>
#include <math.h>
#include <string>
using namespace std;

bool DecodeUnit(char* buff,unsigned char* res)//4->3
{
	if (buff == NULL || res == NULL)
		return false;

	unsigned char base64_code[4] = { 0 };
	for (int i = 0; i<4; ++i)
	{
		if (buff[i] >= 'A' && buff[i] <= 'Z')
			base64_code[i] = buff[i] - 'A';
		else if (buff[i] >= 'a'&&buff[i]<='z')
			base64_code[i] = buff[i] - 'a' + 26;
		else if (buff[i] >= '0'&&buff[i] <= '9')
			base64_code[i] = buff[i] - '0' + 52;
		else if (buff[i] == '+')
			base64_code[i] = 62;
		else if (buff[i] == '/')
			base64_code[i] = 63;
		else if (buff[i] == '=')
			base64_code[i] = 0;
		else
		{
			cout << "±àÂë´íÎó£º" << (int)buff[i] << endl;
			return false;
		}
	}
	unsigned char bit_code[24] = { 0 };
	for (int i = 0; i<4; ++i)
	{
		int j = 5;
		while (base64_code[i]>0)
		{
			bit_code[i * 6 + j] = base64_code[i] % 2;
			base64_code[i] /= 2;
			--j;
		}
	}

	for (int i = 0; i<3; ++i)
	{
		res[i] = 0;
		for (int j = i * 8 + 7, k = 0; j >= i * 8; --j, ++k)
		{
			if (bit_code[j] == 1)
				res[i] += pow(2, k);
		}
	}
	return true;
}


int main()
{
	string str;
	unsigned char res[3];
	while (cin >> str)
	{
		int len = str.length();
		for (int i = 0; i<len; i += 4)
		{
			if (DecodeUnit(&str[i], res))
				for (int i = 0; i<3; ++i)
					if (res[i]>31 && res[i]<127)
						cout << res[i];
					else
						cout << "[<" << (int)res[i] << ">]";
		}
	}
}
