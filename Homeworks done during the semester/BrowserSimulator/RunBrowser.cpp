#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Browser.h"

using namespace std;

int const COMMAND_LENGTH = 10;
int const URL_LENGTH = 512;

int const NUM_EQUAL_STRINGS = 0;

int const INDX_COMMAND_STRING = 1;
int const INDX_URL_STRING = 2;

int const NUMOF_STRINGS_WITH_URL = 3;
int const NUMOF_STRINGS_NO_URL = 2;

void browserFunctionsWithURL(char* command, char* _url, Browser &browser);
void browserNoURLFunctions(char* command, Browser &browser, bool &exitFlag);

int main(int argc, char* argv[]) {

	Browser myBrowser;
	cout << "Enter your command and/or URL. If you want to exit the program type: EXIT" << endl;
	bool flagForExit = false;

	while (!flagForExit) {
		if (argc == NUMOF_STRINGS_WITH_URL) {
			browserFunctionsWithURL(argv[INDX_COMMAND_STRING], argv[INDX_URL_STRING], myBrowser);
		}
		else if (argc == NUMOF_STRINGS_NO_URL) {
			browserNoURLFunctions(argv[INDX_COMMAND_STRING], myBrowser, flagForExit);
		}
		else {
			cerr << "ERROR: Too few or too many commands and /or URLs given." << endl;
			break;
		}
	}
	cout << "Browser closed." << endl;

	system("pause");
	return 0;
}

void browserFunctionsWithURL(char* command, char* _url, Browser &browser) {
	URL newURL(_url);
	if (strcmp(command, "GO") == NUM_EQUAL_STRINGS) {
		browser.go(newURL);
	}
	else if (strcmp(command, "INSERT") == NUM_EQUAL_STRINGS) {
		browser.insert(newURL);
	}
	else if (strcmp(command, "SORT") == NUM_EQUAL_STRINGS) {
		browser.sort(_url);
	}
}

void browserNoURLFunctions(char* command, Browser &browser, bool &exitFlag) {
	if (strcmp(command, "BACK") == NUM_EQUAL_STRINGS) {
		browser.back();
	}
	else if (strcmp(command, "FORWARD") == NUM_EQUAL_STRINGS) {
		browser.forward();
	}
	else if (strcmp(command, "REMOVE") == NUM_EQUAL_STRINGS) {
		browser.remove();
	}
	else if (strcmp(command, "PRINT") == NUM_EQUAL_STRINGS) {
		browser.print();
	}
	else {
		exitFlag = true;
	}
}
