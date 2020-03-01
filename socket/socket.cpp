#include <stdio.h>
#include "InitSock.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int a = 0; 
	int i = 0; 
	int n = 0;

	for (i = 0; i < 3; i++) {
		cout << "start\n1:serve        2:client\n" << endl;
		cout << "please input:" << endl;
		scanf_s("%d", &a);

		if (a == 1) {
			cout << "send message please choose:1     send file please choose:2" << endl;
			main_s();
		}
		else if (a == 2) {
			main_c();
		}
	}

	return 0;
}

