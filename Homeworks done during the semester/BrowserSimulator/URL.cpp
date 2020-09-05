#define _CRT_SECURE_NO_WARNINGS
#include "URL.h"

using namespace std;

int const FOR_NULL_TERM_CHAR = 1;
int const MIN_INDEX = 0;

URL::URL() {
	url = nullptr;
	timestamp = time(0);
}

URL::URL(char* newURL) {
	//not using the setURL() func because there is a problem that
	//appeared, which is not fixed, i have no idea how, this is why i made URL() and
	//not making the default value for url (=nullptr) in the argument of this constructor

	int lenght = strlen(newURL);
	url = new char[lenght + 1];
	strcpy(url, newURL);
	time(&timestamp);
}

URL::URL(const URL& other) :url(nullptr) {
	copyURL(other);
}

URL& URL::operator=(const URL& other) {
	if (this != &other) {
		deleteURL();
		copyURL(other);
	}

	return *this;
}

URL::~URL() {
	deleteURL();
}

void URL::setURL(char* newURL) {
	if (url != nullptr) {
		deleteURL();
	}

	int length = strlen(newURL);
	url = new char[length + FOR_NULL_TERM_CHAR];
	strcpy(url, newURL);
}

int URL::getURLlen() const {
	return strlen(url);
}

char* URL::getURL() const {
	return url;
}

time_t URL::getTimeStamp() const {
	return timestamp;
}

const char URL::operator[](int indx) const {
	if (indx < MIN_INDEX || indx > getURLlen()) {
		return '\0';
	}

	return url[indx];
}

bool URL::operator<=(const char* otherUrl) const {
	if (strcmp(url, otherUrl) <= 0) {
		return true;
	}
	
	return false;
}

bool URL::operator<=(const time_t & otherTStamp) const {
	if (timestamp <= otherTStamp) {
		return true;
	}

	return false;
}
