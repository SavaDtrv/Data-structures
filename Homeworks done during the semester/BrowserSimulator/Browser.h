#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include "DoubleLinkedList.h"
#include "URL.h"

using namespace std;
int const STRINGS_EQUALITY = 0;

class Browser {
	DoubleLinkedList<URL> tabs;
	Element<URL>* currentTab;
	int currTab;

	int getNumOfAllTabs() {
		Element<URL>* tmp = tabs.getFront();
		int numOfTabs = 0;

		while (tmp) {
			numOfTabs++;
			tmp = tmp->next;
		}
		
		return numOfTabs;
	}

	//sorting
	Element<URL>* merge(Element<URL>* leftSide, Element<URL>* rightSide, char* by) {
		if (!leftSide) {
			return rightSide;
		}
		if (!rightSide) {
			return leftSide;
		}

		if (strcmp(by, "URL") == STRINGS_EQUALITY) {
			Element<URL>* result;
			if (leftSide->data.getURL() <= rightSide->data.getURL()) {
				result = leftSide;
				leftSide = leftSide->next;
			}
			else {
				result = rightSide;
				rightSide = rightSide->next;
			}
			Element<URL>* current = result;
			while (leftSide && rightSide) {
				if (leftSide->data.getURL() <= rightSide->data.getURL()) {
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
		
		if (strcmp(by, "TIME") == STRINGS_EQUALITY) {
			Element<URL>* result;
			if (leftSide->data.getTimeStamp() <= rightSide->data.getTimeStamp()) {
				result = leftSide;
				leftSide = leftSide->next;
			}
			else {
				result = rightSide;
				rightSide = rightSide->next;
			}
			Element<URL>* current = result;
			while (leftSide && rightSide) {
				if (leftSide->data.getTimeStamp() <= rightSide->data.getTimeStamp()) {
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

	}

	Element<URL>* split(Element<URL>* list, int toWhere) {
		while (toWhere > 0) {
			list = list->next;
			toWhere--;
		}
		Element<URL>* result = list->next;
		result->next = nullptr;
		return result;
	}

	Element<URL>* mergeSort(Element<URL>* list, int sizeOfList, char* by) {
		Element<URL>* tmpELem = list;
		if (sizeOfList < 2) {
			return tmpELem;
		}

		int middle = sizeOfList / 2;
		Element<URL>* middleElem = split(tmpELem, middle);
		tmpELem = mergeSort(tmpELem, middle + 1, by);
		middleElem = mergeSort(middleElem, sizeOfList - (sizeOfList / 2 + 1), by);

		return merge(tmpELem, middleElem, by);
	}

	void fixPointers(Element<URL>* firstElem) {
		Element<URL>* tmpElem = firstElem;
		if (!tmpElem) {
			return;
		}

		tmpElem->prev = nullptr;
		while (tmpElem->next) {
			tmpElem->next->prev = tmpElem;
			tmpElem = tmpElem->next;
		}
	}
	//

public:
	Browser();
	
	void go(URL _url);
	void insert(URL _url);
	void back();
	void forward();
	void remove();
	void print();
	void sort(char* byWhat);
};