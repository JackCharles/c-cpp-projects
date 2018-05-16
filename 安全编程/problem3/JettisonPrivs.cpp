#include <iostream>
#include <windows.h>
#include <WinSafer.h>
#include <winnt.h>
#include <strsafe.h>

#ifndef SE_PRIVILEGE_REMOVED
#define SE_PRIVILEGE_REMOVED (0x00000004)
#endif

//�ж�����luid�Ƿ����
bool SameLuid(LUID luid1, LUID luid2)
{
	return (luid1.LowPart == luid2.LowPart) && (luid1.HighPart == luid2.HighPart);
}

DWORD JettisonPrivs()
{
	DWORD dwError = 0;
	void *TokenInfo = NULL;
	try
	{
		HANDLE hToken = NULL;
		//���һ�����̷������Ƶľ��, ��������þ��������Ϣ��ѯ�͵�����Ȩ��
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken))
			throw GetLastError();

		DWORD dwSize = 0;
		//��һ�ε���GetTokenInformation��Ϊ�˻�ȡ������Ϣ��Ҫ�Ļ������Ĵ�С���϶�ʧ�ܣ�Ϊ��ʡ�ռ䣩
		if (!GetTokenInformation(hToken, TokenPrivileges, NULL, 0, &dwSize))//��ȡ
		{
			if (dwError != ERROR_INSUFFICIENT_BUFFER || dwSize<=0)
				throw dwError;
		}

		//���仺����
		TokenInfo = new char[dwSize];
		if (NULL == TokenInfo)
			throw ERROR_NOT_ENOUGH_MEMORY;

		//������ȡ��ǰ����������Ϣ
		if (!GetTokenInformation(hToken, TokenPrivileges, TokenInfo, dwSize, &dwSize))
			throw GetLastError();

		TOKEN_PRIVILEGES *pTokenPrivs = (TOKEN_PRIVILEGES *)TokenInfo;

		//��������Ҫ������Ȩ��LUID
		LUID luidChangeNotify;
		LUID luidBackup;
		LookupPrivilegeValue(NULL, SE_CHANGE_NOTIFY_NAME, &luidChangeNotify);
		LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &luidBackup);		//����BackupPrivilege

		//����ChangeNotify��BackPrivilege��ȫ���Ƴ�
		for (DWORD dwIndex = 0; dwIndex < pTokenPrivs->PrivilegeCount; dwIndex++)
		{
			if (!SameLuid(pTokenPrivs->Privileges[dwIndex].Luid, luidChangeNotify) &&
				!SameLuid(pTokenPrivs->Privileges[dwIndex].Luid, luidBackup))	   
				pTokenPrivs->Privileges[dwIndex].Attributes = SE_PRIVILEGE_REMOVED;//������Ϊ�Ƴ�
		}

		//�����޸ĺ������
		if (!AdjustTokenPrivileges(hToken, FALSE, pTokenPrivs, dwSize, NULL, NULL))
			throw GetLastError();
	}
	catch (DWORD err)
	{
		dwError = err;
	}
	if (TokenInfo) 
		delete[] TokenInfo;
	return dwError;
}


int main()
{
	DWORD resValue = JettisonPrivs();
	if (resValue == 0)
		std::cout << "Remove rivileges success!" << std::endl;
	else
		std::cout << "An error occurred, ErrorCode: " << resValue << std::endl;
	return 0;
}