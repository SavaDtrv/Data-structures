#pragma once
#include <iostream>
#include <fstream>
#include <direct.h>
#include <chrono>
#include <ctime>
#include "dirent.h"
#include "md5.h"

using namespace std;

int const FULL_PATH_NAME_LEN = 1025;
int const PROBLEM_WITH_FILE_NUM = -1;
int const BACKUP_NUM = 3;
int const RESTORE_NUM = 4;

class BackupRestore {
	int typeOfOperation;

public:
	BackupRestore(int type) {
		typeOfOperation = type;
	}

	void backup_restore(int type, char* sourceDir, char* destinationDir) {
		if (type == BACKUP_NUM) {
			operation(sourceDir, destinationDir);
		}
		else if (type == RESTORE_NUM) {
			operation(destinationDir, sourceDir);
		}
	}

	int getFileSize(const char* fileName) {
		ifstream file(fileName, ifstream::in | ifstream::binary);

		if (!file.is_open())
		{
			return PROBLEM_WITH_FILE_NUM;
		}

		file.seekg(0, ios::end);
		int fileSize = file.tellg();
		file.close();

		return fileSize;
	}

	void copyFile(char* sourceFile, char* destinationFile) {
		ifstream source(sourceFile, ios::in | ios::binary);
		ofstream destination(destinationFile, ios::out | ios::binary);

		if (source.is_open() && destination.is_open()) {
			char* buffer;
			int len = getFileSize(sourceFile);
			if (len == PROBLEM_WITH_FILE_NUM) {
				cerr << "There was a problem copying the previous file." << endl;
			}
			
			buffer = new char[len];
			source.read(buffer, len);
			destination.write(buffer, len);
			delete[] buffer;
		}
		source.close();
		destination.close();
	}

	void operation(char* sourceDir, char* destinationDir) {
		MD5 md5;
		DIR *sourceDirectory = opendir(sourceDir);
		if (!sourceDirectory) {
			return;
		}

		DIR *destDirectory = opendir(destinationDir);
		if (!destDirectory) {
			_mkdir(destinationDir);
		}
		destDirectory = opendir(destinationDir);

		dirent *destEntry;
		dirent *sourceEntry;		
		while (sourceEntry = readdir(sourceDirectory)) {
			destEntry = readdir(destDirectory);
			
			//gives us full path of current file or dir 
			//for source and destination
			char sourcePath[FULL_PATH_NAME_LEN];
			sprintf(sourcePath, "%s\\%s", sourceDir, sourceEntry->d_name);
			char destPath[FULL_PATH_NAME_LEN];
			sprintf(destPath, "%s\\%s", destinationDir, sourceEntry->d_name);

			if (sourceEntry->d_type == DT_REG) {
				if (!(destEntry = readdir(destDirectory))) {
					auto start = chrono::system_clock::now();

					cout << "Copying: " << sourceEntry->d_name;
					copyFile(sourcePath, destPath);
					cout << " - Copied." << endl;

					auto end = chrono::system_clock::now();
					chrono::duration<double> elapsed_seconds = end - start;
					cout << "Elapsed time: " << elapsed_seconds.count() << "s\n" << endl;
				}
				if (strcmp(md5.digestFile(sourcePath), md5.digestFile(destPath)) != 0) {
					auto start = chrono::system_clock::now();

					cout << "Copying: " << sourceEntry->d_name << endl;
					copyFile(sourcePath, destPath);
					cout << " - Copied." << endl;

					auto end = chrono::system_clock::now();
					chrono::duration<double> elapsed_seconds = end - start;
					cout << "Elapsed time: " << elapsed_seconds.count() << "s\n" << endl;
				}
			}
			else if (sourceEntry->d_type == DT_DIR && 
				strcmp(sourceEntry->d_name, ".") != 0
				&& strcmp(sourceEntry->d_name, "..") != 0) {
				//recursively calls our function to go deeper in the directory
				operation(sourcePath, destPath);
			}
		}
		closedir(sourceDirectory);
	}
};