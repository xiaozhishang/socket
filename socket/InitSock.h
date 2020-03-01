#include <winsock2.h>   
#include <stdlib.h>    
#include <conio.h>    
#include <stdio.h>    

int main_c();
int main_s();

// 链接到WS2_32.lib
#pragma comment(lib, "WS2_32") 
#ifdef _InitSock
#endif  

class CInitSock
{
public:
    CInitSock(BYTE minorVer = 2, BYTE majorVer = 2)
    {
        // 初始化WS2_32.dll   
        WSADATA wsaData;
        WORD sockVersion = MAKEWORD(minorVer, majorVer);
        if (::WSAStartup(sockVersion, &wsaData) != 0) {
            exit(0);
        }
    }

    ~CInitSock()
    {
        ::WSACleanup();
    }
};
// 初始化Winsock库  
CInitSock initSock;
