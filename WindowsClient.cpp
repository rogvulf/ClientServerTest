//#include <windows.h>
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <stdio.h>

#pragma comment(lib,"Ws2_32.lib")
#pragma warning(disable:4996)


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int CmdShow)
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	SOCKET ClientSocket = INVALID_SOCKET;
	int intresult;
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in ClientSocket_adr;
	ClientSocket_adr.sin_family = AF_INET;
	ClientSocket_adr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	ClientSocket_adr.sin_port = htons(8080);
	intresult = connect(ClientSocket, (struct sockaddr*)&ClientSocket_adr, sizeof(ClientSocket_adr));
	int checker;
	do
	{
		checker = send(ClientSocket, "Hello From Client!", 50, 0);
		char charr[50]{'1'};
		checker = recv(ClientSocket, charr, sizeof(charr), 0);
		std::string strrecv;
		strrecv += charr;
		MessageBoxA(NULL, strrecv.c_str(), strrecv.c_str(), NULL);
	} while (checker > 0);
	shutdown(ClientSocket, SD_SEND);
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}
