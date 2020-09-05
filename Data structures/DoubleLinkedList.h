#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct ListElem {
	T data;
	ListElem<T>* prev;
	ListElem<T>* next;

	ListElem(T _data = T(), ListElem<T>* _prev = nullptr, ListElem<T>* _next = nullptr)
		:data(_data), prev(_prev), next(_next) {}
};

template <typename T>
class DLList {
private:
	ListElem<T>* front;
	ListElem<T>* back;
public:
	DLList();
	DLList(const DLList<T>& other);
	DLList<T>& operator=(const DLList& other);
	~DLList();

	ListElem<T>* getFront() const;
	ListElem<T>* getBack() const;

	bool append(const T& _newElement);
	bool insertBefore(int index, const T& _newElement);
	bool insertAfter(int index, const T& _newElement);

	bool deleteAt(int index);
	bool deleteBefore(int index);
	bool deleteAfter(int index);

private:
	bool empty() const {
		return front == nullptr;
	}

	void remove() {
		ListElem<T>* toDelete = front;
		ListElem<T>* tmp;
		while (toDelete != nullptr) {
			tmp = toDelete;
			toDelete = toDelete->next;
			delete tmp;
		}
	}

	void copyList(const DLList<T>& other) {
		if (other.front == nullptr) {
			return;
		}

		ListElem<T>* toCopy = other.front;
		ListElem<T>* newElem = new ListElem<T>(toCopy->data);
		ListElem<T>* lastCopied = newElem;

		front = newElem;

		while (toCopy->next != nullptr) {
			toCopy = toCopy->next;
			newElem = new ListElem<T>(toCopy->data, lastCopied);
			lastCopied->next = newElem;
			lastCopied = newElem;
		}

		back = lastCopied;
	}

	ListElem<T>* findElement(int index) {
		ListElem<T>* currentElem = front;
		for (int i = 0; i < index; i++) {

			if (currentElem == nullptr) {
				return nullptr;
			}
			
			currentElem = currentElem->next;
		}
		return currentElem;
	}
};

template<typename T>
inline DLList<T>::DLList()
	: front(nullptr), back(nullptr) {}

template<typename T>
inline DLList<T>::DLList(const DLList<T>& other) {
	copyList(other);
}

template<typename T>
inline DLList<T>& DLList<T>::operator=(const DLList & other) {
	if (this != &other) {
		remove();
		copyList(other);
	}

	return *this;
}

template<typename T>
inline DLList<T>::~DLList() {
	remove();
}

template<typename T>
inline ListElem<T>* DLList<T>::getFront() const { 
	if (empty()) {
		return nullptr;
	}
	return front; 
}

template<typename T>
inline ListElem<T>* DLList<T>::getBack() const { 
	if (empty()) {
		return nullptr;
	}

	return back; 
}

template<typename T>
inline bool DLList<T>::append(const T & _newElement) {
	if (empty()) {
		ListElem<T>* newElem = new ListElem<T>(_newElement);
		front = newELem;
		back = front;
		return true;
	}

	ListElem<T>* newElem = new ListElem<T>(_newElement, back);
	newElem->prev->next = newElem;
	back = newElem;
	return true;
}

template<typename T>
inline bool DLList<T>::insertBefore(int index, const T & _newElement) {
	if (index < 0) {
		return false;
	}

	if (empty()) {
		ListElem<T>* newElem = new ListElem<T>(_newElement);
		front = newELem;
		back = front;
		return true;
	}

	if (index == 0) {
		ListElem<T>* newElem = new ListElem<T>(_newElement, nullptr, front);
		front->prev = newELem;
		front = newELem;
		return true;
	}

	return insertAfter(index, _newElement);
}

template<typename T>
inline bool DLList<T>::insertAfter(int index, const T & _newElement) {
	ListElem<T>* searchedElem = findElement(index);
	if (searchedElem == nullptr) {
		return false;
	}
	
	if (searchedElem->next == nullptr) {
		return append(_newElement);
	}
	
	ListElem<T>* newElem = new ListElem<T>(_newElement, searchedElem, searchedElem->next);
	searchedElem->next = newElem;
	newElem->next->prev = newELem;
	return true;
}

template<typename T>
inline bool DLList<T>::deleteAt(int index) {
	ListElem<T>* elemToDelete = findElement(index);

	if (elemToDelete == nullptr) {
		return false;
	}

	elemToDelete->prev->next = elemToDelete->next;
	elemToDelete->next->prev = elemToDelete->prev;
	delete elemToDelete;
	return false;
}

template<typename T>
inline bool DLList<T>::deleteBefore(int index) {
	if (index == 0 || empty()) {
		return false;
	}

	return deleteAt(index - 1);
}

template<typename T>
inline bool DLList<T>::deleteAfter(int index) {
	if (empty()) {
		return false;
	}

	ListElem<T>* elemToDelete = findElement(index);
	if (elemToDelete == nullptr || elemToDelete->next == nullptr) {
		return false;
	}

	return deleteAt(index + 1);
}
