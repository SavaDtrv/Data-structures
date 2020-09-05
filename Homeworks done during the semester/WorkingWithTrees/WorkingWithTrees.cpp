#include <iostream>
#include <fstream>
#include "BinaryTree.h"
#include "DynamicArray.h"
#include "Pair.h"

using namespace std;

int const ARRAY_SIZE = 100;
int const REQUEST_NAME_LEN = 10;
int const NUM_OF_AS_PAR = 1;
int const GIVEN_MAIN_PARAM = 2;
int const INT_SIZE_READING = 4;
int const BEG_OF_ARRAY_SORTING = 0;
int const BEG_OF_ARRAY_TREE = 0;

void mergeSort(Pair*, int, int);
bool requests(char*, BinaryTree<Pair>&);
int requestRemoveall(BinaryTree<Pair>&);

int main(int argc, char* argv[]) {
	//argc = GIVEN_MAIN_PARAM;
	if (argc == GIVEN_MAIN_PARAM) {
		argv[NUM_OF_AS_PAR] = "test.bin";
		ifstream binFile(argv[NUM_OF_AS_PAR], ios::in | ios::binary);
		DynamicArray<Pair> arrayOfPairs;

		if (binFile.is_open()) {
			int key = 0;
			int dataLen = 0;
			char* data;

			while (!binFile.eof() && binFile.good()) {
				binFile.read((char*)&key, INT_SIZE_READING);
				binFile.read((char*)&dataLen, INT_SIZE_READING);
				data = new char[dataLen + 1];
				binFile.read(data, dataLen);
				data[dataLen] = '\0';

				Pair newPair(key, data);
				arrayOfPairs.addNewElement(newPair);
				delete[] data;
			}
		}
		binFile.close();

		mergeSort(arrayOfPairs.getDArray(), BEG_OF_ARRAY_SORTING, 
			arrayOfPairs.getSize());
		
		BinaryTree<Pair> tree;
		tree.makePerfBalancedTree(arrayOfPairs.getDArray(),
			BEG_OF_ARRAY_TREE, arrayOfPairs.getSize());

		cout << "Enter your request: " << endl;
		char request[REQUEST_NAME_LEN];
		cin.getline(request, REQUEST_NAME_LEN);
		
		while (!cin.eof()) {
			if (strcmp(request, "removeall") == 0) {
				int counter = 0;
				counter = requestRemoveall(tree);
				cout << "The number of items removed: " << counter << endl;
			}
			else {
				cout << boolalpha << requests(request, tree) << endl;
			}

			cout << "Enter your next request: " << endl;
			cin.getline(request, REQUEST_NAME_LEN);
		}
	}
	else {
		cerr << "Error: Too few or too many arguments given." << endl;
	}

	system("pause");
	return 0;
}

void mergeSort(Pair* arr, int begOfArr, int endOfArr) {
	if (begOfArr == endOfArr) {
		return;
	}

	int middle = (begOfArr + endOfArr) / 2;
	mergeSort(arr, begOfArr, middle);
	mergeSort(arr, middle + 1, endOfArr);

	int i = begOfArr;
	int j = middle + 1;
	int l = (endOfArr - begOfArr) + 1;

	Pair* tmpArr = new Pair[l];

	for (int k = 0; k < l; k++) {
		if (j > endOfArr || (i <= middle && arr[i] < arr[j])) {
			tmpArr[k] = arr[i];
			i++;
		}
		else {
			tmpArr[k] = arr[j];
			j++;
		}
	}

	for (int k = 0, i = begOfArr; k < l; k++, i++) {
		arr[i] = tmpArr[k];
	}

	delete[] tmpArr;
}

bool requests(char* request, BinaryTree<Pair>& pairsTree) {

	if (strcmp(request, "add") == 0) {
		cout << "Enter a pair to add. The pair contains a key "
			<< "and data: " << endl;
		int newKey = 0;
		cin >> newKey;
		char newData[STRING_IN_PAIR_LEN];
		//newData = new char[STRING_IN_PAIR_LEN];
		cin.getline(newData, STRING_IN_PAIR_LEN);

		Pair newPair(newKey, newData);
		
		//delete[] newData;
		return pairsTree.insert(newPair);
	}
	if (strcmp(request, "remove") == 0) {
		cout << "Enter a pair to remove. The pair contains a key "
			<< "and data: " << endl;
		int newKey = 0;
		cin >> newKey;
		char newData[STRING_IN_PAIR_LEN];
		//newData = new char[STRING_IN_PAIR_LEN];
		cin.getline(newData, STRING_IN_PAIR_LEN);
		
		Pair pairToRemove(newKey, newData);

		//delete[] newData;
		return pairsTree.remove(pairToRemove);
	}
	if (strcmp(request, "search") == 0) {
		cout << "Enter a pair to find.The pair contains a key "
			<< "and data: " << endl;
		int newKey = 0;
		cin >> newKey;
		char newData[STRING_IN_PAIR_LEN];
		//newData = new char[STRING_IN_PAIR_LEN];
		cin.getline(newData, STRING_IN_PAIR_LEN);
		
		Pair pairToFind(newKey, newData);

		//[] newData;
		return pairsTree.find(pairToFind);
	}

	cout << "Invalid command!" << endl;
	return false;
}

int requestRemoveall(BinaryTree<Pair>& pairsTree) {
	int key;
	cout << "Enter a key by which you want to remove elements: ";
	cin >> key;
	return pairsTree.remove(key);
}


