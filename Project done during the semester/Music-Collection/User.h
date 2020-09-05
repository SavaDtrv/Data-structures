#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "constVariablesForMain.h"
#include <iostream>
#include "DynamicArray(genres).h"

using namespace std;

class User {
private:
	//User data needed to access the system
	char* userName;
	//User real name and birth date
	char* firstName;
	char* lastName;
	char* dateOfBirth;
	DynamicArray<char*> favGenres;

public:
	User() {
		userName = nullptr; 
		firstName = nullptr;
		lastName = nullptr;
		dateOfBirth = nullptr;
	}

	User(char* _userName, char* _firstName, char* _lastName, char* _dateOfBirth);
	User(const User& other);
	User& operator=(const User& other);
	~User();

	void setUserName(char* newUserName);
	void setFirstName(char* newFirstName);
	void setLastName(char* newLastName);
	void setDateOfBirth(char* newDate);

	void addNewGenres(char* newGenre);
	void removeGenre(char* genre);
	bool genreIsIn(char* genre);

	const char* getUserName() const;
	const char* getFirstName() const;
	const char* getLastName() const;
	const char* getDateOfBirth() const;
	DynamicArray<char*> getFavGenres() const;
	int getArraySize() const { return favGenres.getSize(); }


	friend ostream& operator<<(ostream& os, const User& user) {
		os << "User name: " << user.getUserName() << "\n"
			<< "First name: " << user.getFirstName() << "\n"
			<< "Last name: " << user.getLastName() << "\n"
			<< "Birth date: " << user.getDateOfBirth() << "\n"
			<< "Favourite music genres: " << user.getFavGenres() << endl;
	}

private:
	void copy(const User& other) {
		setUserName(other.userName);
		setFirstName(other.firstName);
		setLastName(other.lastName);
		setDateOfBirth(other.dateOfBirth);
		favGenres = other.favGenres;
	}

	void removeUser() {
		delete[] userName;
		userName = nullptr;
		delete[] firstName;
		firstName = nullptr;
		delete[] lastName;
		lastName = nullptr;
		delete[] dateOfBirth;
		dateOfBirth = nullptr;
	}
};