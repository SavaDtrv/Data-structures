#pragma once
#include <iostream>

using namespace std;

int const STRING_IN_PAIR_LEN = 100;

class Pair {
private:

	int key;
	char* data;

public:
	Pair();
	Pair(int, char*);
	Pair(const Pair&);
	Pair& operator=(const Pair&);
	~Pair();

	char* getData() const;
	int getKey() const;

	void setKey(int);
	void setData(char*);

	bool operator==(const Pair&) const;
	bool operator==(const int) const;
	bool operator>(const Pair&) const;
	bool operator<(const Pair&) const;
	bool operator>=(const Pair& other) const {
		return key >= other.key;
	}
	bool operator>(const int _key) const {
		return key > _key;
	}
	bool operator<(const int _key) const {
		return key < _key;
	}

	/*friend istream& operator>>(istream& is, Pair& newPair) {
		cout << "Enter key and data: ";
		int newKey = 0;
		is >> newKey;
		char newData[STRING_IN_PAIR_LEN];
		is.getline(newData, STRING_IN_PAIR_LEN);

		newPair.setKey(newKey);
		newPair.setData(newData);

		return is;
	}*/

private:

	void deletePair() {
		delete[] data;
		data = nullptr;
	}

	void copy(const Pair& other) {
		key = other.key;
		setData(other.data);
	}
};