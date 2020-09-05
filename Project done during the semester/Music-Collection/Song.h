#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "constVariablesForMain.h"
#include <iostream>

using namespace std;

int const BEFORE_AFTER_SPEC_YEAR = 1990;
int const PERSON_VOTED = 1;
int const EARLIEST_RELEASE_YEAR = 1945;
int const LOWEST_RATING = 0;
int const LOWEST_NUM_PEOPLE_VOTED = 0;
//името на песента и нейния изпълнител, жанр, албум, година на издаване и рейтинг.

class Song {
private:
	char* songName;
	char* artist;
	char* genre;
	char* fromAlbum;
	int releaseYear;
	int songRating;
	int peopleVoted;

public:
	Song();
	Song(char* _songName, char* _artist, char* _genre, char* _fromAlbum, 
		int _releaseYear, int _songRating, int _peopleVoted);
	Song(const Song& other);
	Song& operator=(const Song& other);
	~Song();

	void setSongName(char* newName);
	void setSongArtist(char* newArtist);
	void setGenre(char* newGenre);
	void setAlbumName(char* newAlbumName);
	void setReleaseYear(int newReleaseYear);
	void setRating(int newRating);
	void setPeopleVoted(int newNum);


	const char* getSongName() const;
	const char* getArtist() const;
	const char* getGenre() const;
	const char* getAlbum() const;
	int getReleaseYear() const;
	int getSongRating() const;
	int getPeopleWhoVoted() const;

	void changeSongRatWhileWorking(int numberToAdd); //for increasing the rating

	bool operator>=(const Song& other) {
		if (songRating >= other.songRating) {
			if (releaseYear >= BEFORE_AFTER_SPEC_YEAR && 
				other.releaseYear >= BEFORE_AFTER_SPEC_YEAR) {
				return true;
			}
		}

		return false;
	}

	friend ostream& operator<<(ostream& os, const Song& mySong) {
		os << "Song name: " << mySong.getSongName() << '\n'
			<< "Artist: " << mySong.getArtist() << '\n'
			<< "Genre: " << mySong.getGenre() << '\n'
			<< "Album: " << mySong.getAlbum() << '\n'
			<< "Released: " << mySong.getReleaseYear() << '\n'
			<< "Rating: " << mySong.getSongRating() << '\n'
			<< "Votes: " << mySong.getPeopleWhoVoted() << endl;

			return os;
	}
	friend istream& operator>>(istream& is, Song& newSong) {
		char _songName[NAMES_LEN], _artist[NAMES_LEN], _genre[GENRE_LEN], _fromAlbum[NAMES_LEN];
		int _releaseYear, _songRating, _peopleVoted;
		cout << "Enter the name of the song: ";
		cin >> _songName;
		cout << "Enter the name of the artist: ";
		cin >> _artist;
		cout << "Enter the genre of the song: ";
		cin >> _genre;
		cout << "Enter the name of the album: ";
		cin >> _fromAlbum;
		cout << "Enter the release year of the song: ";
		cin >> _releaseYear;
		cout << "Enter the rating of the song so far: ";
		cin >> _songRating;
		cout << "Enter the number of people who voted for the song: ";
		cin >> _peopleVoted;

		newSong.setSongName(_songName);
		newSong.setSongArtist(_artist);
		newSong.setGenre(_genre);
		newSong.setAlbumName(_fromAlbum);
		newSong.setReleaseYear(_releaseYear);
		newSong.setRating(_songRating);
		newSong.setPeopleVoted(_peopleVoted);

		return is;
	}

private:

	void changeOfPeopleWhoVoted(int voted = PERSON_VOTED) {
		peopleVoted += voted;
	}

	void copySong(const Song& other) {
		setSongName(other.songName);
		setSongArtist(other.artist);
		setGenre(other.genre);
		setAlbumName(other.fromAlbum);
		setReleaseYear(other.releaseYear);
		setRating(other.songRating);
		peopleVoted = other.peopleVoted;
	}

	void deleteSong() {
		delete[] songName;
		songName = nullptr;
		delete[] artist;
		artist = nullptr;
		delete[] genre;
		genre = nullptr;
		delete[] fromAlbum;
		fromAlbum = nullptr;
	}
};