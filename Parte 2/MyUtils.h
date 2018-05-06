#ifndef MYUTILS_H_
#define MYUTILS_H_

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

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

/* Removes any odd whitspaces or semicolon or newlines
 * From the beginning and end of a string
 */
 //Added new tests for the new file
void trimString(string &str);

/* Takes a string and makes its letters uppercase
 */
//New function, taken from userIn. Now its separate for other uses
void makeUpper(string &a);

string checkLine(string &line, multimap<string, string> &v);

/* Sorts vector
 */
void sortVector(vector<string> &v);

/* Checks if word is in v
 * v vector where the word is being searched
 * word string to be searched in v
 */
const bool searchVector(const vector<string> &v, const string word);

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

#endif
