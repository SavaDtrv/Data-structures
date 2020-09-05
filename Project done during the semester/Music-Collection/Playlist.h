#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include "constVariablesForMain.h"
#include "DoubleLinkedList.h"
#include "Song.h"
#include "User.h"

using namespace std;

int const PLAYLIST_MAX_SIZE = 30;
int const STARTING_SIZE = -1;

class Playlist {
private:
	DoubleLinkedList<Song> playlist;
	int size;
	int maxSize;
	Element<Song>* curr;
public:
	Playlist();
	
	bool fullPlaylist();

	Element<Song>* getFront() const;
	Element<Song>* getCurr() const;

	void changeSong(char* backorForw);

	bool addSongToPlaylist(const Song& s, const User& user);
	void sortPlaylist(const User& user);

	void savePlaylist(char* path);
	void loadPlaylist(char* path);

	friend ostream& operator<<(ostream& os, const Playlist& myPL) {
		Element<Song>* current = myPL.getFront();
		for (int i = 0; current != nullptr; i++) {
			if (myPL.getCurr() == current) {
				cout << "current > ";
			}
			if (i == 0) {
				os << i + 1 << "st song: " << current->data << endl;
			}
			if (i == 1) {
				os << i + 1 << "nd song: " << current->data << endl;
			}
			if (i == 2) {
				os << i + 1 << "rd song: " << current->data << endl;
			}
			os << i + 1 << "th song: " << current->data << endl;
		}

		return os;
	}
private:

	bool isFromUserFavGenres(const User& user, Element<Song>* current) {
		for (int i = 0; i < user.getArraySize(); i++) {
			if (strcmp(user.getFavGenres()[i], current->prev->data.getGenre()) == 0) {
				return true;
			}
		}

		return false;
	}

	bool emptyPlaylist() {
		return size == 0;
	}
};