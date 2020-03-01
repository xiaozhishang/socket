//#include "InitSock.h"   
#include <stdio.h>   
#include <iostream>
#include <windows.h> 
using namespace std;

SOCKET sClient;
//void tprocess4(void* args)
DWORD WINAPI tprocess4(LPVOID lpParam)
{
    while (TRUE)
    {
        char buff[256];
        int nRecv = ::recv(sClient, buff, 256, 0);
        if (nRecv > 0)
        {
            buff[nRecv] = '\0';
            printf(" ���յ����ݣ�%s\n", buff);
        }
    }
}
int main_s()
{
    // �����׽���
    DWORD dwThread;
    SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //����ָ���׽���ʹ�õĵ�ַ��ʽ��ͨ��ʹ��AF_INET  
    //ָ���׽��ֵ����ͣ�����SOCK_DGRAM�����õ���udp���ɿ�����  
    //���type����ʹ�ã�ָ��ʹ�õ�Э�����ͣ���ָ���׽������ͺ󣬿�������Ϊ0����ΪĬ��ΪUDP��TCP��  
    if (sListen == INVALID_SOCKET)
    {
        printf("Failed socket() \n");
        return 0;
    }

    // ���sockaddr_in�ṹ ,�Ǹ��ṹ��  
    /* struct sockaddr_in {

    short sin_family;  //��ַ�壨ָ����ַ��ʽ�� ����ΪAF_INET
    u_short sin_port; //�˿ں�
    struct in_addr sin_addr; //IP��ַ
    char sin_zero[8]; //���ӽڣ���Ϊ��
    } */

    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(4567);  //1024 ~ 49151����ͨ�û�ע��Ķ˿ں�  
    sin.sin_addr.S_un.S_addr = INADDR_ANY;

    // ������׽��ֵ�һ�����ص�ַ   
    if (::bind(sListen, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        printf("Failed bind() \n");
        return 0;
    }

    // �������ģʽ   
    //2ָ���ǣ����������������ֵ���δ��������������  

    if (::listen(sListen, 2) == SOCKET_ERROR)
    {
        printf("Failed listen() \n");
        return 0;
    }

    // ѭ�����ܿͻ�����������   
    sockaddr_in remoteAddr;
    int nAddrLen = sizeof(remoteAddr);

    //SOCKET sClient = 0;   
    char szText[] = " TCP Server Demo! \r\n";
    while (sClient == 0)
    {
        // ����һ��������   
        //��(SOCKADDR*)&remoteAddr��һ��ָ��sockaddr_in�ṹ��ָ�룬���ڻ�ȡ�Է���ַ  
        sClient = ::accept(sListen, (SOCKADDR*)&remoteAddr, &nAddrLen);
        if (sClient == INVALID_SOCKET)
        {
            printf("Failed accept()");
        }


        printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));
        continue;
    }
    CreateThread(NULL, 0, tprocess4, NULL, 0, &dwThread);
    while (TRUE)
    {   //cout<<"send message please choose:1     send file please choose:2"<<endl;
        // ��ͻ��˷�������   
        gets_s(szText);
        ::send(sClient, szText, strlen(szText), 0);

        // �ӿͻ��˽�������   
        /*char buff[256] ;
        int nRecv = ::recv(sClient, buff, 256, 0);
        if(nRecv > 0)
        {
            buff[nRecv] = '\0';
            printf(" ���յ����ݣ�%s\n", buff);
        }   */

    }

    //pthread_create(&t1,NULL,tprocess4,NULL); 
    //CreateThread(,a)
    /*while(TRUE)
    {
        char buff[256] ;
        int nRecv = ::recv(sClient, buff, 256, 0);
        if(nRecv > 0)
        {
            buff[nRecv] = '\0';
            printf(" ���յ����ݣ�%s\n", buff);
        }
    }*/

    // �ر�ͬ�ͻ��˵�����   
    ::closesocket(sClient);

    // �رռ����׽���   
    ::closesocket(sListen);

    return 0;
}