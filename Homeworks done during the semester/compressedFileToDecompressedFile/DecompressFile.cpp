#include "DecompressFile.h"

DecompressFile::DecompressFile()
	:symbol('\0'), bracketCounter(DEFAULT_BRACKETCOUNT), errorTracker(false)
{}

void DecompressFile::decompressFile(char * compressedFile, char * decompressedFile) {

	ifstream compressedTXT(compressedFile, ios::in);
	if (compressedTXT.is_open()) {
		while (!compressedTXT.eof() && compressedTXT.good()) {
			compressedTXT >> symbol;
			
			if (isSpecialSymbol(symbol)) {
				compressedTXT >> symbol;
				
				if (compressedTXT.eof()) {
					errorTracker = true;
					break;
				}
				stackSymbols.push(symbol);
			}
			else if (symbolIsNumber(symbol)) {
				unsigned numberBeforeBrackets = DEFAULT_DUPLICNUM;
				numberBeforeBrackets = getFullNumberFromFile(compressedTXT, symbol);

				if (isSpecialSymbol(symbol)) {
					errorTracker = true;
					break;
				}
				else if (symbol != '(') {
					errorTracker = true;
					break;
				}
				stackNumbers.push(numberBeforeBrackets);
				stackSymbols.push(symbol); // the function getFullNumberFromFile will move to symbol '(' 
				bracketCounter++;
			}
			else if (symbol == ')') {
				bracketCounter--;
				duplicateSymbolArray(stackSymbols, stackNumbers);
			}
			else {
				stackSymbols.push(symbol);
			}
			symbol = '\0';
		}
		compressedTXT.close();

		if (!errorTracker && correctlyWrittenBrackets(bracketCounter)) {
			ofstream decompressedTXT(decompressedFile, ios::out);
			if (decompressedTXT.is_open()) {
				decompressedTXT << stackSymbols;
			}
			decompressedTXT.close();
		}
		else {
			cerr << "Error: Not correctly written file!" << endl;
		}
	}
}
