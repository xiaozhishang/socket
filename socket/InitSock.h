#include <winsock2.h>   
#include <stdlib.h>    
#include <conio.h>    
#include <stdio.h>    

int main_c();
int main_s();

#pragma comment(lib, "WS2_32")  // ���ӵ�WS2_32.lib 
#ifdef _InitSock
#endif  

class CInitSock
{
public:
    CInitSock(BYTE minorVer = 2, BYTE majorVer = 2)
    {
        // ��ʼ��WS2_32.dll   
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
CInitSock initSock;     // ��ʼ��Winsock��  
