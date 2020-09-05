#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct StackElement {
	T data; 
	StackElement* next;
};

template <typename T>
class LinkedStack {
private:
	StackElement<T>* top; 

	void copy(LinkedStack const&);

public:
	LinkedStack();
	LinkedStack(LinkedStack const&);
	LinkedStack& operator=(LinkedStack const&);
	~LinkedStack();

	bool empty() const;
	T peek() const;
	void push(T const&);
	T pop();
};

template <typename T>
LinkedStack<T>::LinkedStack() {
	top = nullptr;
}

template <typename T>
bool LinkedStack<T>::empty() const {
	return top == nullptr;
}

template <typename T>
T LinkedStack<T>::peek() const {
	if (empty()) {
		cout << "Error: Trying to peek in an empty stack!\n";
		return 0;
	}

	return top->data;
}

template <typename T>
void LinkedStack<T>::push(T const& x) {
	StackElement<T>* p = new StackElement<T>;
	p->data = x;
	p->next = top;
	top = p;
}

template <typename T>
T LinkedStack<T>::pop() {
	if (empty()) {
		cout << "Error: Trying to pop from an empty stack!\n";
		return 0;
	}

	StackElement<T>* p = top;
	top = top->next;
	T x = p->data;
	delete p;
	return x;
}

template <typename T>
LinkedStack<T>::~LinkedStack() {

	StackElement<T>* toDelete;
	while (top != nullptr) {
		toDelete = top;
		top = top->next;
		delete toDelete;
	}
}

template <typename T>
void LinkedStack<T>::copy(LinkedStack const& ls)
{
	StackElement<T>* toCopy = ls.top; 
	StackElement<T>* copy; // pointer to the new element which we want to put in the new stack
	StackElement<T>* lastCopied = nullptr; //pointer to the last element pushed, so we can connect the next one to the last
	while (toCopy != nullptr) {
		copy = new StackElement<T>;

		if (top == nullptr) //if the stack is empty connect top to the new element
			top = copy;

		copy->data = toCopy->data;

		if (lastCopied != nullptr) //if we already copied an element
			lastCopied->next = copy; //connect it to the new one

		//moving the pointer
		lastCopied = copy;
		toCopy = toCopy->next;
	}
	lastCopied->next = nullptr;
}

template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack<T> const& ls)
	: top(nullptr) {
	copy(ls);
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack<T> const& ls) {
	if (this != &ls) {
		while (!empty()) pop();
		copy(ls);
	}

	return *this;
}
