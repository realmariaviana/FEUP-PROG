#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cctype>

#include "MyUtils.h"

using namespace std;

vector<string> readFile(ifstream &input, vector<int> &freq, vector<int> &num);
vector<char> generatePool(const vector<int> &freq);
void printMenu(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool);
void invalidMenuOption(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool);
void checkWord(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool);
string userIn();
void guessRndWord(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool);
void existWord(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool);
void calcInt(int &init, int &end, char ltr, const vector<int> &numWords);
void buildWord(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool);
void wildcardGame(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool);

int main(){
	string name_f;
	ifstream words;

	vector<string> WordsList;
	vector<int> NumWords(26, 0);
	vector<int> Freq(26, 0);
	vector<char> Pool;

	srand(time(NULL));

	cout << "Words file ? " << endl;
	cin >> name_f;

	openFile(name_f, words);

	WordsList = readFile(words, Freq, NumWords);

	Pool = generatePool(Freq);

	Freq.clear();
	words.close();

	printMenu(WordsList, NumWords, Pool);

	return 0;
}

/* Wildcard Game
 * It is required that the first letter is given....
 * Then it checks the second letter to cut down the size of the
 * Interval where that word can be
 * arguments needed to give the user the option to choose another game and not have to restart
 */
void wildcardGame(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool){
	string in;

	cout << "Wildcard word ?" <<endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, in);

	if(in.at(0) != '*' && in.at(0) != '?'){
		int init = 0, end = 0;
		calcInt(init, end, in.at(0), numWords);
		for(int i = init; i <= end; i++){
			string aux = wordsList.at(i);
			if(wildcardMatch(aux.c_str(), in.c_str())){
				cout << aux << endl;
			}
		}
	}else{
		for(size_t i = 0; i < wordsList.size(); i++){
			string aux = wordsList.at(i);
			if(wildcardMatch(aux.c_str(), in.c_str())){
				cout << aux << endl;
			}
		}
	}

	cout << "Want to play again ? [Y/N]" << endl;
	in = userIn();

	if(in == "Y"){
		wildcardGame(wordsList, numWords, pool);
	}else{
		printMenu(wordsList, numWords, pool);
	}

	return;
}

/* Asks the user to create a word from the given random letters
 * Checks if word exist in dictionary
 * arguments needed to give the user the option to choose another game and not have to restart
 */
void buildWord(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool){
	int len = rand()%5 +5;						//The length of the word is >= 5 since the average length of words in english is
	//Around 5ish
	int pos = 0;
	string rndLetters, in;

	for(int i = 0; i < len; i++){
		pos = rand()%pool.size();
		rndLetters.push_back(pool.at(pos));
	}

	cout << "With this letters generate a word: " << rndLetters << endl;
	in = userIn();


	if(searchVector(wordsList, in)){
		cout << "The word exists" << endl;
	}else{
		cout << "The word does not exist" << endl;
	}

	cout << "Want to play again ? [Y/N]" << endl;
	in = userIn();

	if(in == "Y"){
		buildWord(wordsList, numWords, pool);
	}else{
		printMenu(wordsList, numWords, pool);
	}
}

/* Calculates the interval where a letter is located in the vector WordsList
 * init initial position of the letter
 * end last position where a word begins with the letter ltr
 * ltr the letter we want in the first position
 */
void calcInt(int &init, int &end, char ltr, const vector<int> &numWords){
	init = end = 0;

	int pos = POS_LETTER((int)ltr);

	if(pos == 0){
		init = 0;
		end = numWords.at(pos);
		return;
	}

	for(int i = 0; i < pos; i++) init += numWords.at(i);
	++init;
	end = init + numWords.at(pos) -1;
	if(pos == 25) --end;
}

/* Given a set of random letters it checks what words they can be made into
 * It does this not by searching everyword but by searching for each initial letter
 * numWords vector contain the number of words starting with each letter
 */
void existWord(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool){
	string in;
	vector<string> res;

	cout << "Insert letters: " << endl;
	in = userIn();

	for(size_t i = 0; i < in.length(); i++){
		int init = 0, end = 0;
		calcInt(init, end, in.at(i), numWords);
		for(int i = init; i <= end; i++){
			if(checkIfValid(in, wordsList.at(i))){
				res.push_back(wordsList.at(i));
			}
		}
	}

	if(res.empty()){
		cout << "No words were found" << endl;
	}else{
		sortVector(res, 0, res.size()-1);
		for(size_t i = 0; i < res.size(); i++) cout << res.at(i) << endl;
	}

	cout << "Want to play again ? [Y/N]" << endl;
	in = userIn();

	if(in == "Y"){
		existWord(wordsList, numWords, pool);
	}else{
		printMenu(wordsList, numWords, pool);
	}

	return;
}

/* Given a scrambled word the user has to guess it
 * arguments needed to give the user the option to choose another game and not have to restart
 */
void guessRndWord(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool){
	int pos = rand() % wordsList.size();
	string wrd = wordsList.at(pos), guess, wrdOri;
	wrdOri = wrd;

	scrambleString(wrd);

	cout << "Word scrambled: " << wrd << endl << endl;
	cout << "You have 3 turns" << endl;

	for(int i = 1; i < 4; i++){
		if(i != 3){
			cout << "\nTry number " << i << endl;
		}else{
			cout << "\nLast try" << endl;
		}

		guess = userIn();

		if(guess == wordsList.at(pos)){
			cout << "Correct" << endl;
			break;
		}else{
			if(i != 3){
				cout << "Incorrect, try again" << endl;
			}else{
				cout << "Incorrect" << endl;
				cout << "\nCorrect word: " << wrdOri << endl;
			}
		}
	}

	cout << "Want to play again ? [Y/N]" << endl;
	guess = userIn();

	if(guess == "Y"){
		guessRndWord(wordsList, numWords, pool);
	}else{
		printMenu(wordsList, numWords, pool);
	}

	return;
}

/* Checks user input and makes sure it is all in uppercase
 * If it isn't it transforms it
 * return string read
 */
string userIn(){
	string in;
	bool flag = true;

	while(flag){
		cin >> in;

		for(size_t i = 0; i < in.length(); i++){
			if(in.at(i) < 'A' && in.at(i) > 'Z' && in.at(i) < 'a' && in.at(i) > 'z'){
				cout << "Weird symbol detected!" << endl;
				break;
			}else{
				flag = false;
			}
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	for(size_t i = 0; i < in.length(); i++){
		in.at(i) = toupper(in.at(i));
	}

	return in;
}

/* Checks if the word read from the keyboard is present on the dictionary
 * arguments needed to give the user the option to choose another game and not have to restart
 */
void checkWord(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool){
	string in;

	cout << "Insert word: " << endl;
	in = userIn();

	if(searchVector(wordsList, in)){
		cout << "Word found" << endl;
	}else{
		cout << "Word not found" << endl;
	}

	cout << "Want to play again ? [Y/N]" << endl;
	in = userIn();

	if(in == "Y"){
		checkWord(wordsList, numWords, pool);
	}else{
		printMenu(wordsList, numWords, pool);
	}

	return;
}

/* If the input from the user was an invalid option in the menu
 * Lets the user have another try at choosing the game
 * arguments needed to give the user the option to choose another game and not have to restart
 */
void invalidMenuOption(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool){
	if(cin.fail()){
		cout << endl << "Invalid option detected. Try again" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		printMenu(wordsList, numWords, pool);
	}else{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		printMenu(wordsList, numWords, pool);
	}
}

/* Prints the menu giving the user options of the games
 * Makes the calls to the functions of the various games
 * arguments needed to give the user the option to choose another game and not have to restart
 */
void printMenu(const vector<string> &wordsList, const vector<int> &numWords, const vector<char> &pool){
	cout << "======================================" << endl;
	cout << "Welcome to Play with Words" << endl;
	cout << "Use the number to choose an option" << endl;
	cout << "1) Check if word exists" << endl;
	cout << "2) Guess word from letters" << endl;
	cout << "3) Generates words from letters" << endl;
	cout << "4) Build a word from the letters" << endl;
	cout << "5) Wildcard game" << endl;
	cout << "0) End program" << endl;
	cout << "======================================" << endl;

	int options = -1;

	while(!cin.fail()){
		cin >> options;

		switch (options) {
		case 0:
			cout << "Closing the program..." << endl;
			exit(0);
		case 1:
			checkWord(wordsList, numWords, pool);
			break;
		case 2:
			guessRndWord(wordsList, numWords, pool);
			break;
		case 3:
			existWord(wordsList, numWords, pool);
			break;
		case 4:
			buildWord(wordsList, numWords, pool);
			break;
		case 5:
			wildcardGame(wordsList, numWords, pool);
			break;
		default:
			invalidMenuOption(wordsList, numWords, pool);
			break;
		}
	}
}

/* Generates pool of letters from their frequency
 * Populates Pool vector
 * For every 100 of said letter it adds it to the pool
 * freq vector with the frequency of each word
 * returns the pool vector
 */
vector<char> generatePool(const vector<int> &freq){
	vector<char> ret;
	int val = 0;
	char letter = 'A';

	for(size_t i = 0; i < freq.size(); i++){
		val = ceil(freq.at(i) / 100);
		for(int j = 0; j < val; j++) ret.push_back(letter);
		letter++;
	}

	return ret;
}

/*	Reads words from file and populates freq and num vectors
 * 	input ifstream of file
 * 	freq vector with frequency of each letter
 * 	num vector with the number of words starting with each letter
 * 	returns wordlist vector containg every word read from the file
 */
vector<string> readFile(ifstream &input, vector<int> &freq, vector<int> &num){
	vector<string> ret;
	string word;
	int pos = 0;

	input >> word;
	ret.push_back(word);
	pos = POS_LETTER(word.at(0));
	freq.at(pos)++;
	num.at(pos)++;

	while(!input.eof()){
		input >> word;
		ret.push_back(word);

		pos = POS_LETTER(word.at(0));
		num.at(pos)++;

		for(size_t i = 0; i < word.length(); i++){
			int pos = POS_LETTER(word.at(i));
			freq.at(pos)++;
		}
	}

	return ret;
}
