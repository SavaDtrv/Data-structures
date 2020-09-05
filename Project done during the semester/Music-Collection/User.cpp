#include "User.h"

User::User(char* _userName, char* _firstName, char* _lastName, char* _dateOfBirth) {
	setUserName(_userName);
	setFirstName(_firstName);
	setLastName(_lastName);
	setDateOfBirth(_dateOfBirth);
}

User::User(const User& other)
	:userName(nullptr), firstName(nullptr), lastName(nullptr), dateOfBirth(nullptr) {
	copy(other);
}

User& User::operator=(const User& other) {
	if (this != &other) {
		removeUser();
		copy(other);
	}

	return *this;
}

User::~User() {
	removeUser();
}

void User::setUserName(char* newUserName) {
	if (this->userName != nullptr) {
		delete[] userName;
		userName = nullptr;
	}

	int len = strlen(newUserName);
	userName = new char[len + 1];
	strcpy(this->userName, newUserName);
}

void User::setFirstName(char* newFirstName) {
	if (this->firstName != nullptr) {
		delete[] firstName;
		firstName = nullptr;
	}

	int len = strlen(newFirstName);
	firstName = new char[len + 1];
	strcpy(this->firstName, newFirstName);
}

void User::setLastName(char* newLastName) {
	if (this->lastName != nullptr) {
		delete[] lastName;
		lastName = nullptr;
	}

	int len = strlen(newLastName);
	lastName = new char[len + 1];
	strcpy(this->lastName, newLastName);
}

void User::setDateOfBirth(char* newDate) {
	if (this->dateOfBirth != nullptr) {
		delete[] dateOfBirth;
		dateOfBirth = nullptr;
	}

	int len = strlen(newDate);
	dateOfBirth = new char[len + 1];
	strcpy(this->dateOfBirth, newDate);
}

void User::addNewGenres(char* newGenre) {
	favGenres.addNewElement(newGenre);
}

void User::removeGenre(char* genre) {
	favGenres.removeElement(genre);
}

bool User::genreIsIn(char* genre) {
	bool flag = false;

	for (int i = 0; i <= favGenres.getSize() && !flag; i++) {
		if (strcmp(favGenres[i], genre) == 0) {
			flag = true;
		}
	}

	return flag;
}

const char* User::getUserName() const { return userName; }
const char * User::getFirstName() const { return firstName; }
const char * User::getLastName() const { return lastName; }
const char * User::getDateOfBirth() const { return dateOfBirth; }
DynamicArray<char*> User::getFavGenres() const { return favGenres; }