#ifndef MYUTILS_H_
#define MYUTILS_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define POS_LETTER(n) n-65

using namespace std;

/*	Prints header of program
 */
void printInit();

/*	Opens file
 * 	filename name of file to be open
 * 	input ifstream passed by reference
 */
void openFile(string filename, ifstream &input);

/*	Opens file
 * 	filename name of file to be open
 * 	output ofstream passed by reference
 */
void openFile(string filename, ofstream &output);

/* Sorts vector recursively
 * v vector to be sorted
 * L leftmost position
 * R rightmost position
 */
void sortVector(vector<string> &v, int L, int R);

/*	Removes duplicate words from vector
 * 	v vector to remove duplicates from
 */
void removeDuplicates(vector<string> &v);

/* Checks if word is in v
 * v vector where the word is being searched
 * word string to be searched in v
 */
bool searchVector(const vector<string> &v, const string word);

/* Scrambles word by changing its letters position
 * word string to be scrambled
 */
void scrambleString(string &word);

/* Checks if the 2 strings made of the same letters
 * a, b string to be tested
 * returns true if they are made of the same letters, false otherwise
 */
bool checkIfValid(string a, string b);

/*
 * WildcardMatch
 *   str    - Input string to match
 *   strWild - Match mask that may contain wildcards like ? and*
 *
 *   A ? sign matches any character, except an empty string.
 *   A * sign matches any string inclusive an empty string.
 *   Characters are compared caseless.
 *
 * ADAPTED FROM:
 * https://www.codeproject.com/Articles/188256/A-Simple-Wildcard-Matching-Function */
bool wildcardMatch(const char *str, const char *strWild);

#endif /* MYUTILS_H_ */
