#include <stdio.h>
#include "InitSock.h"
#include <iostream>

#define server 1
#define client 2
using namespace std;

int main(int argc, char* argv[])
{
	int select_s_c = 0; 
	int num = 0; 

	for (num = 0; num < 3; num++) {
		cout << "start\n1:serve       2:client\n" << endl;
		cout << "please input:" << endl;
		scanf_s("%d", &select_s_c);

		if (select_s_c == server) {
			cout << "choose server" << endl;
			main_s();
		}
		else if (select_s_c == client) {
			cout << "choose client" << endl;
			main_c();
		}
	}

	return 0;
}

