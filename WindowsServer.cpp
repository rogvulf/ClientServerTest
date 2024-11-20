//#include <windows.h>
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <stdio.h>

#pragma comment(lib,"Ws2_32.lib") 


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int CmdShow)
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	int intresult;
	SOCKET ClientSocket = INVALID_SOCKET;
	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in ListenSocket_adr;
	ListenSocket_adr.sin_family = AF_INET;
	ListenSocket_adr.sin_port = htons(8080);
	ListenSocket_adr.sin_addr.s_addr = INADDR_ANY;
	
	intresult = bind(ListenSocket, (struct sockaddr*)&ListenSocket_adr, sizeof(ListenSocket_adr));
	intresult = listen(ListenSocket, 5);
	ClientSocket = accept(ListenSocket, NULL, NULL);
	closesocket(ListenSocket);
	int checker;
	do
	{
		checker = send(ClientSocket, "Hello From Server!", 50, 0);
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
