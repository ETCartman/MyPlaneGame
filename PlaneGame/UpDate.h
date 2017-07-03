#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <iostream>
#include <fstream>
#pragma comment(lib, "ws2_32.lib")


#define BUF_SIZE 1024
class CUpDate
{
public:
	CUpDate();
	bool CheckNewVersion();
	void GetNewVersion();
	
	WSADATA wsaData;
	SOCKET sock;
	sockaddr_in sockAddr;
	char str[20];
	FILE *fp;
	~CUpDate();
};
