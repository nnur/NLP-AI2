#include <string>
#include <unordered_map>
#include <algorithm>
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

		if ( database.count(nGram) == 0 )
			database[nGram] = 1;
		else
			database[nGram] = database[nGram] + 1;	
	} 

	return database;

}

T p3(string fileName, int Nsize) {
	try {
		vector<T> tokens;
		unordered_map<vector<T>, int> set;
		unordered_map<vector<T>, int> setSm;

		read_tokens(fileName, tokens, true);

		set = getNgrams(tokens, Nsize);
		if (Nsize > 1) {
			setSm = getNgrams(tokens, Nsize-1);
		}
		

		int m = set.size();
		int totalWords = tokens.size();
	
		vector<double> probs;
		vector<vector<T>> ngrams;

		for (auto i = set.begin(); i != set.end(); ++i) 
		{
			int numCount = i-> second;
			double prob = numCount/double(totalWords);
			probs.push_back(prob);
			ngrams.push_back(i->first);

		}	

		cout << probs.size()<< endl << endl;

		
		T sentence;
		bool isEnd = false;

		while (isEnd) {
			int i = drawIndex(probs);
			vector<T> nGram = ngrams[i];
			for ( unsigned int j = 0; j < nGram.size(); j++ ) {
				T value = nGram[j];
				cout << nGram[j] << " ";  
				
				if (value == EOS) {
					isEnd = true;
				}
							
			}
		}


		return sentence;
	}
	catch (FileReadException e) {
		e.Report();
	}
}

int main(int argc, char* argv[]) {
	string file1 = string(argv[1]);
	int size = atoi(argv[2]);
	
	p3(file1, size);

	return 1;
}
