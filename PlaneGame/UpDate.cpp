#include "stdafx.h"
#include "UpDate.h"

CUpDate::CUpDate()
{

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建套接字
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//向服务器发起请求

	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("123.206.180.119");

}
bool CUpDate::CheckNewVersion()
{
	sockAddr.sin_port = htons(1234);

	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	char szBuffer[MAXBYTE] = { 0 };
	recv(sock, szBuffer, MAXBYTE, NULL);
	//输出接收到的数据
	
	
	//printf("Message form server: %s\n", szBuffer);
	fp = fopen("game.version", "r");
	fscanf(fp, "%s", str);
	//printf("%s", str);
	fclose(fp);
	std::ofstream out("game.version");
	if (out.is_open())
	{
		out << szBuffer;

		out.close();
	}
	for (int i = 0; i < 4; i++)
	{
		if (str[i] != szBuffer[i])
		{
			return TRUE;
		}
	}

	
	
	return FALSE;




}

void CUpDate::GetNewVersion()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建套接字
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//向服务器发起请求

	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("123.206.180.119");
	sockAddr.sin_port = htons(5656);
	FILE *fp = fopen("PlaneGame.exe", "wb");  //以二进制方式打开（创建）文件
	if (fp == NULL)
	{
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//循环接收数据，直到文件传输完毕
	char buffer[BUF_SIZE] = { 0 };  //文件缓冲区
	int nCount;
	while ((nCount = recv(sock, buffer, BUF_SIZE, 0)) > 0) {
		fwrite(buffer, nCount, 1, fp);
	}
	//puts("File transfer success!");
	//文件接收完毕后直接关闭套接字，无需调用shutdown()
	fclose(fp);
	WSACleanup();
	exit(0);

}
CUpDate::~CUpDate()
{
	//关闭套接字
	closesocket(sock);
}