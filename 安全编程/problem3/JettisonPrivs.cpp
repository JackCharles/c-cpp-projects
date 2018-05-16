#include <iostream>
#include <windows.h>
#include <WinSafer.h>
#include <winnt.h>
#include <strsafe.h>

#ifndef SE_PRIVILEGE_REMOVED
#define SE_PRIVILEGE_REMOVED (0x00000004)
#endif

//判断两个luid是否相等
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
		//获得一个进程访问令牌的句柄, 并且允许该句柄具有信息查询和调整的权限
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken))
			throw GetLastError();

		DWORD dwSize = 0;
		//第一次调用GetTokenInformation是为了获取令牌信息需要的缓冲区的大小（肯定失败，为节省空间）
		if (!GetTokenInformation(hToken, TokenPrivileges, NULL, 0, &dwSize))//获取
		{
			if (dwError != ERROR_INSUFFICIENT_BUFFER || dwSize<=0)
				throw dwError;
		}

		//分配缓冲区
		TokenInfo = new char[dwSize];
		if (NULL == TokenInfo)
			throw ERROR_NOT_ENOUGH_MEMORY;

		//真正获取当前进程令牌信息
		if (!GetTokenInformation(hToken, TokenPrivileges, TokenInfo, dwSize, &dwSize))
			throw GetLastError();

		TOKEN_PRIVILEGES *pTokenPrivs = (TOKEN_PRIVILEGES *)TokenInfo;

		//定义两个要保留的权限LUID
		LUID luidChangeNotify;
		LUID luidBackup;
		LookupPrivilegeValue(NULL, SE_CHANGE_NOTIFY_NAME, &luidChangeNotify);
		LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &luidBackup);		//查找BackupPrivilege

		//除了ChangeNotify和BackPrivilege外全部移除
		for (DWORD dwIndex = 0; dwIndex < pTokenPrivs->PrivilegeCount; dwIndex++)
		{
			if (!SameLuid(pTokenPrivs->Privileges[dwIndex].Luid, luidChangeNotify) &&
				!SameLuid(pTokenPrivs->Privileges[dwIndex].Luid, luidBackup))	   
				pTokenPrivs->Privileges[dwIndex].Attributes = SE_PRIVILEGE_REMOVED;//属性设为移除
		}

		//适配修改后的令牌
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