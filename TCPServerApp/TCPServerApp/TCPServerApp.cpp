// TCPClientApp.cpp : Defines the entry point for the console application.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;

int main()
{
	while (1) {
		//khoi tao winsock
		WSADATA DATA;
		int ec = WSAStartup(MAKEWORD(2, 2), &DATA);
		if (ec == 0) {
			cout << "Khoi tao WinSock thanh cong" << endl;
		}
		else {
			cout << "khoi tao WinSock that bai";
		}

		//tao socket
		SOCKET s;
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s != INVALID_SOCKET)
		{
			cout << "Tao duoc socket" << endl;
		}
		else
		{
			cout << "Khong tao duoc socket" << endl;
		}

		//thiet lap ip, port
		SOCKADDR_IN serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(8888);
		serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

		//dua thong tin ip, port vao socket
		bind(s, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

		//lang nghe ket noi
		listen(s, 5);

		//chap nhan ket noi tu client
		SOCKET connectSoc;
		SOCKADDR_IN clientAddr;
		int clen = sizeof(clientAddr);
		connectSoc = accept(s, (SOCKADDR*)&clientAddr, &clen);

		//gui loi chao
		char buf[255] = "Chao mung da ket noi den 127.0.0.1 ";
		send(connectSoc, buf, sizeof(buf), 0);

		//nhan thong diep
		char mes[255];
		int i = 0;
		int len = recv(s, mes, sizeof(mes), 0);
		while (i < len)
		{
			cout << buf[i];
			i++;
		}
		cout << endl;

		closesocket(s);
		closesocket(connectSoc);
		WSACleanup();
	}

	system("pause");
}

