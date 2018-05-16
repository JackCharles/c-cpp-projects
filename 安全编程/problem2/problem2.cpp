/*VS 2015下编译通过*/

#include <iostream>
#include <windows.h>
#include <Sddl.h>

using namespace std;

int main()
{
	/*
	Guests（拒绝访问）
	SYSTEM（完全控制）
	Administrators（完全控制）
	Interactive Users（读、写和执行）
	创建者（完全控制）
	备份者（只读）
	*/

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;
	char *szSD = "D:P"			//DACL
		"(D;OICI;GA;;;BG)"		//Deny Guests
		"(A;OICI;GA;;;SY)"		//Allow SYSTEM Full Control
		"(A;OICI;GA;;;BA)"		//Allow Admins Full Control
		"(A;OICI;GA;;;CO)"      //Allow Creator Owner Full Control
		"(A;OICI;GR;;;BO)"		//Allow Backup Operators Read Only
		"(A;OICI;GRGWGX;;;IU)";	//Allow Interactive Users RWX

	if (ConvertStringSecurityDescriptorToSecurityDescriptor(szSD, SDDL_REVISION_1, &(sa.lpSecurityDescriptor), NULL))
	{
		if (!CreateDirectory("C:\\MyDir", &sa))
			cout << "Error code: " << GetLastError() << endl;
		else
			cout << "Create file successfully!" << endl;

		LocalFree(sa.lpSecurityDescriptor);
	}
	else
		cout << "Error code: " << GetLastError() << endl;
}
