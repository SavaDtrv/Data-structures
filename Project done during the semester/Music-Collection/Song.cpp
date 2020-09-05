#include "Song.h"

using namespace std;

int const LOWEST_SONG_RATING = 0;
int const HIGHEST_SONG_RATING = 10;


Song::Song() :songName(nullptr), artist(nullptr), genre(nullptr), fromAlbum(nullptr) {
	releaseYear = EARLIEST_RELEASE_YEAR;
	songRating = LOWEST_RATING;
	peopleVoted = LOWEST_NUM_PEOPLE_VOTED;
}

Song::Song(char * _songName, char * _artist, char * _genre,
	char * _fromAlbum, int _releaseYear, int _songRating, int _peopleVoted) {
	setSongName(_songName);
	setSongArtist(_artist);
	setGenre(_genre);
	setAlbumName(_fromAlbum);
	setReleaseYear(_releaseYear);
	setRating(_songRating);
	peopleVoted = _peopleVoted;
}

Song::Song(const Song & other) 
	:songName(nullptr), artist(nullptr), genre(nullptr), fromAlbum(nullptr) {
	copySong(other);
}

Song & Song::operator=(const Song & other) {
	if (this != &other) {
		deleteSong();
		copySong(other);
	}

	return *this;
}

Song::~Song() {
	deleteSong();
}

void Song::setSongName(char* newName) {
	if (this->songName != nullptr) {
		delete[] songName;
		songName = nullptr;
	}

	int len = strlen(newName);
	songName = new char[len + 1];
	strcpy(this->songName, newName);
}

void Song::setSongArtist(char* newArtist) {
	if (this->artist != nullptr) {
		delete[] artist;
		artist = nullptr;
	}

	int len = strlen(newArtist);
	artist = new char[len + 1];
	strcpy(this->artist, newArtist);
}

void Song::setGenre(char* newGenre) {
	if (this->genre != nullptr) {
		delete[] genre;
		genre = nullptr;
	}

	int len = strlen(newGenre);
	genre = new char[len + 1];
	strcpy(this->genre, newGenre);
}

void Song::setAlbumName(char* newAlbumName) {
	if (this->fromAlbum != nullptr) {
		delete[] fromAlbum;
		fromAlbum = nullptr;
	}

	int len = strlen(newAlbumName);
	fromAlbum = new char[len + 1];
	strcpy(this->fromAlbum, newAlbumName);
}

void Song::setReleaseYear(int newReleaseYear) {
	if (newReleaseYear >= EARLIEST_RELEASE_YEAR) {
		releaseYear = newReleaseYear;
		return;
	}
	else {
		cerr << "ERROR: Not a valid release year!" << endl;
		cout << "Input again: ";
		cin >> newReleaseYear;
		cout << endl;
		setReleaseYear(newReleaseYear);
	}
}

void Song::setRating(int newRating) {
	if (newRating >= LOWEST_SONG_RATING && 
		newRating <= HIGHEST_SONG_RATING) {
		songRating = newRating;
		return;
	}
	else {
		cerr << "ERROR: Not a valid value for the rating." << endl;;
		cout << "Song ratings have a number between 0 and 10."
			<< " Input new value for the rating: " << endl;
		cin >> newRating;
		setRating(newRating);
	}
}

void Song::setPeopleVoted(int newNum) {
	peopleVoted = newNum;
}

const char* Song::getSongName() const { return this->songName; }
const char * Song::getArtist() const { return this->artist; }
const char* Song::getGenre() const { return this->genre; }
const char * Song::getAlbum() const { return this->fromAlbum; }
int Song::getReleaseYear() const { return this->releaseYear; }
int Song::getSongRating() const { return this->songRating; }
int Song::getPeopleWhoVoted() const { return this->peopleVoted; }

void Song::changeSongRatWhileWorking(int ratingToAdd) {
	if (ratingToAdd >= LOWEST_SONG_RATING &&
		ratingToAdd <= HIGHEST_SONG_RATING) {
		int currentWholeRat = songRating * peopleVoted;
		currentWholeRat += ratingToAdd;
		changeOfPeopleWhoVoted();

		setRating(currentWholeRat/peopleVoted);
	}
}

