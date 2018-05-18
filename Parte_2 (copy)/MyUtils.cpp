#include "MyUtils.h"

using namespace std;

void openFile(string filename, ifstream &input){
	input.open(filename);
	if(input.fail()){
		cerr << "Error opening file: " << filename << endl;
		exit(1);
	}
}

void openFile(string filename, ofstream &output){
	output.open(filename);
	if(output.fail()){
		cerr << "Error opening file: " << filename << endl;
		exit(1);
	}
}

void trimString(string &str){
	if(str.front() == ' ' || str.front() == ';' || str.front() == ',' || str.back() == ':'){
		str.erase(0, 1);
	}

	if(str.back() == ' ' || str.back() == '\n' || str.back() == ','){
		str = str.substr(0, str.size() -1);
	}
}

void makeUpper(string &a){
	for(size_t i = 0; i < a.length(); i++){
		a.at(i) = toupper(a.at(i));
	}
}

string checkLine(string &line, multimap<string, string> &v){
	string aux, key;

	size_t pos = line.find_first_of(':');

	key = line.substr(0, pos);
	trimString(key);
	makeUpper(key);
	line.erase(0, pos+1);

	while(!line.empty()){
		pos = line.find(',');
		if(pos == string::npos) break;

		aux = line.substr(0, pos);
		trimString(aux);
		makeUpper(aux);
		v.insert(pair<string, string>(key, aux));
		line.erase(0, pos+1);
	}
	line=line.substr(0, pos);
	trimString(line);
	makeUpper(line);
	v.insert(pair<string, string>(key, line));

	return key;
}

void sortVector(vector<string> &v){
	sort(v.begin(), v.end());
}

const bool searchVector(const vector<string> &v, const string word){
	return binary_search(v.begin(), v.end(), word);
}

bool wildcardMatch(const char*str, const char*strWild){
	/* We have a special case where string is empty ("") and the mask is "*".
	 * We need to handle this too. So we can't test on !*str here.
	 * The loop breaks when the match string is exhausted. */
	while(*strWild){
		// Single wildcard character
		if(*strWild== '?')
		{
			// Matches any character except empty string
			if(!*str)return false;
			// OK next
			++str;
			++strWild;
		}else if(*strWild== '*'){
			/* Need to do some tricks.
			 * 1. The wildcard * is ignored.
			 *    So just an empty string matches. This is done by recursion.
			 *    Because we eat one character from the match string,
			 *    the recursion will stop. */
			if(wildcardMatch(str,strWild+1))
				// we have a match and the * replaces no other character
				return true;
			/* 2. Chance we eat the next character and try it again,
			 *    with a wildcard * match. This isdone by recursion.
			 *    Because we eat one character from the string,
			 *    the recursion will stop. */
			if(*str && wildcardMatch(str+1,strWild))return true;
			// Nothing worked with this wildcard.
			return false;
		}else{
			/* Standard compare of 2 chars. Note that *str might be here,
			 * but then we never get a match on *strWild
			 * that has always a value while inside this loop.*/
			if(toupper(*str++)!=toupper(*strWild++))
				return false;
		}
	}
	// Have a match? Only if both are at the end...
	return !*str && !*strWild;
}
