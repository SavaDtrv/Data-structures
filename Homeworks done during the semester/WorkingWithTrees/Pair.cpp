#define _CRT_SECURE_NO_WARNINGS
#include "Pair.h"

int const DEFAULT_KEY_VALUE = 0;

Pair::Pair():data(nullptr), key(DEFAULT_KEY_VALUE) {}

Pair::Pair(int _key, char* _data) {
	key = _key;
	setData(_data);
}

Pair::~Pair() {
	deletePair();
}

Pair::Pair(const Pair& other) :data(nullptr) {
	copy(other);
}

Pair& Pair::operator=(const Pair& other) {
	if (this != &other) {
		deletePair();
		copy(other);
	}

	return *this;
}

char* Pair::getData() const { return data; }
int Pair::getKey() const { return key; }

void Pair::setKey(int newKey) {
	key = newKey;
}

void Pair::setData(char* newData) {
	if (data != nullptr) {
		deletePair();
	}

	int dataLen = strlen(newData);
	data = new char[dataLen + 1];
	strcpy(data, newData);
}

bool Pair::operator==(const Pair& other) const {
	if (key == other.key) {
		if (strcmp(data, other.data) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Pair::operator==(const int _key) const {
	return key == _key;
}

bool Pair::operator>(const Pair& other) const {
	return key > other.key;
}

bool Pair::operator<(const Pair& other) const {
	return key < other.key;
}
