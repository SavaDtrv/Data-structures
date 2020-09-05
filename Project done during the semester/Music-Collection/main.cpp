#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "MusicalCollection.h"

using namespace std;

int const PROG_SERVICE_ONE = 1;
int const PROG_SERVICE_TWO = 2;

int main() {

	int serviceNum;

	do
	{
		cout << "\t\tChoose what you want to do:\n"
			<< "1: For registration.\n"
			<< "2: For entering the system with existing registration.\n" 
			<< "####### Any other number will terminate the program. #######"<< endl;
		cin >> serviceNum;
		MusicalCollection mc(serviceNum);
		mc.regORexisting();

	} while (serviceNum == PROG_SERVICE_ONE || serviceNum == PROG_SERVICE_TWO);

	cout << "Program closed." << endl;

	system("pause");
	return 0;
}