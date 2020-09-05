#pragma once
#include <iostream>

using namespace std;

int const INDX_FOR_FIRST_EL = 0;


template<typename T>
struct Element {
	T data;
	Element* next;
	Element* prev;

	Element(T _data = T(), Element* _prev = nullptr, Element* _next = nullptr)
		: data(_data), prev(_prev), next(_next) {}
};

template<typename T>
class DoubleLinkedList {
	Element<T>* front;
	Element<T>* back;

public:
	DoubleLinkedList();
	DoubleLinkedList(DoubleLinkedList const& other);
	DoubleLinkedList& operator=(DoubleLinkedList const& other);
	~DoubleLinkedList();

	Element<T>* getFront() const;
	Element<T>* getBack() const;

	bool insertBefore(T const& _newElement, int index);
	bool insertAfter(T const& _newElement, int index);
	bool append(T const& _newElement);

	bool deleteBefore(int index);
	bool deleteAt(int index);
	bool deleteAfter(int index);

private:
	bool empty() const {
		return front == nullptr;
	}

	void copyList(DoubleLinkedList const& other) {
		if (other.front == nullptr) {
			return;
		}

		Element<T>* toCopy = other.front;
		Element<T>* newElement = new Element<T>(toCopy->data);
		Element<T>* lastCopied = newElement;

		front = newElement;

		while (toCopy->next != nullptr) {
			toCopy = toCopy->next;
			newElement = new Element<T>(toCopy->data, lastCopied);
			lastCopied->next = newElement;
			lastCopied = newElement;
		}

		back = lastCopied;
	}

	void deleteList() {
		Element<T>* toDelete = front;
		Element<T>* tmp;
		while (toDelete != nullptr) {
			tmp = toDelete;
			toDelete = toDelete->next;
			delete tmp;
		}
	}

	Element<T>* findElement(int index) {
		Element<T>* currentElement = front;
		for (int i = 0; i < index; i++)
		{
			if (currentElement == nullptr) {
				return nullptr;
			}
			currentElement = currentElement->next;
		}
		return currentElement;
	}

	void removeFront() {
		Element<T>* toDelete = front;
		front = front->next;
		front->prev = nullptr;
		delete toDelete;
	}

	void removeBack() {
		Element<T>* toDelete = back;
		back = back->prev;
		back->next = nullptr;
		delete toDelete;
	}
};

template<typename T>
inline DoubleLinkedList<T>::DoubleLinkedList()
	:front(nullptr), back(nullptr) {}

template<typename T>
inline DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList const & other) {
	copyList(other);
}

template<typename T>
inline DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList const & other) {
	if (this != &other) {
		deleteList();
		copyList(other);
	}

	return *this;
}

template<typename T>
inline DoubleLinkedList<T>::~DoubleLinkedList() {
	deleteList();
}

template<typename T>
inline Element<T>* DoubleLinkedList<T>::getFront() const {
	if (empty()) {
		return nullptr;
	}

	return this->front;
}

template<typename T>
inline Element<T>* DoubleLinkedList<T>::getBack() const {
	if (empty()) {
		return nullptr;
	}

	return this->back;
}

template<typename T>
inline bool DoubleLinkedList<T>::insertBefore(T const& _newElement, int index) {
	if (index < INDX_FOR_FIRST_EL) {
		return false;
	}

	if (empty()) {
		Element<T>* newELem = new Element<T>(_newElement);
		front = newELem;
		back = front;
		return true;
	}

	if (index == INDX_FOR_FIRST_EL) {
		Element<T>* newElement = new Element<T>(_newElement, nullptr, front);
		front->prev = newElement;
		front = newElement;

		return true;
	}

	return insertAfter(_newElement, index - 1);
}

template<typename T>
inline bool DoubleLinkedList<T>::insertAfter(T const& _newElement, int index) {
	Element<T>* searchedElement = findElement(index);
	if (searchedElement == nullptr) {
		return false;
	}

	if (searchedElement->next == nullptr) {
		return append(_newElement);
	}

	Element<T>* newElement = new Element<T>(_newElement, searchedElement, searchedElement->next);
	searchedElement->next = newElement;
	newElement->next->prev = newElement;
	return true;
}

template<typename T>
inline bool DoubleLinkedList<T>::append(T const& _newElement) {
	if (empty()) {
		Element<T>* newELem = new Element<T>(_newElement);
		front = newELem;
		back = front;
		return true;
	}

	Element<T>* newElement = new Element<T>(_newElement, back);
	newElement->prev->next = newElement;
	back = newElement;
	return true;
}

template<typename T>
inline bool DoubleLinkedList<T>::deleteBefore(int index) {
	if (index == INDX_FOR_FIRST_EL || empty()) {
		return false;
	}
	return deleteAt(index - 1);
}

template<typename T>
inline bool DoubleLinkedList<T>::deleteAt(int index) {
	Element<T>* elemToDelete = findElement(index);
	if (!elemToDelete) {
		return false;
	}

	if (elemToDelete->prev == nullptr) {
		removeFront();
		return true;
	}

	if (elemToDelete->next == nullptr) {
		removeBack();
		return true;
	}

	elemToDelete->prev->next = elemToDelete->next;
	elemToDelete->next->prev = elemToDelete->prev;
	delete elemToDelete;
	return true;
}

template<typename T>
inline bool DoubleLinkedList<T>::deleteAfter(int index) {
	if (empty()) {
		return false;
	}

	Element<T>* searchedElement = findElement(index);
	if (!searchedElement || searchedElement->next == nullptr) {
		return false;
	}

	return deleteAt(index + 1);
}
