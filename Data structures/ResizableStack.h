#pragma once
#include <iostream>

using namespace std;

int const DEFAULT_CURRENT = -1; //this will also help us check if the stack is empty
int const DEFAULT_STARTING_CAPACITY = 10;

template <typename T>
class DynamicStack {
private:
	T* dStack;
	int current; // top = current
	int capacity;

	bool full() const {
		return current == capacity - 1;
	}

	void resize() {
		capacity *= 2;

		T* tmpDStack = new T[capacity];
		for (int i = 0; i <= current; i++) {
			tmpDStack[i] = dStack[i];
		}

		delete[] dStack;
		dStack = tmpDStack;

	}

	void copyStack(DynamicStack<T> const& other) {
		current = other.getCurrentElement();
		capacity = other.getCapacityOfStack();
		dStack = new T[capacity];

		for (int i = 0; i <= current; i++) {
			dStack[i] = other.getSpecificElement(i);
		}
	}

	void clearStack() {
		delete[] dStack;
	}

public:
	DynamicStack();
	DynamicStack(DynamicStack<T> const& other);
	DynamicStack<T>& operator=(DynamicStack<T> const& other);
	~DynamicStack();

	int getCurrentElement() const { return current; }
	int getCapacityOfStack() const { return capacity; }
	T getSpecificElement(int index) const { return dStack[index]; }

	bool empty() const;
	T peek() const;
	void push(T const& newELement);
	T pop();

	//operator<< is made only for the funcionality of the program
	friend ostream& operator<<(ostream& os, DynamicStack<T> const& myStack) {
		for (int i = 0; i < myStack.getCurrentElement(); i++) {
			os << myStack.getSpecificElement(i);
			if (i != 0 && (i + 1) % 100 == 0) {
				os << '\n';
			}
		}

		return os;
	}
};

template<typename T>
inline DynamicStack<T>::DynamicStack() {
	current = DEFAULT_CURRENT;
	capacity = DEFAULT_STARTING_CAPACITY;
	dStack = new T[capacity];
}

template<typename T>
inline DynamicStack<T>::DynamicStack(DynamicStack<T> const& other) {
	copyStack(other);
}

template<typename T>
inline DynamicStack<T>& DynamicStack<T>::operator=(DynamicStack<T> const& other) {
	if (this != &other) {
		clearStack();
		copyStack(other);
	}

	return *this;
}

template<typename T>
inline DynamicStack<T>::~DynamicStack() {
	clearStack();
}

template<typename T>
inline bool DynamicStack<T>::empty() const {
	return current == DEFAULT_CURRENT;
}

template<typename T>
inline T DynamicStack<T>::peek() const {
	if (empty()) {
		cerr << "Error: Peeking in empty stack!" << endl;
		return T();
	}

	return dStack[current];
}

template<typename T>
inline void DynamicStack<T>::push(T const& newELement) {
	if (full()) {
		resize();
	}

	dStack[++current] = newELement;
}

template<typename T>
inline T DynamicStack<T>::pop() {
	if (empty()) {
		cerr << "Error: No elements in the stack!" << endl;
		return T();
	}

	return dStack[current--];
}
