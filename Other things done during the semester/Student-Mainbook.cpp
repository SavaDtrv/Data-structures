#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
const int MAX_NAME_SIZE = 100;


class Student {
	char name[MAX_NAME_SIZE];
	double grade;
	int fn;

public:
	Student(char const* _name = "<anon>", double _grade = 2.0, int _fn = 00000) :grade(_grade), fn(_fn) {
		strncpy(name, _name, MAX_NAME_SIZE);
		name[MAX_NAME_SIZE] = '\0';
	}

	const char* getName() const { return name; }
	double getGrade() const { return grade; }
	int getFN() const { return fn; }

	void setGrade(double newGrade) {
		grade = newGrade;
	}

	friend istream& operator>>(istream&, Student&);

	friend ostream& operator<<(ostream os, const Student& myStudent);
};

istream& operator>>(istream& is, Student& myStudent) {
	cout << "FN: ";
	is >> myStudent.fn;
	cout << endl;
	cout << "Grade: ";
	is >> myStudent.grade;
	cout << endl;
	cout << "Name: ";
	is.ignore();
	is.getline(myStudent.name, MAX_NAME_SIZE);
	//cout << "!" << myStudent.name << "!";
	cout << endl;

	return is;
}
ostream& operator<<(ostream& os, Student& myStudent) {
	os << myStudent.getName();
	os << myStudent.getGrade();
	os << myStudent.getFN();

	return os;
}

Student* readStudents(int& n) {
	cout << "Enter the number of the students you want to add in the file: ";
	cin >> n;
	Student* students = new Student[n];
	for (int i = 0; i < n; i++) {
		cin >> students[i];
	}

	return students;
}

void writeStudents(Student* students, int n) {
	ofstream myFile("students.txt", ios::out | ios::trunc);
	myFile << n << endl;

	for (int i = 0; i < n; i++) {
		myFile << students[i].getFN() << " ";
		myFile << students[i].getName() << " ";
		myFile << students[i].getGrade();
		myFile << endl;
	}
}

void toMainBook() {
	ifstream ifs("students.txt");
	ofstream ofs("main.bk", ios::out | ios::binary);
	int n;
	ifs >> n;
	Student s;
	while (ifs >> s) {
		if (s.getGrade() >= 3) {
			ofs.write((char const*)&s, sizeof(Student));
		}
	}
}
void readMainBook() {
	ifstream ifs("main.bk", ios::in | ios::binary);
	Student s;
	while (ifs.read((char*)&s, sizeof(Student))) {
		cout << s;
		}
	ifs.close();
}

void raiseGrade(int fn) {
	fstream fo("main.bk", ios::in | ios::out | ios::binary);
	Student s;
	while (fo.read((char*)&s, sizeof(Student))) {
		if (s.getFN() == fn) {
			s.setGrade(s.getGrade() + 1);
			fo.seekp(-(int)(sizeof(Student)), ios::cur); //current, beg - begining, end - end
			fo.write((const char*)&s, sizeof(Student));
		}
	}

	fo.close();
}

int main() {	
	//int numOfStudents;
	///*cout << "Enter the number of the students you want to add in the file: ";
	//cin >> numOfStudents;*/
	//Student* students = readStudents(numOfStudents);
	//writeStudents(students, numOfStudents);

	toMainBook();
	raiseGrade(1004);

	system("pause");
	return 0;
}