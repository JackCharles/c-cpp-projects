#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")
#define MAXBUFF 1024
using namespace std;


int main()
{
	char buffer[MAXBUFF];
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN ServerAddr;
	int AddrSize = sizeof(SOCKADDR_IN);

	memset(&ServerAddr, 0, AddrSize);
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ServerAddr.sin_port = htons(1234);

	int ret = connect(sock, (SOCKADDR*)&ServerAddr, AddrSize);
	if (ret == 0)
		cout << "Server has connected..." << endl;
	else
	{
		cerr << "Can not connect the server: " << WSAGetLastError() << endl;
		return 1;
	}

	int count = 0;
	while (1)
	{
		cin >> buffer;
		if (strcmp(buffer, "quit") == 0)
			break;
		send(sock, buffer, strlen(buffer), 0);
		count++;
	}

	closesocket(sock);
	WSACleanup();
}
