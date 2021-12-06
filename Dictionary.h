#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
using namespace std;

int totalItems;

class Meaning
{
public:
	string meaning;
	string synonyms[2];
	string antonyms[2];

	Meaning()
	{

	}

};



void insertWord(unordered_map<string, Meaning>& umap)
{

	ifstream fin("Dictionary.txt");

	//totalnumber of words in the dictionary
	int totalWords;
	fin >> totalWords;

	totalItems = totalWords;
	//To store the word
	char word[90];

	//To store the meaning
	char meaning[200];

	//To store the synonyms
	char synonyms[90];

	//To store the antonyms
	char antonyms[90];

	fin.ignore();

	string w, m, s, a;

	for (int i = 0; i < totalWords; i++)
	{
		Meaning* newObj = new Meaning;

		fin.ignore();
		fin.getline(word, 90);
		fin.getline(meaning, 200);
		fin.getline(synonyms, 90);
		w = word;
		m = meaning;
		s = synonyms;

		//synonyms
		newObj->meaning = m;
		newObj->synonyms[0] = s;

		fin.getline(synonyms, 90);
		s = synonyms;
		newObj->synonyms[1] = s;

		//antonyms
		fin.getline(antonyms, 90);
		a = antonyms;
		newObj->antonyms[0] = a;

		fin.getline(antonyms, 90);
		a = antonyms;
		newObj->antonyms[1] = a;

		//insertWord in umap
		umap[w] = *newObj;
	}
	fin.close();
}


void deleteWord(unordered_map<string, Meaning>& umap)
{
	char w[90];
	string word;
	cout << "\nEnter word to delete from dictionary: ";
	cin >> w;
	word = w;

	if (umap.find(word) == umap.end())
	{
		cout << "\nWord: " << word << " does not exist in our database.\n";
	}

	// If the word found  
	else
	{
		ofstream out("History.txt", ios::app);
		out << "Word deleted: " << word << endl;				//	For search history
		out.close();

		totalItems--;

		umap.erase(word);

		ofstream fout("Dictionary.txt");
		fout << totalItems;
		fout << endl;
		fout << endl;

		unordered_map<string, Meaning>::iterator itr;
		for (itr = umap.begin(); itr != umap.end(); itr++)
		{

			fout << itr->first;
			fout << endl;

			Meaning newObj;
			newObj = itr->second;

			fout << newObj.meaning;
			fout << endl;

			fout << newObj.synonyms[0];
			fout << endl;

			fout << newObj.synonyms[1];
			fout << endl;

			fout << newObj.antonyms[0];
			fout << endl;

			fout << newObj.antonyms[1];
			fout << endl;

			fout << endl;
		}
		fout.close();
	}
}




void updateWord(unordered_map<string, Meaning>& umap)
{

	Meaning newObj;

	char word[90];

	//To store the meaning
	char meaning[200];

	//To store the synonyms
	char synonyms[90];

	//To store the antonyms
	char antonyms[90];

	string w, m, s, a;

	cout << "\nEnter word to update: ";
	cin >> word;
	w = word;



	if (umap.find(w) == umap.end())
	{
		cout << "\nWord: " << word << " does not exist in our database.\n";
	}

	// If the word found  
	else
	{
		ofstream out("History.txt", ios::app);
		out << "Word updated: " << word << endl;				//	For search history
		out.close();

		umap.erase(word);

		cout << "\nEnter meaning: ";
		cin >> meaning;
		newObj.meaning = meaning;

		cout << "\nEnter synonym 1: ";
		cin >> synonyms;
		newObj.synonyms[0] = synonyms;

		cout << "\nEnter synonym 2: ";
		cin >> synonyms;
		newObj.synonyms[1] = synonyms;

		cout << "\Enter antonym 1: ";
		cin >> antonyms;
		newObj.antonyms[0] = antonyms;

		cout << "\nEnter antonym 2: ";
		cin >> antonyms;
		newObj.antonyms[1] = antonyms;

		umap[word] = newObj;

		ofstream fout("Dictionary.txt");
		fout << totalItems;
		fout << endl;
		fout << endl;


		unordered_map<string, Meaning>::iterator itr;
		for (itr = umap.begin(); itr != umap.end(); itr++)
		{

			fout << itr->first;
			fout << endl;

			newObj = itr->second;

			fout << newObj.meaning;
			fout << endl;

			fout << newObj.synonyms[0];
			fout << endl;

			fout << newObj.synonyms[1];
			fout << endl;

			fout << newObj.antonyms[0];
			fout << endl;

			fout << newObj.antonyms[1];
			fout << endl;

			fout << endl;
		}
		fout.close();
	}
}



void displayWord()
{
	ifstream fin("Dictionary.txt");

	//totalnumber of words in the dictionary
	int totalWords;
	fin >> totalWords;

	//To store the word
	char word[90];

	//To store the meaning
	char meaning[200];

	//To store the synonyms
	char synonyms[90];

	//To store the antonyms
	char antonyms[90];

	fin.ignore();

	string w, m, s, a;

	for (int i = 0; i < totalWords; i++)
	{
		fin.ignore();
		fin.getline(word, 90);
		fin.getline(meaning, 200);
		fin.getline(meaning, 90);
		fin.getline(meaning, 90);
		fin.getline(meaning, 90);
		fin.getline(meaning, 90);
		w = word;
		m = meaning;
		cout << w << "\n";
	}
	fin.close();
}


void composeWord(unordered_map<string, Meaning>& umap) {
	Meaning newObj;

	char word[90];

	//To store the meaning
	char meaning[200];

	//To store the synonyms
	char synonyms[90];

	//To store the antonyms
	char antonyms[90];

	string w, m, s, a;

	cout << "\nEnter word to add to dictionary: ";
	cin >> word;
	w = word;



	if (umap.find(w) == umap.end())
	{
		ofstream out("History.txt", ios::app);
		out << "Word composed: " << word << endl;				//	For search history
		out.close();

		totalItems++;

		umap.erase(word);

		cout << "\nEnter meaning: ";
		cin >> meaning;
		newObj.meaning = meaning;

		cin.ignore();
		cout << "\nEnter synonym 1: ";
		cin >> synonyms;
		newObj.synonyms[0] = synonyms;

		cout << "\nEnter synonym 2: ";
		cin >> synonyms;
		newObj.synonyms[1] = synonyms;

		cout << "\Enter antonym 1: ";
		cin >> antonyms;
		newObj.antonyms[0] = antonyms;

		cout << "\nEnter antonym 2: ";
		cin >> antonyms;
		newObj.antonyms[1] = antonyms;

		umap[word] = newObj;

		ofstream fout("Dictionary.txt");
		fout << totalItems;
		fout << endl;
		fout << endl;


		unordered_map<string, Meaning>::iterator itr;
		for (itr = umap.begin(); itr != umap.end(); itr++)
		{

			fout << itr->first;
			fout << endl;

			newObj = itr->second;

			fout << newObj.meaning;
			fout << endl;

			fout << newObj.synonyms[0];
			fout << endl;

			fout << newObj.synonyms[1];
			fout << endl;

			fout << newObj.antonyms[0];
			fout << endl;

			fout << newObj.antonyms[1];
			fout << endl;

			fout << endl;
		}
		fout.close();
	}

	// If the word found  
	else
	{
		cout << "\nWord: " << word << " already exists in our database. Kindly select the edit option in settings to edit word.\n";		
	}
}



void searchWord(unordered_map<string, Meaning> umap)
{

	//To store the word
	string word;

	//To store the meaning
	Meaning meaning;


	cout << endl << "\nEnter word: ";
	cin >> word;
	system("CLS");

	ofstream out("History.txt", ios::app);
	out << "Searched word: " << word << endl;				//	For search history
	out.close();

	//if word does not found
	if (umap.find(word) == umap.end())
	{
		cout << "\nWord: " << word << " does not exist in our database.\n";
	}

	// If the word found  
	else
	{
		bool flag = false;
		meaning = umap.at(word);
		do {
			//word and meaning output
			cout << "\nWord: " << word << "\n\nMeaning:--->\t" << meaning.meaning << endl;
			int input;
			cout << "\nSelect one of the following actions: \n";
			cout << "\t1). See synonyms\n\t2). See antonyms\n\t3). See both synonyms and antonyms\n\t0). Exit to start page\n";
			cin >> input;
			while (cin.fail()) {
				cin.clear();									// clear input buffer to restore cin to a usable state
				cin.ignore(INT_MAX, '\n');						// ignore last input
				cout << "\n[NOTE]\tSelect one of the given options: ";
				cin >> input;
			}
			cout << endl << endl;
			//output synonyms
			if (input == 1)
			{
				cout << "Synonym 1: " << meaning.synonyms[0] << endl << endl;
				cout << "Synonym 2: " << meaning.synonyms[1] << endl << endl;
			}

			//output antonyms
			else if (input == 2)
			{
				cout << "Antonym 1: " << meaning.antonyms[0] << endl << endl;
				cout << "Antonym 2: " << meaning.antonyms[1] << endl << endl;
			}
			else if (input == 3)
			{
				cout << "Synonym 1: " << meaning.synonyms[0] << endl << endl;
				cout << "Synonym 2: " << meaning.synonyms[1] << endl << endl;
				cout << "Antonym 1: " << meaning.antonyms[0] << endl << endl;
				cout << "Antonym 2: " << meaning.antonyms[1] << endl << endl;
			}
			else if (input == 0) {
				flag = true;
				cout << "[INFO]\tReturning to start page.\n";
				system("pause");
			}
			else {
				cout << "[INFO]\tImproper input.\n";
				flag = false;
			}
		} while (flag == false);
	}
}

void callDictionary()
{
	unordered_map<string, Meaning> umap;

	insertWord(umap);
	system("CLS");
	displayWord();
	system("pause");
	cout << endl;
	searchWord(umap);
	system("CLS");
	/*while (1)
	{
		int input;
		cout << "enter 1 if you want to seacrch meaning of a word \n 2 if you want to deleteWord the word and 3 if you want to updateWord the word \n";
		cin >> input;
		if (input == 1)
			searchWord(umap);
		else if (input == 2)
			deleteWord(umap);
		else if (input == 3)
			updateWord(umap);
	}
	updateWord(umap);
	displayWord();*/
	
}



#endif // !DICTIONARY_H