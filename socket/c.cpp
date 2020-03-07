//#include "InitSock.h"
#include <stdio.h>
#include <iostream>
#include <windows.h>

using namespace std;

char szText[256];
SOCKET s;

DWORD WINAPI tprocess3(LPVOID lpParam)
{
    static int num = 1;
    while (TRUE) {
        if (num == 1) {
            num = 2;
            /* code */
        } else {
            cout<<"send data: ";
        }
        
        gets_s(szText);
        //szText[255] = '\0';   
        ::send(s, szText, strlen(szText), 0);
    }
}

int main_c()
{
    DWORD dwThread;
    // 创建套节字   
    s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) {
        printf(" Failed socket() \n");
        return 0;
    }

    // 也可以在这里调用bind函数绑定一个本地地址   
    // 否则系统将会自动安排   

    // 填写远程地址信息   
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(4567);
    // 注意，这里要填写服务器程序（TCPServer程序）所在机器的IP地址   
    // 如果你的计算机没有联网，直接使用127.0.0.1即可   
    servAddr.sin_addr.S_un.S_addr = inet_addr("192.168.50.54");

    if (::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
        printf(" Failed connect() \n");
        return 0;
    }

    char buff[256];
    //char szText[256] ;   
    CreateThread(NULL, 0, tprocess3, NULL, 0, &dwThread);
    while (TRUE) {
        //从服务器端接收数据   
        int nRecv = ::recv(s, buff, 256, 0);
        if (nRecv > 0)
        {
            buff[nRecv] = '\0';
            printf("receive data: %s\n", buff);
        }

        // 向服务器端发送数据   

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
    // 关闭套节字   
    ::closesocket(s);
    return 0;
}