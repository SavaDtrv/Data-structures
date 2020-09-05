#include "MusicalCollection.h"

void MusicalCollection::maskPassword(string & password) {
	//This function is found on the internet.
	cout << "\n" << "Enter your password: " << endl;
	password = "";
	char ch;
	ch = _getch();
	while (ch != 13) { //character 13 is enter
		password.push_back(ch);
		cout << '*';
		ch = _getch();
	}
}

string MusicalCollection::encryptDecrypt(string toEncrypt) {
	char key = 'K'; //Any char will work
	string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key;

	return output;
}

bool MusicalCollection::userReallyExisting(char * path, char * userName) {
	DIR *directory = opendir(path);
	if (!directory) {
		return false;
	}

	dirent *entry;
	while (entry = readdir(directory)) {
		if (entry->d_type == DT_REG &&
			strcmp(entry->d_name, userName) == 0) {
			return true;
		}
	}
	closedir(directory);

	return false;
}

void MusicalCollection::makeFolders(DIR * directory, char * path) {
	if (!directory) {
		_mkdir(path);
	}
}

void MusicalCollection::changeUserData(User & user) {
	cout << "Choose the data you want to change\\optimize:\n"
		<< "\t1: User name.\n\t2: First name.\n\t3: Last name.\n"
		<< "\t4: Add new favourite genre.\n\t5: Remove a favourite genre.\n"
		<< "\t6: To finish changing/optimizing" << endl;
	int whatToChange;
	char changeNames[MAX_NAMES_LEN];
	char changeBirthDate[BIRTH_DATE_LEN];
	char changeGenres[MAX_GENRE_NAME_LEN];
	do {

		cin >> whatToChange;
		if (whatToChange == USER_NAME_CHANGE_NUM) {
			cout << "Input your new user name: ";
			cin >> changeNames;
			cout << endl;
			user.setUserName(changeNames);
		}
		else if (whatToChange == FIRST_NAME_CHANGE_NUM) {
			cout << "Input your new first name: ";
			cin >> changeNames;
			cout << endl;
			user.setFirstName(changeNames);
		}
		else if (whatToChange == LAST_NAME_CHANGE_NUM) {
			cout << "Input your new last name: ";
			cin >> changeNames;
			cout << endl;
			user.setLastName(changeNames);
		}
		else if (whatToChange == ADD_GENRE_NUM) {
			cout << "Input new genre to add: ";
			cin >> changeGenres;
			cout << endl;
			user.addNewGenres(changeGenres);
		}
		else if (whatToChange == REMOVE_GENRE_NUM) {
			cout << "Input genre to remove: ";
			cin >> changeGenres;
			cout << endl;
			user.removeGenre(changeGenres);
		}

	} while (whatToChange != FINISH_CHANGING_NUM &&
		(whatToChange >= INTERVAL_START_NUM && whatToChange <= INTERVAL_FINISH_NUM));

	cout << "Changing your data finalized." << endl;
}

void MusicalCollection::addSongToArchive(const Song & song, char * usersPath) {
	char songsFoldPath[FULL_PATH_NAME_LEN];
	sprintf(songsFoldPath, "%s\\%s", usersPath, "Songs");
	char songNamePath[FULL_PATH_NAME_LEN];
	sprintf(songNamePath, "%s\\%s", songsFoldPath, song.getSongName());
	char songExtansion[FULL_PATH_NAME_LEN];
	sprintf(songExtansion, songNamePath, ".sg");

	ofstream songFile(songExtansion, ios::out | ios::binary);
	if (songFile.is_open()) {
		int songSize = sizeof(song);
		songFile.write((char*)&songSize, sizeof(int));
		songFile.write((char*)&song, songSize);
	}
	songFile.close();
}

void MusicalCollection::makeNewPlaylist(Playlist & userPlaylist, char * playlistPath, const User & user, char* pathUserFolder) {
	char stop[STOP_ADDING];
	cout << "If you want to stop adding songs to the playlist type: Done. Before entering the song name." << endl;
	Song song;
	while (strcmp(stop, "Done") != 0 && !(userPlaylist.fullPlaylist())) {
		cin >> song;
		userPlaylist.addSongToPlaylist(song, user);
		addSongToArchive(song, pathUserFolder);
		cout << "If you want to stop adding type Done." << endl;
		cin >> stop;
	}
	cout << "You entered all songs you wanted. Playlist is being saved in your profile." << endl;
	userPlaylist.savePlaylist(playlistPath);
}

void MusicalCollection::whatToDoWithThePL(Playlist & userPlaylist, char * path, const User & user, char* pathUserFolder) {
	char command[MAKE_LOAD];
	cout << "What you want to do with the playlist, make new one or load an existing one. "
		<< "use one of the words: Make or Load." << endl;
	cin >> command;

	if (strcmp(command, "Make") == 0) {
		makeNewPlaylist(userPlaylist, path, user, pathUserFolder);
		return;
	}
	if (strcmp(command, "Load") == 0) {
		userPlaylist.loadPlaylist(path);
		return;
	}
}

void MusicalCollection::regORexisting() {
	switch (serviceNum)
	{
		case 1: registration(); break;
		case 2: existing(); break;
		default: return;
	}
}

void MusicalCollection::loadAllUserArchivedSongs(DoubleLinkedList<Song>& userSongs, char * pathToFolder) {
	char songsFoldPath[FULL_PATH_NAME_LEN];
	sprintf(songsFoldPath, "%s\\%s", pathToFolder, "Songs");

	DIR *directory = opendir(songsFoldPath);
	if (!directory) {
		return;
	}

	dirent *entry;
	while (entry = readdir(directory)) {
		if (entry->d_type == DT_REG) {
			ifstream song(entry->d_name, ios::in | ios::binary);
			int sizeOfSong = 0;
			Song s;
			if (song.is_open()) {
				song.read((char*)&sizeOfSong, sizeof(int));
				song.read((char*)&s, sizeOfSong);
			}
			song.close();
			userSongs.append(s);
		}
	}
	closedir(directory);
}

void MusicalCollection::makePathsAndCopyData(const string & password, const User & user) {
	char sysPath[] = "./SystemData";
	DIR *directory = opendir(sysPath);
	makeFolders(directory, sysPath);

	char fullPath[FULL_PATH_NAME_LEN];
	char fileNameExtantion[FILE_NAME_EXTAN_LEN];
	sprintf(fileNameExtantion, user.getUserName(), ".data");
	sprintf(fullPath, "%s\\%s", sysPath, fileNameExtantion);
	ofstream destination(fullPath, ios::out | ios::binary);


	char usersPath[] = "../USERS";
	DIR *directory1 = opendir(usersPath);
	makeFolders(directory1, usersPath);

	char fullUserPath[FULL_PATH_NAME_LEN];
	sprintf(fullUserPath, "%s\\%s", usersPath, user.getUserName());
	directory1 = opendir(fullUserPath);
	makeFolders(directory1, fullUserPath);

	char userDataPath[FULL_PATH_NAME_LEN];
	sprintf(userDataPath, "%s\\%s", fullUserPath, "userData.data");
	ofstream userData(userDataPath, ios::out | ios::binary);
	int userSize = sizeof(user);
	userData.write((char*)&userSize, sizeof(int));
	userData.write((char*)&user, userSize);

	char songFolderPath[FULL_PATH_NAME_LEN];
	sprintf(songFolderPath, "%s\\%s", fullUserPath, "Songs");
	directory1 = opendir(songFolderPath);
	makeFolders(directory1, songFolderPath);

	char playlistsFolderPath[FULL_PATH_NAME_LEN];
	sprintf(playlistsFolderPath, "%s\\%s", fullUserPath, "Playlists");
	directory1 = opendir(playlistsFolderPath);
	makeFolders(directory1, playlistsFolderPath);

	if (destination.is_open()) {
		int passLen = password.size();
		destination.write((char*)&passLen, sizeof(int));
		destination.write((char*)&password, passLen);
		int pathLen = strlen(fullUserPath);
		destination.write((char*)&pathLen, sizeof(int));
		destination.write(fullUserPath, pathLen);
	}
	destination.close();
	closedir(directory);
	closedir(directory1);
}

void MusicalCollection::registration() {
	cout << "\t\tREGISTRATION" << endl;
	cout << "Enter your data:" << endl;

	cout << "Enter your user name: ";
	char sysName[MAX_NAMES_LEN];
	cin >> sysName;
	cout << "\n" << "Enter your first name: ";
	char userFirstName[MAX_NAMES_LEN];
	cin >> userFirstName;
	cout << "\n" << "Enter your last name: ";
	char userLastName[MAX_NAMES_LEN];
	cin >> userLastName;
	cout << "\n" << "Enter your birth date(to look like dd/mm/y, year - four digits): ";
	char userBirthDate[BIRTH_DATE_LEN];
	cin >> userBirthDate;

	User user(sysName, userFirstName, userLastName, userBirthDate);

	cout << "\n" << "Enter your favourite music genres: ";
	cout << "\n" << "If you want to stop entering genres just enter STOP." << endl;
	char genre[MAX_GENRE_NAME_LEN];
	cin >> genre;
	if (strcmp(genre, "STOP") != EQUAL_STRINGS) {
		do {
			user.addNewGenres(genre);
			cin >> genre;
		} while (strcmp(genre, "STOP") != EQUAL_STRINGS);
	}
	else {
		cout << "You didnt enter any genres in your profile." << endl;
	}

	string password;
	maskPassword(password);
	string encryptedPassword;
	encryptedPassword = encryptDecrypt(password);

	makePathsAndCopyData(encryptedPassword, user);
	existing();
}

void MusicalCollection::existing() {
	system("cls");
	cout << "Enter your user name: ";
	char userName[MAX_NAMES_LEN];
	cin >> userName;
	string password;
	maskPassword(password);

	char sysDataPath[] = "./SystemData";
	if (!(userReallyExisting(sysDataPath, userName))) {
		cout << "\nAccess aborted. Incorect user name." << endl;
		cout << "You will be returned to the start of the program." << endl;
		system("cls");
		return;
	}

	string encryptedPassword;
	encryptedPassword = encryptDecrypt(password);

	char fileNameExtantion[FILE_NAME_EXTAN_LEN];
	sprintf(fileNameExtantion, userName, ".data");
	char path[FULL_PATH_NAME_LEN];
	sprintf(path, "%s\\%s", sysDataPath, fileNameExtantion);
	ifstream userPassPath(path, ios::in | ios::binary);

	int pathLen;
	char pathUserFolder[FULL_PATH_NAME_LEN];

	if (userPassPath.is_open()) {
		int passLen;
		userPassPath.read((char*)&passLen, sizeof(int));
		string pass;
		userPassPath.read((char*)&pass, passLen);

		if (pass == encryptedPassword) {
			cout << "\nAccess granted.\n";
			userPassPath.read((char*)&pathLen, sizeof(int));
			userPassPath.read(pathUserFolder, pathLen);
		}
		else {
			cout << "\nAccess aborted. Incorect password\n";
			return;
		}
	}
	userPassPath.close();

	char userDataFile[FULL_PATH_NAME_LEN];
	sprintf(userDataFile, "%s\\%s", pathUserFolder, "userData.data");
	ifstream userData(userDataFile, ios::in | ios::binary);
	int userSize;
	User user;
	if (userData.is_open()) {
		userData.read((char*)&userSize, sizeof(int));
		userData.read((char*)&user, userSize);
	}
	userData.close();

	DoubleLinkedList<Song> userSongs;
	loadAllUserArchivedSongs(userSongs, pathUserFolder);

	Playlist userPlaylist;
	char playlistPath[FULL_PATH_NAME_LEN];
	sprintf(playlistPath, "%s\\%s", pathUserFolder, "Playlists");

	whatToDoWithThePL(userPlaylist, playlistPath, user, pathUserFolder); 

	musicalCollection(user, userSongs, userPlaylist, pathUserFolder, playlistPath);
}

void MusicalCollection::musicalCollection(User& user, DoubleLinkedList<Song>& userSongs, 
	Playlist& userPlaylist, char* pathUserFolder, char* playlistPath) {
	cout << "If you want to log out from the profile type: Log out." << endl;
	int command;
	
	do
	{
		cout << "Input what you want to do now:"
			<< "\t1.Change data - to change your profile data;\n"
			<< "\t2. Make playlist - to generate new playlist;\n"
			<< "\t3. Load playlist - to load new playlist from the ones in your profile;\n "
			<< "\t4. Add song - to add a song in your song archive;\n"
			<< "\t5. Give rating - to give raiting to the current song;\n"
			<< "\t6. Change song - to change the song;\n"
			<< "\t7. Show loaded songs;\n"
			<< "\t8. Log out - to log out of your profile."<< endl;
		cin >> command;

		if (command == FIRST_COMMAND) {
			changeUserData(user);
		}
		if (command == SECOND_COMMAND) {
			Playlist newPL;
			makeNewPlaylist(newPL, playlistPath, user, pathUserFolder);
			userPlaylist = newPL;
		}
		if (command == THIRD_COMMAND) {
			Playlist newPL;
			newPL.loadPlaylist(playlistPath);
			userPlaylist = newPL;
		}
		if (command == FOURTH_COMMAND) {
			Song song;
			cin >> song;
			addSongToArchive(song, pathUserFolder);
		}
		if (command == FIFTH_COMMAND) {
			int num;
			cout << "Input a number between 0 and 10 as rating for that song." << endl;
			cin >> num;
			userPlaylist.getCurr()->data.changeSongRatWhileWorking(num);
		}
		if (command == SIXTH_COMMAND) {
			char backOrForw[LEN_BACK_FORW];
			cout << "You want to go to the previous or next song? Type Back or Forward." << endl;
			cin >> backOrForw;
			userPlaylist.changeSong(backOrForw);
		}
		if (command == SEVENTH_COMMAND) {
			cout << "\tLoaded song are: " << endl;
			cout << userPlaylist;
		}

	} while (command != EIGHT_COMMAND);
}
