#pragma once
#include <iostream>
#include <fstream>
#include "DynamicArray.h"
#include "DynamicStack.h"

using namespace std;

int const DEFAULT_BRACKETCOUNT = 0;
int const DEFAULT_DUPLICNUM = 0;
int const MULTIPLIER = 10;
int const DUPLICATION_STOPPER = 0;
int const ARRAY_STOPPER = 0;

class DecompressFile {
	char symbol;
	DynamicStack<char> stackSymbols;
	DynamicStack<int> stackNumbers;
	int bracketCounter; //if it stays 0, the file is correctly written
	bool errorTracker; //tracks if the file is written correctly

	int convertSymbolToNum(char symbol) {
		/* switch (symbol)
		{
			case '1': return 1; 
				break;
			case '2': return 2; 
				break;
			case '3': return 3; 
				break;
			case '4': return 4; 
				break;
			case '5': return 5; 
				break;
			case '6': return 6; 
				break;
			case '7': return 7; 
				break;
			case '8': return 8; 
				break;
			case '9': return 9; 
				break;
			default: return 0; 
				break;
		} */
		
		return symbol - '0';
	}
	bool symbolIsNumber(char symbol) {
		if(symbol >= '0' && symbol <= '9') {
			return true;
		}
		
		return false;
	}
	int getFullNumberFromFile(ifstream& file, char& symbolDigit) {
		unsigned duplicationNumber = DEFAULT_DUPLICNUM;
		if (file.is_open()) {
			duplicationNumber = convertSymbolToNum(symbolDigit);
			file >> symbolDigit;

			while (symbolIsNumber(symbolDigit)) {
				duplicationNumber *= MULTIPLIER;
				duplicationNumber += convertSymbolToNum(symbolDigit);
				file >> symbolDigit;
			}
		}
		return duplicationNumber;
	}
	bool correctlyWrittenBrackets(int counter) {
		return counter == DEFAULT_BRACKETCOUNT;
	}
	bool isSpecialSymbol(char symbol) {
		return symbol == '\\';
	}
	void duplicateSymbolArray(DynamicStack<char>& stackOfSym, DynamicStack<int>& stackOfNums) {
		DynamicArray<char> strForDuplication;
		char moveSymbols = '0';
		while (stackOfSym.peek() != '(' && !stackOfSym.empty()) {
			moveSymbols = stackOfSym.pop();
			strForDuplication.addNewElement(moveSymbols);
		}
		stackOfSym.pop(); //removes the symbol '(' from the stack

		unsigned iterator = stackOfNums.pop();
		while (iterator != DUPLICATION_STOPPER) {
			for (int i = strForDuplication.getSize(); i >= ARRAY_STOPPER; i--) {
				stackOfSym.push(strForDuplication.getAt(i));
			}
			iterator--;
		}
	}
public:
	DecompressFile();
	void decompressFile(char*, char*);
};