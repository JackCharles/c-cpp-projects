/*VS 2015�±���ͨ��*/

#include <iostream>
#include <windows.h>
#include <Sddl.h>

using namespace std;

int main()
{
	/*
	Guests���ܾ����ʣ�
	SYSTEM����ȫ���ƣ�
	Administrators����ȫ���ƣ�
	Interactive Users������д��ִ�У�
	�����ߣ���ȫ���ƣ�
	�����ߣ�ֻ����
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
