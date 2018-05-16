#include <iostream>
#include <cstring>

using namespace std;

bool IsDNA(char c)
{
	if (c == 'A' || c == 'T' || c == 'C' || c == 'G')
		return true;
	return false;
}

int GetDNALength(char* str)
{
	if (str == NULL)
		return 0;
	int maxlen = 0;
	int len = strlen(str);
	int i = 0, t=0;
	while (i < len)
	{
		if (IsDNA(str[i]))
		{
			t = 1;
			++i;
			while (i < len)
			{
				if (IsDNA(str[i]))
				{
					++i;
					++t;
				}
				else
					break;
			}
			if (t > maxlen)
				maxlen = t;
		}
		else
			++i;
	}

	return maxlen;
}


int GetOddStrMaxLen(char* str)
{
	if (str == NULL)
		return 0;

	int len = strlen(str)/2;
	char t[100];
	int j = 0, max = 0, k;
	for (int i = 0; i < len-1; i++)
	{
		t[j] = str[i];
		j++;
		for (k = 0; k < j; ++k)
			if (t[k] != str[i + k+1])
				break;
		if (k == j)
			max = j;
		//cout << max << endl;
	}

	return max*2;
}


int GetLeastCircleStr(char *str)
{
	if (str == NULL)
		return 0;
	int len = strlen(str);
	char t[128] = {0};
	for (int i = 0; i < len; i++)
	{
		if (t[str[i]] == 0)
			t[str[i]] = 1;
		else
			t[str[i]] = 0;
	}

	int k = 0;
	for (int i = 0; i < 128; i++)
		if (t[i] == 1)
			k++;
	if (k < 2)
		return 1;
	else
		return k;
}

int main()
{
	char str[1002];
	while (cin.getline(str, 1002))
	{
		cout << GetLeastCircleStr(str);
	}

	return 0;
}

//abcabcabcabc