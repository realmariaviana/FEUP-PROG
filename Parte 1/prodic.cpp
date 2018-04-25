#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "MyUtils.h"

using namespace std;

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"			//Used when checking if line is a header (if its all in caps)
#define WHITESPACE " "														//Used when checking if line is a header (if it contains whitespaces)

vector<string> readDictionary(ifstream &dictionary);
void checkLine(string &line,vector<string> &v);
void trimString(string &str);
bool isHeader(string line);
void writeToVector(string line, vector<string> &v);
void writeToFile(const vector<string> &v, ofstream &words);

int main() {
	printInit();

	string dictionaryFile, wordsFile;
	ifstream dictionary;
	ofstream words;
	vector<string> wordList;

	cout << "Dictionary file ? ";
	cin >> dictionaryFile;
	cout << endl;
	openFile(dictionaryFile, dictionary);

	cout << "Word list file ? ";
	cin >> wordsFile;
	cout << endl;
	openFile(wordsFile, words);

	cout << "Extracting simple words from file " << dictionaryFile << endl;
	cout << "Beginning with letter ..." << endl << endl;

	wordList = readDictionary(dictionary);

	dictionary.close();

	cout << endl << "Number of simple words = " << wordList.size() << endl;

	cout << "Sorting words ..." << endl;
	sortVector(wordList, 0, wordList.size()-1);

	cout << "Removing duplicate words ..." << endl;
	removeDuplicates(wordList);

	cout << "Number of non-duplicate simple words = " << wordList.size() << endl;

	cout << "Saving words into file " << wordsFile << " ..." << endl;
	writeToFile(wordList, words);

	cout << "End of processing." << endl;

	words.close();

	return 0;
}

/* Write words after processing to file
 * v vector of words
 * words file
 */
void writeToFile(const vector<string> &v, ofstream &words){
	for(size_t i = 0; i < v.size(); i++){
		string aux = v.at(i);
		words << aux << endl;																			//Writes a word per line
	}
}

/*	Adds word to vector and takes care of printing the letter being processed and the dot
 * 	word string to be added to vector
 * 	v vector storing word
 */
void writeToVector(string word, vector<string> &v){
	static char letter = 'A';																					//Static to keep track of word being processed
	static int numLetter = 0;																					//Static to keep track of the number of words written

	if(letter == 'A' && numLetter == 0) cout << letter << endl;				//Needed to print A

	//Check if the word to be added starts with another letter also checks if that letter is the one
	//Following the one that was being processed
	//Takes care of the RACE that is left in a new line, in the middle of the C section
	if(letter != word.at(0) && letter +1 == word.at(0)){
		letter = word.at(0);
		cout << endl << letter << endl;
		numLetter = 0;
	}

	if(numLetter % 100 == 0) cout << ".";															//Every 100 words it prints out a .
	numLetter ++;

	v.push_back(word);
}

/*	Checks if line read from dictionary is header
 * 	All uppercase and simple words
 * 	line to be check if is header
 * 	return: true if is header false otherwise
 */
bool isHeader(string line){
	if(line.empty()) return false;															//If line is empty it cant be a headline

	bool flag_alphabet = false;
	if(line.find_first_not_of(ALPHABET) == string::npos){				//Check if line is in all caps
		flag_alphabet = true;
	}else{
		flag_alphabet = false;
	}

	bool flag_whitespaces = true;
	if(line.find_first_not_of(WHITESPACE) == string::npos){			//Checks if the line contains any whitespaces
		flag_whitespaces = false;
	}else{
		flag_whitespaces = true;
	}

	return flag_alphabet && flag_whitespaces;										//Logic AND of the flags
}

/* Removes any odd whitspaces or semicolon or newlines
 * From the beginning and end of a string
 */
void trimString(string &str){
	if(str.front() == ' ' || str.front() == ';'){
		str.erase(0, 1);
	}

	if(str.back() == ' ' || str.back() == '\n'){
		str = str.substr(0, str.size() -1);
	}
}

/*	Checks if anything in the line read from the dictionary file can be used
 *	This means checking for the various words when separeted by ' ; '
 */
void checkLine(string &line, vector<string> &v){
	string aux;

	if(line.find(';') == string::npos){													//If theres no ' ; ' in the line take care of it as is
		trimString(line);
		if(isHeader(line)) writeToVector(line, v);
	}else{
		while(!line.empty()){																			//If there is a semicolon on the line it must be divided
			size_t pos = line.find(';');
			if(pos == string::npos) break;

			aux = line.substr(0, pos);															//Divides the whole line until a semicolon
			trimString(aux);																				//Trims String in case of having a misplaced space
			if(isHeader(aux)) writeToVector(aux, v);								//Test said division
			line.erase(0, pos +1);																	//Deletes the word from the line so the next one can be
			trimString(line);
		}
		trimString(line);																					//Because a line can have only one semicolon, but both words
		if(isHeader(line)) writeToVector(line, v);								//Be valid I trim the string and check if the remaining word
																															//Is a header

	}
}

/*	Reads whole lines from dictionary file and writes them to vector
 * 	dictionary file from where line are read
 * 	return: vector of strings storing words read
 */
vector<string> readDictionary(ifstream &dictionary){
	string line;
	vector<string> headlines;

	getline(dictionary, line);														//Reads the whole line, including whitespaces, til \n
	line = line.substr(0, line.size()-1);
	checkLine(line, headlines);

	while(!dictionary.eof()){
		getline(dictionary, line);
		line = line.substr(0, line.size()-1);
		checkLine(line, headlines);
	}

	return headlines;
}
