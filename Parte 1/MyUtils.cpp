#include "MyUtils.h"

using namespace std;

void printInit(){
	cout << "EXTRACTION OF WORD LIST FROM DICTIONARY" << endl;
	cout << "=======================================" << endl;
}

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

/*	Swaps the values of position a and b
 * 	a becomes b, b becomes a
 * 	v vector to swap values
 * 	a, b positions
 */
void swapVector(vector<string> &v, int a, int b){
	string aux = v.at(a);
	v.at(a) = v.at(b);
	v.at(b) = aux;
}

void sortVector(vector<string> &v, int L, int R){
	//QuickSort implementation
	int i = L, j = R, mid;
	string piv;

	mid = L + (R-L)/2;
	piv = v.at(mid);

	while(i < R || j > L){
		while(v.at(i) < piv) i++;
		while(v.at(j) > piv) j--;

		if(i <= j){
			swapVector(v, i, j);
			i++;
			j--;
		}else{
			if(i < R) sortVector(v, i, R);
			if(j > L) sortVector(v, L, j);

			return;
		}
	}
}

void removeDuplicates(vector<string> &v){
	for(size_t i = 0; i < v.size()-1; i++){
		while(v.at(i) == v.at(i+1)) v.erase(v.begin() +i +1);			//While the next word is equal to the one before erase it
	}
}

bool searchVector(const vector<string> &v, const string word){
	//Binary search the vector since it is sorted
	int L = 0, R = v.size(), M;

	while(L < R){
		M = L + (R - L) / 2;
		if(word > v.at(M)){
			L = M + 1;
		}else if(word < v.at(M)){
			R = M;
		}else{
			return true;
		}
	}

	return false;
}

/* Swaps the value of position a and b
 * a becomes b, b becomes a
 * str string where values are swapped
 * a, b positions
 */
void swap(string &str, int a, int b){
	char temp = str.at(a);
	str.at(a) = str.at(b);
	str.at(b) = temp;
}

void scrambleString(string &word){
	for(unsigned int i = 0; i < word.length(); i++){
		int pos = rand() % word.length();
		swap(word, i, pos);
	}
}

bool checkIfValid(string a, string b){
	if(a.size() != b.size()) return false;

	int Arr[26] = {};

	for(size_t i = 0; i < a.size(); i++){
		int pos = POS_LETTER((int)a.at(i));
		Arr[pos]++;
		pos = POS_LETTER((int)b.at(i));
		Arr[pos]--;
	}

	for(int i = 0; i < 26; i++) if(Arr[i] != 0) return false;

	return true;
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
