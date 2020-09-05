#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int const COMMENT_BUFF_LENGTH = 2;
int const BMPFILES_NAME_LENGTH = 256;
int const BFHHEADER_SIZE = 14;
int const DIBHEADER_SIZE = 40;
int const BMPIDENT_SIZE = 3;

bool isCommentLine(char* tdfFileName) {
	ifstream tdfFile(tdfFileName, ios::in);
	if (tdfFile.is_open()) {
		char commentBuff[COMMENT_BUFF_LENGTH];
		tdfFile >> commentBuff;
		char commentIdentifier[2] = ";";

		if (commentBuff[0] == commentIdentifier[0]) {
			tdfFile.close();
			return true;
		}
		else {
			tdfFile.close();
			return false;
		}
	}
	else {
		cout << "error: File cannot open.";
		return false;
	}
}

void getBMPFilesAndCoordinates(char* fileName, char* firstBuffer, char* secondBuffer,
	signed int* _startX, signed int* _startY, signed int* _lenByX, signed int* _lenByY) {
	ifstream tdfFile(fileName, ios::in);
	if (tdfFile.is_open()) {
		char comment = '\0';
		while (isCommentLine(fileName) && comment != '\n') {
			while (tdfFile.get(comment)) {
				if (comment == '\n') {
					break;
				}
			}
		}
		tdfFile >> firstBuffer;
		tdfFile.ignore(2);
		tdfFile >> *_startX;
		tdfFile.ignore();
		tdfFile >> *_startY;
		tdfFile.ignore();
		tdfFile >> *_lenByX;
		tdfFile.ignore();
		tdfFile >> *_lenByY;
		tdfFile.ignore(2);
		tdfFile >> secondBuffer;
	}
	tdfFile.close();
}

void getBFheaderComp(char* fileName, char* _bfhArr) {
	ifstream bmpBFH(fileName, ios::in | ios::binary);
	if (bmpBFH.is_open()) {
		bmpBFH.read(_bfhArr, 14);
	}
	bmpBFH.close();
}

void getDIBheaderComp(char* fileName, char* _dibArr) {
	ifstream bmpDIB(fileName, ios::in | ios::binary);
	if (bmpDIB.is_open()) {
		bmpDIB.read(_dibArr, 40);
	}
	bmpDIB.close();
}

void fixPadding(int padCheck, int* padding) {
	while ((padCheck + *padding) % 4 != 0) {
		padding++;
	}
}
void cropImage(char* srcBMP, char* destBMP, signed int _startByX, signed int _startByY, signed int _lenByX, signed int _lenByY, char* _bfHeader, char* _dibHeader) {
	ifstream source(srcBMP, ios::in | ios::binary);
	ofstream dest(destBMP, ios::out | ios::binary | ios::ate);
	if (source.is_open() && dest.is_open()) {
		dest.write(_bfHeader, sizeof(_bfHeader));
		dest.write(_dibHeader, sizeof(_dibHeader));

		int imageMaxWidth = 0;
		source.seekg(18, ios::beg);
		source.read((char*)&imageMaxWidth, sizeof(imageMaxWidth));
		int imageMaxHeight = 0;
		source.seekg(22, ios::beg);
		source.read((char*)&imageMaxHeight, sizeof(imageMaxHeight));
		short bytesPerPixel = 0;
		source.seekg(28, ios::beg);
		source.read((char*)&bytesPerPixel, sizeof(bytesPerPixel));
		bytesPerPixel /= 8;

		int row = imageMaxWidth * bytesPerPixel;
		int rowPadding = 0; 
		fixPadding(row, &rowPadding);
		int writeTimes = _lenByY - _startByY;
		int skipPixels = (imageMaxWidth - _lenByX + _startByX) * bytesPerPixel;

		char* buff;
		int buffLen = (_lenByX - _startByX)*bytesPerPixel;

		source.seekg(-(_lenByY*(row + rowPadding)) + _startByX*bytesPerPixel, ios::end);
		for (int i = 0; i < writeTimes; i++) {
			buff = new char[buffLen + 1];
			source.read(buff, buffLen);
			int padding = 0;
			fixPadding(buffLen, &padding);
			dest.write(buff, (buffLen + padding));
			source.seekg(skipPixels, ios::cur);
			delete buff;
			buff = nullptr;
		}
	}
	dest.close();
	source.close();
}
void rewritePartsOfBMP(char* fileName, signed int lenX, signed int lenY) {
	fstream destBMP(fileName, ios::out | ios::ate | ios::in | ios::binary); //so we can read and write generally for the pixelSize
	if (destBMP.is_open()) {
		short pixelSize = 0;
		destBMP.seekg(28, ios::beg);
		destBMP.read((char*)&pixelSize, sizeof(pixelSize));

		int bmpSize = sizeof(destBMP);
		int imageSize = lenX*lenY*pixelSize;
		int padding = 0;
		fixPadding(imageSize, &padding);
		imageSize += padding;
		destBMP.seekp(2, ios::beg);
		destBMP.write((char*)&bmpSize, sizeof(bmpSize));
		destBMP.seekp(18, ios::beg);
		destBMP.write((char*)&lenX, sizeof(lenX));
		destBMP.seekp(22, ios::beg);
		destBMP.write((char*)&lenY, sizeof(lenY));
		destBMP.seekp(34, ios::beg);
		destBMP.write((char*)&imageSize, sizeof(imageSize));
	}
	destBMP.close();
}

int main(int argc, char* argv[]) {
	argc = 2;
	argv[1] = "dogs.tdf";
	if (argc >= 2) {
		for (int i = 1; i < argc; i++)
		{
			ifstream myTDF(argv[i], ios::in);
			if (myTDF.is_open()) {
				char buff = '\0';
				while (myTDF>>buff) {
					char sourceBMPBuff[BMPFILES_NAME_LENGTH];
					char destBMPbuff[BMPFILES_NAME_LENGTH];
					signed int startX = 0, startY = 0, lenbyX = 0, lenbyY = 0;
					getBMPFilesAndCoordinates(argv[i], sourceBMPBuff, destBMPbuff, &startX, &startY, &lenbyX, &lenbyY);
					char bfhHeader[BFHHEADER_SIZE];
					getBFheaderComp(sourceBMPBuff, bfhHeader);
					char dibHeader[DIBHEADER_SIZE];
					getDIBheaderComp(sourceBMPBuff, dibHeader);
					ifstream srcFile(sourceBMPBuff, ios::in);
					char checkBMP[BMPIDENT_SIZE];
					if (srcFile.is_open()) {
						srcFile.read(checkBMP, 3);
					}
					srcFile.close();
					char bmp[3] = "BM";
					if (strcmp(checkBMP, bmp)) {
						cropImage(sourceBMPBuff, destBMPbuff, startX, startY, lenbyX, lenbyY, bfhHeader, dibHeader);
						rewritePartsOfBMP(destBMPbuff, lenbyX, lenbyY);
					}
				}
				myTDF.close();
			}
		}
	}
	else {
		cout << "error: Atleast one file must be used." << endl;
	}

	system("pause");
	return 0;
}