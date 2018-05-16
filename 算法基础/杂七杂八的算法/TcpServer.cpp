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

	SOCKET ServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN ServerAddr;
	int AddrSize = sizeof(SOCKADDR_IN);

	memset(&ServerAddr, 0, AddrSize);
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ServerAddr.sin_port = htons(1234);

	bind(ServerSock, (SOCKADDR*)&ServerAddr, AddrSize);
	listen(ServerSock, 10);
	cout << "Server is listening on port 1234 ..." << endl;

	SOCKADDR_IN ClientAddr;
	SOCKET ClientSock = accept(ServerSock, (SOCKADDR*)&ClientAddr, &AddrSize);

	cout << "client address is: " << inet_ntoa(ClientAddr.sin_addr)
		<< ":" << ntohs(ClientAddr.sin_port) << endl;
	int count = 0;
	while (1)
	{
		int len = recv(ClientSock, buffer, MAXBUFF, 0);
		if (len <= 0)
			break;
		buffer[len] = 0;
		cout << "Message: " << buffer << len <<endl;
		count++;
	}

	closesocket(ServerSock);
	closesocket(ClientSock);
	WSACleanup();
}
