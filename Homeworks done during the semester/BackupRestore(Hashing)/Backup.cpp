#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "BackupRestore.h"

using namespace std;

/*Examples for non CMD run of the program.
argc = 3;
argv[1] = "D:\\School\\3rdSemester\\SDP\\homeworks\\HW5\\HW5_71737_Hashing";
argv[2] = "D:\\Old1\\HW5_71737_Hashing";
*/

int main(int argc, char *argv[])
{
	//For me the directory must have double '\' in order for the program to run. 
	//Example: D:\\School\\3rdSemester\\SDP\\homeworks\\HW5. If you don't need double '\'
	//then on the rows, where i change the path of the directory, you must change 
	//"%s\\%s" with "%s\%s".

	if (argc == BACKUP_NUM) {
		BackupRestore backRest(argc);
		backRest.backup_restore(argc, argv[1], argv[2]);
	}
	else if (argc == RESTORE_NUM) {
		BackupRestore backRest(argc);
		backRest.backup_restore(argc, argv[2], argv[3]);
	}
	else {
		cerr << "Error: Too few or too many arguments given." << endl;
	}

	system("pause");
	return 0;
}