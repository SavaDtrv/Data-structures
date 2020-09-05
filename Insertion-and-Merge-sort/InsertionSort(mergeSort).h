#pragma once
#include <iostream>

using namespace std;


void insertSort() {

	ListNode *marker, *current;

	for (marker = front->next; marker != nullptr; marker = marker->next) {
		double temp = marker->data;
		current = marker;
                                       
		while (current->prev != nullptr && current->prev->data >= temp) {
			current->data = current->prev->data;
			current = current->prev;
		}
		current->data = temp;
	}
}

//merge sort
Element<T>* merge(Element<T>* leftSide, Element<T>* rightSide) {
	if (!leftSide) {
		return rightSide;
	}
	if (!rightSide) {
		return leftSide;
	}

	Element<URL>* result;
	if (leftSide->data < rightSide->data) {
		result = leftSide;
		leftSide = leftSide->next;
	}
	else {
		result = rightSide;
		rightSide = rightSide->next;
	}
	Element<URL>* current = result;
	while (leftSide && rightSide) {
		if (leftSide->data < rightSide->data) {
			current->next = leftSide;
			leftSide = leftSide->next;
		}
		else {
			current->next = rightSide;
			rightSide = rightSide->next;
		}
		current = current->next;
	}
	return result;
}

Element<T>* split(Element<T>* list, int toWhere) {
	while (toWhere > 0) {
		list = list->next;
		toWhere--;
	}
	Element<T>* result = list->next;
	result->next = nullptr;
	return result;
}

Element<T>* mergeSort(Element<T>* list, int sizeOfList) {
	Element<T>* tmpELem = list;
	if (sizeOfList < 2) {
		return tmpELem;
	}

	int middle = sizeOfList / 2;
	Element<T>* middleElem = split(tmpELem, middle);
	tmpELem = mergeSort(tmpELem, middle + 1);
	middleElem = mergeSort(middleElem, sizeOfList - (sizeOfList / 2 + 1));

	return merge(tmpELem, middleElem);
}

void fixPointers(Element<T>* firstElem) {
	Element<T>* tmpElem = firstElem;
	if (!tmpElem) {
		return;
	}

	tmpElem->prev = nullptr;
	while (tmpElem->next) {
		tmpElem->next->prev = tmpElem;
		tmpElem = tmpElem->next;
	}
}