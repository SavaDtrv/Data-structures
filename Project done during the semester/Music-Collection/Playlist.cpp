#include "Playlist.h"
#include <fstream>

int const PLAYLIST_NAME_LEN = 21;

Playlist::Playlist() {
	size = STARTING_SIZE;
	maxSize = PLAYLIST_MAX_SIZE;
	curr = getFront();
}

bool Playlist::fullPlaylist() { return size == maxSize; }

Element<Song>* Playlist::getFront() const { return playlist.getFront(); }

Element<Song>* Playlist::getCurr() const { return curr; }

void Playlist::changeSong(char * backorForw) {
	if (strcmp(backorForw, "Back") == 0) {
		if (curr->prev != nullptr) {
			curr = curr->prev;
		}
		else {
			curr = playlist.getBack();
		}
	}
	else {
		if (curr->next != nullptr) {
			curr = curr->next;
		}
		else {
			curr = playlist.getFront();
		}

	}
}

bool Playlist::addSongToPlaylist(const Song& s, const User& user) {
	if (!fullPlaylist()) {
		playlist.append(s);
		size++;
		if (size >= 2) {
			sortPlaylist(user);
			curr = getFront();
		}
		return true;
	}
	else {
		cerr << "ERROR: Playlist is full. Make a new one." << endl;
		return false;
	}
}

void Playlist::sortPlaylist(const User& user) {
	Element<Song> *marker, *current;

	for (marker = playlist.getFront()->next; marker != nullptr; marker = marker->next)
	{
		Song temp = marker->data;
		current = marker;

		while (current->prev != nullptr)
		{
			if (isFromUserFavGenres(user, current)) {
				if (current->prev->data >= temp) {
					current->data = current->prev->data;
					current = current->prev;
				}
			}
			else {
				if (current->prev->data >= temp) {
					current->data = current->prev->data;
					current = current->prev;
				}
			}
		}
		current->data = temp;
	}
}

void Playlist::savePlaylist(char* path) {
	char playlistName[PLAYLIST_NAME_LEN];
	cout << "Enter name for the playlist: ";
	cin >> playlistName;
	cout << endl;
	char plFilePath[FULL_PATH_NAME_LEN];
	sprintf(plFilePath, "%s\\%s", path, playlistName);

	ofstream pl(plFilePath, ios::out | ios::binary);
	if (pl.is_open()) {
		int sizeOfPlaylist = sizeof(this);
		pl.write((char*)&sizeOfPlaylist, sizeof(int));
		pl.write((char*)&*this, sizeOfPlaylist);
	}
	pl.close();
}

void Playlist::loadPlaylist(char* path) {
	char playlistName[PLAYLIST_NAME_LEN];
	cout << "Enter the name of the playlist: ";
	cin >> playlistName;
	cout << endl;
	char plFilePath[FULL_PATH_NAME_LEN];
	sprintf(plFilePath, "%s\\%s", path, playlistName);

	ifstream pl(plFilePath, ios::in | ios::binary);
	if (pl.is_open()) {
		int sizeOfPlaylist = 0;
		pl.read((char*)&sizeOfPlaylist, sizeof(int));
		pl.read((char*)&*this, sizeOfPlaylist);
	}
	pl.close();

	curr = getFront();
}
