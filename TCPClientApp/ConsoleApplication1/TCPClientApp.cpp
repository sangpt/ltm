// TCPClientApp.cpp : Defines the entry point for the console application.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>

using namespace std;

int main()
{
	//khoi tao winsock
	WSADATA DATA;
	if (WSAStartup(MAKEWORD(2, 2), &DATA)) {
		cout << "Khoi tao WinSock that bai";
	}
	else {
		cout << "Khoi tao WINSOCK thanh cong!" << endl;
	}

	//mo socket
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		cout << "Khong the mo socket" << endl;
	}
	else {
		cout << "Mo socket thanh cong. Dang cho ket noi..." << endl;
	}


	char mes[255];
	cout << "Nhap noi dung thong diep: ";
	cin >> mes;

	//cai dat ip va port
	char localhost[10] = "127.0.0.1";
	SOCKADDR_IN iAddr;
	iAddr.sin_family = AF_INET;
	iAddr.sin_port = htons(8888);
	iAddr.sin_addr.s_addr = inet_addr(localhost);

	//ket noi
	connect(s, (SOCKADDR*)&iAddr, sizeof(iAddr));

	//nhan loi chao
	char buf[255];
	int i = 0;
	int len = recv(s, (char *)&buf, sizeof(buf), 0);
	while (i < len)
	{
		cout << buf[i];
		i++;
	}
	cout << endl;

	send(s, mes, sizeof(mes), 0);

	system("pause");
	return 0;
}

