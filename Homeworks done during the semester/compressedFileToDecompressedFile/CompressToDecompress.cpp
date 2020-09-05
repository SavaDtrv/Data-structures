#include <iostream>
#include <fstream>
#include "DynamicArray.h"
#include "DynamicStack.h"
#include "DecompressFile.h"

using namespace std;

//the number of file needed for this exact program to run correctly
int const EXACT_NUM_OF_FILES = 3;
int const FIRST_FILE_NUM = 1;
int const SECOND_FILE_NUM = 2;

int main(int argc, char* argv[]) {
	if (argc == EXACT_NUM_OF_FILES) {
		DecompressFile decompression;
		decompression.decompressFile(argv[FIRST_FILE_NUM], argv[SECOND_FILE_NUM]);
	}
	else if (argc < EXACT_NUM_OF_FILES) {
		cerr << "Error: Not enough files for the functionally of the program!" << endl;
	}
	else {
		cerr << "Error: Too many files for the functionally of the program!" << endl;
	}
	system("pause");
	return 0;
}