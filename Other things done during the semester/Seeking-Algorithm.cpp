#include <iostream>

using namespace std;

int main() {

	int arr[] = { 2,3,5,8,11,13,21 };

	int beg = 0;
	int end = 6;
	int mid = 0;

	int elToSeek = 21;
	bool hasTheNum = false;

	while (!hasTheNum) {
		mid = (end + beg) / 2;

		if (elToSeek > arr[mid]) {
			beg = mid + 1;
		}
		else if(elToSeek < arr[mid]) {
			end = mid - 1;
		}
		else {
			hasTheNum = true;
		}
	}

	cout << hasTheNum << " " << arr[mid] << endl;
	
	
	system("pause");
	return 0;
}