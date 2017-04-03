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

	for (int i = 0; i <= tokens.size() - n; i++)
	{
		vector<T> nGram(n);

		for (unsigned int j = 0; j < n; j++) {
			nGram[j] = tokens[i + j];
		}

		if (database.count(nGram) == 0) {
			database[nGram] = 1;
		}
		else {
			database[nGram] = database[nGram] + 1;
		}
	}

	return database;

}

void getProbs(unordered_map<vector<T>, int> sentenceNgrams, unordered_map<vector<T>, int> nGrams, double bottom, double delta) {
	unordered_map<vector<T>, double> probs;
	double prob;
	double sum = 0;
	for (auto i = sentenceNgrams.begin(); i !=  sentenceNgrams.end(); ++i) {
		vector<T> nGram = i->first;
		int count = nGrams[nGram];
		prob = (count + delta) / bottom;
		probs[nGram] = prob;

		sum += log(prob);

		cout << nGram[0] << " " << nGram[1] << " : " << prob << endl;
	}

	cout << sum << endl;

	//return probs;
}

void p4(string fileName, string fileName2, int nSize, double delta) {
	vector<T> tokens;
	vector<T> sentenceTokens;
	read_tokens(fileName, tokens, false);
	read_tokens(fileName2, sentenceTokens, false);

	double N = tokens.size();
	
	unordered_map<vector<T>, int> oneGrams = getNgrams(tokens, 1);
	unordered_map<vector<T>, int> nGrams = getNgrams(tokens, nSize);
	unordered_map<vector<T>, int> sentenceNgrams = getNgrams(sentenceTokens, nSize);
	unordered_map<vector<T>, int> sentence1grams = getNgrams(sentenceTokens, 1);

	double V = oneGrams.size() + 1;
	double B = pow(V, nSize);
	double bottom = N + B * delta;

	cout << "V: " << V << endl;
	cout << "B: " << B << endl;
	cout << "N: " << N << endl;

	cout << "bottom: " <<bottom << endl;

	getProbs(sentenceNgrams, nGrams, bottom, delta);

	B = pow(V, 1);
	bottom = N + B * delta;
	


	cout << "bottom: " << bottom << endl;

}


int main(int argc, char* argv[]) {
	string file1 = string(argv[1]);
	string file2 = string(argv[2]);
	int size = atoi(argv[3]);
	double delta = atof(argv[4]);

	p4(file1, file2, size, delta);

	return 1;
}
