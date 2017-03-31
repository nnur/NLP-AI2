#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;


#include "../Ngrams/fileRead.cpp"
#include "../Ngrams/VectorHash.h"
#include "../Ngrams/utilsToStudents.h"

typedef string T;

unordered_map<vector<T>, int> getNgrams(vector<T>tokens, int n) {
		
	unordered_map<vector<T>, int> database;  

	for ( int i = 0; i <=  tokens.size() - n; i++ )
	{
		vector<T> nGram(n);
			 
		for ( unsigned int j = 0; j < n; j++ ) {
			nGram[j] = tokens[i+j];
		}

		database[nGram] = i;		
	} 

	return database;

}

void p2(string file1, string file2, int n, int toPrint ) {

	try {
		
		vector<T> tokens1;
		vector<T> tokens2;

		read_tokens(file1, tokens1, false);
		read_tokens(file2, tokens2, false);

		int numUnique = 0;

		unordered_map<vector<T>, int> ngrams1 = getNgrams(tokens1, n);
		unordered_map<vector<T>, int> ngrams2 = getNgrams(tokens2, n);

		for (auto i = ngrams2.begin(); i != ngrams2.end(); ++i) {
			vector<T> nGram = i->first;

			if (ngrams1.count(nGram) == 0 ) {
				numUnique += 1;
			} else if (toPrint == 1) {
				for ( unsigned int j = 0; j < nGram.size(); j++ ) {
					cout << nGram[j] << " "; 
				}
				cout << endl;
			}
		}

		float percentageUnique = 100.0* numUnique/float(ngrams2.size());
		cout << "------------ printing the percentage -------------____------- " << endl;

		cout << numUnique << endl << ngrams2.size() << endl<< percentageUnique << endl;
		
	}

	catch (FileReadException e) {
		e.Report();
	}
}

int main(int argc, char* argv[]) {
	string file1 = string(argv[1]);
	string file2 = string(argv[2]);
	int size = atoi(argv[3]);
	int toPrint = atoi(argv[4]);

	//cout << file1 << endl << file2 << endl << size << endl << toPrint << endl;

	//p2("..\\..\\Texts\\Novels\\DostoevskyPart1.txt","..\\..\\Texts\\Novels\\DostoevskyPart1.txt", 1, 1);
	p2(file1, file2, size, toPrint);

	return 1;
}
