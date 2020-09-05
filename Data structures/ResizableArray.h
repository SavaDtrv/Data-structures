#pragma once
#include <iostream>

using namespace std;

int const DEFAULT_SIZE = -1;
int const DEFAULT_START_CAPACITY = 10;

template <typename T>
class DynamicArray {
private:
	T* dArray;
	int size;
	int capacity;

	bool fullArray() {
		return size == capacity - 1;
	}

	void resize() {

		capacity *= 2;
		T* tmpDArray = new T[capacity];
		for (int i = 0; i <= size; i++) {
			tmpDArray[i] = dArray[i];
		}

		delete[] dArray;
		dArray = tmpDArray;
	}

	void copyArray(DynamicArray<T> const& other) {
		size = other.getSize();
		capacity = other.getCapacity();
		dArray = new T[capacity];

		for (int i = 0; i <= size; i++) {
			dArray[i] = other.getAt(i);
		}
	}

	void clearArray() {
		delete[] dArray;
	}

public:
	DynamicArray();
	DynamicArray(DynamicArray<T> const& other);
	DynamicArray<T>& operator=(DynamicArray<T> const& other);
	~DynamicArray();

	int getSize() const { return size; }
	int getCapacity() const { return capacity; }
	T getAt(int index) const { return dArray[index]; }

	void addNewElement(T newElement);

};

template<typename T>
inline DynamicArray<T>::DynamicArray() {
	size = DEFAULT_SIZE;
	capacity = DEFAULT_START_CAPACITY;
	dArray = new T[capacity];
}

template<typename T>
inline DynamicArray<T>::DynamicArray(DynamicArray<T> const & other) {
	copyArray(other);
}

template<typename T>
inline DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T> const & other) {
	if (this != &other) {
		clearArray();
		copyArray(other);
	}

	return *this;
} 

template<typename T>
inline DynamicArray<T>::~DynamicArray() {
	clearArray();
}

template<typename T>
inline void DynamicArray<T>::addNewElement(T newElement) {
	if (fullArray()) {
		resize();
	}

	size++;
	dArray[size] = newElement;
}