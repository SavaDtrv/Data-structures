#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <ctime>

using namespace std;

class URL {
	char* url;
	time_t timestamp;
	
public:
	URL();
	URL(char* newURL);
	URL(const URL& other);
	URL& operator=(const URL& other);
	~URL();

	void setURL(char* newURL);

	int getURLlen() const;
	char* getURL() const;
	time_t getTimeStamp() const;

	const char operator[](int indx) const;
	bool operator<=(const char* otherUrl) const;
	bool operator<=(const time_t& otherUrl) const;

	friend ostream& operator<<(ostream& os, const URL& myURL) {
		for (int i = 0; i < myURL.getURLlen(); i++)
		{
			os << myURL[i];
		}
		os << " " << myURL.getTimeStamp() << endl;

		return os;
	}

private:

	void copyURL(const URL& other) {
		setURL(other.getURL());
		timestamp = other.getTimeStamp();
	}

	void deleteURL() {
		delete[] url;
		url = nullptr;
	}
};