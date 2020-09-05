#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <direct.h>
#include "DoubleLinkedList.h"
#include "Playlist.h"
#include "Song.h"
#include "User.h"
#include "dirent.h"

using namespace std;

class MusicalCollection {
private:
	int serviceNum;

public:
	MusicalCollection(int _serviceNum) :serviceNum(_serviceNum) {}


	//I'm using string only for the password so i can mask it while it is being entered and encrypt it when saved.
	//I know it is forbiden but i tried with [char <name>[<size>]] but i could find a function to help out with
	//that implementation and couldn't think of how to make it.

	void maskPassword(string& password);

	string encryptDecrypt(string toEncrypt);

	bool userReallyExisting(char* path, char* userName);

	void makeFolders(DIR *directory, char* path);

	void changeUserData(User& user);

	void addSongToArchive(const Song& song, char* usersPath);

	void makeNewPlaylist(Playlist& userPlaylist, char* playlistPath, const User& user, char* pathUserFolder);

	void whatToDoWithThePL(Playlist& userPlaylist, char* path, const User& user, char* pathUserFolder);

	void regORexisting();

	void loadAllUserArchivedSongs(DoubleLinkedList<Song>& userSongs, char* pathToFolder);

	void makePathsAndCopyData(const string& password, const User& user);

	void registration();

	void existing();

	void musicalCollection(User& user, DoubleLinkedList<Song>& userSongs, 
		Playlist& userPlaylist, char* pathUserFolder, char* playlistPath);


private:

};