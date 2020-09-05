#define _CRT_SECURE_NO_WARNINGS
#include "Browser.h"

int const DEFAULT_CURR_TAB = 1;
int const DEFAULT_INDX_OF_TABS = 0;
int const EQUAL_STRINGS = 0;

Browser::Browser() {
	URL newURL("about:blank");
	currTab = DEFAULT_CURR_TAB;
	tabs.insertBefore(newURL, currTab - 1);
	currentTab = tabs.getFront();
}

void Browser::go(URL _url) {
	currentTab->data = _url;
}

void Browser::insert(URL _url) {
	if (tabs.insertBefore(_url, currTab - 1)) {
		currentTab = currentTab->next;
		currTab++;
	}
	else {
		cerr << "Error: There was a problem with inserting a new tab." << endl;
	}
}

void Browser::back() {
	if (currentTab->prev == nullptr) {
		currentTab = tabs.getBack();
		currTab = getNumOfAllTabs();
	}
	else {
		currentTab = currentTab->prev;
		currTab--;
	}
}

void Browser::forward() {
	if (currentTab->next == nullptr) {
		currentTab = tabs.getFront();
		currTab = DEFAULT_CURR_TAB;
	}
	else {
		currentTab = currentTab->next;
		currTab++;
	}
}

void Browser::remove() {
	tabs.deleteAt(currTab - 1);

	if (getNumOfAllTabs() == DEFAULT_INDX_OF_TABS) {
		URL forEmptyList("about:blank");
		currTab = DEFAULT_CURR_TAB;
		tabs.insertBefore(forEmptyList, currTab - 1);
		currentTab = tabs.getFront();
		return;
	}

	if (currentTab->next != nullptr) {
		currentTab = currentTab->next;
		return;
	}
	else {
		currentTab = currentTab->prev;
		return;
	}
}

void Browser::print() {
	Element<URL>* tmpForPrint = tabs.getFront();
	int checkForCurrTab = DEFAULT_INDX_OF_TABS;

	while (tmpForPrint != nullptr) {
		if (checkForCurrTab != currTab - 1) {
			cout << tmpForPrint->data << endl;
		}
		else {
			cout << "> " << tmpForPrint->data << endl;
		}

		tmpForPrint = tmpForPrint->next;
		checkForCurrTab++;
	}
}

void Browser::sort(char * byWhat) {
	mergeSort(tabs.getFront(), getNumOfAllTabs(), byWhat);
	fixPointers(tabs.getFront());
}
