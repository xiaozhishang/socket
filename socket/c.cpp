//#include "InitSock.h"
#include <stdio.h>
#include <iostream>
#include <windows.h>

using namespace std;

char szText[256];
SOCKET s;

DWORD WINAPI tprocess3(LPVOID lpParam)
{
    while (TRUE) {
        gets_s(szText);
        //szText[255] = '\0';   
        ::send(s, szText, strlen(szText), 0);
    }
}

int main_c()
{
    DWORD dwThread;
    // �����׽���   
    s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) {
        printf(" Failed socket() \n");
        return 0;
    }

    // Ҳ�������������bind������һ�����ص�ַ   
    // ����ϵͳ�����Զ�����   

    // ��дԶ�̵�ַ��Ϣ   
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(4567);
    // ע�⣬����Ҫ��д����������TCPServer�������ڻ�����IP��ַ   
    // �����ļ����û��������ֱ��ʹ��127.0.0.1����   
    servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    if (::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
        printf(" Failed connect() \n");
        return 0;
    }

    char buff[256];
    //char szText[256] ;   
    CreateThread(NULL, 0, tprocess3, NULL, 0, &dwThread);
    while (TRUE) {
        //�ӷ������˽�������   
        int nRecv = ::recv(s, buff, 256, 0);
        if (nRecv > 0)
        {
            buff[nRecv] = '\0';
            printf("���յ����ݣ�%s\n", buff);
        }

        // ��������˷�������   

       /* gets(szText) ;
        szText[255] = '\0';
        ::send(s, szText, strlen(szText), 0) ;  */

    }

    /*while(TRUE)
    {
        gets(szText) ;
        szText[255] = '\0';
        ::send(s, szText, strlen(szText), 0) ;
    }*/
    // �ر��׽���   
    ::closesocket(s);
    return 0;
}