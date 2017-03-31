#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;


#include "../Ngrams/fileRead.cpp"
#include "../Ngrams/VectorHash.h"
#include "../Ngrams/utilsToStudents.h"

typedef string T;   // Currently tests string language model.

bool comp(pair<T, int> a, pair<T, int> b) {
    return a.second > b.second;
}

void p1(string fileName, int k) {

	int size = 0;
	unordered_map<T, int> wordCounts; 

	try {
		// First read all tokens from file into a vector 		
		vector<T> tokens;     // stores tokens read from file
		read_tokens(fileName, tokens, false); // reads tokens from file without EOS
		int size = tokens.size();

		if ( size < k )
			cout << "\nInput file is too small to create any nGrams of size " << k;
		else {
			for ( int i = 0; i < size; i++ ) {
				++wordCounts[tokens[i]];
			}

			vector<pair<T, int>> bestCounts(wordCounts.begin(), wordCounts.end());
			sort(bestCounts.begin(), bestCounts.end(), comp);

			bestCounts.erase(bestCounts.begin() + k, bestCounts.end());

			double numWords = 0;

			for (int i = 0; i < bestCounts.size(); i++) {
				cout << bestCounts[i].first << ", " << bestCounts[i].second << endl;
				numWords += bestCounts[i].second;
			}

			double percent = numWords/size;

			cout << percent << endl;
		}
		
			
	} 
	
	catch (FileReadException e) {
		e.Report();
	}
}

int main() {
	string fileName = "C:/Users/nnur3/Downloads/toStudents/toStudents/Texts/Novels/DostoevskyKaramazov.txt";
	p1(fileName, 49);
	cin.get();

	return 1;
}