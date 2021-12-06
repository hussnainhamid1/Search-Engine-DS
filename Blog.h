#pragma once
#ifndef BLOG_H
#define BLOG_H

#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
using namespace std;




void insertBlog(unordered_map<string, string>& umap)
{

	ifstream fin("Blog.txt");



	//To store the word
	char word[200];

	//To store the meaning
	char articles[65530];



	string w, a;

	while (!fin.eof())
	{
		fin.getline(word, 200);
		fin.getline(articles, 65530);

		w = word;
		a = articles;



		//insertBlog in umap
		umap[w] = a;

		fin.ignore();

	}
	fin.close();
}




void displayBlog()
{
	ifstream fin("Blog.txt");

	//To store the word
	char word[200];

	//To store the meaning
	char articles[65530];


	string w, a;

	while (!fin.eof())
	{
		fin.getline(word, 200);
		fin.getline(articles, 6000);

		w = word;
		a = articles;

		cout << "Article title: " << word << endl;

		fin.ignore();
	}
	fin.close();
}


void deleteBlog(unordered_map<string, string>& umap)
{
	char w[200];
	string word;
	cout << "\nEnter title of article to delete: ";
	cin >> w;
	word = w;

	if (umap.find(word) == umap.end())
	{
		cout << "\nArticle: " << word << " does not exist in our database.\n";
	}

	// If the word found  
	else
	{

		ofstream out("History.txt", ios::app);
		out << "Article deleted: " << word << endl;				//	For search history
		out.close();

		umap.erase(word);


		ofstream fout("Blog.txt");


		unordered_map<string, string>::iterator itr;
		for (itr = umap.begin(); itr != umap.end(); itr++)
		{

			fout << itr->first;
			fout << endl;

			fout << itr->second;
			fout << endl;
			fout << endl;

		}
		fout.close();
	}
}





void updateBlog(unordered_map<string, string>& umap)
{
	char word[200], article[6000];

	string w, a;

	cout << "\nEnter article title to update it: ";
	cin >> word;
	w = word;



	if (umap.find(w) == umap.end())
	{
		cout << "\nArticle: " << word << " does not exist in our database.\n";
	}

	// If the word found  
	else
	{
		ofstream out("History.txt", ios::app);
		out << "Article updated: " << word << endl;				//	For search history
		out.close();

		umap.erase(w);

		cout << "\nEnter article content: \n\n";
		cin >> article;
		a = article;


		umap[w] = a;

		ofstream fout("Blog.txt");



		unordered_map<string, string>::iterator itr;
		for (itr = umap.begin(); itr != umap.end(); itr++)
		{

			fout << itr->first;
			fout << endl;

			fout << itr->second;
			fout << endl;
			fout << endl;


		}
		fout.close();
	}
}







void composeBlog()
{
	char word[200];

	//To store the meaning
	char* articles = new char[65530];
	cout << "Enter the title of the article: ";
	cin >> word;
	cout << "\nEnter the article: \n\n";
	cin >> articles;

	ofstream out("History.txt", ios::app);
	out << "Article composed: " << word << endl;				//	For search history
	out.close();

	ofstream fout("Blog.txt", ios::app);

	fout << endl;
	fout << word << endl;
	fout << articles << endl;

	cout << "[INFO]\t Exiting compose blog.\n";
	system("pause");
}





void searchBlog(unordered_map<string, string> umap)
{

	//To store the word
	string word;

	string articles;

	cout << "\n\nEnter title of article you want to search: ";
	cin >> word;

	ofstream fout("History.txt", ios::app);
	fout << "Searched article " << word << endl;				//	For search history
	fout.close();


	//if word does not found
	if (umap.find(word) == umap.end())
	{
		cout << "[INFO]\tArticle title " << word << " does not exist in our database.\n";
	}

	// If the word found  
	else
	{
		articles = umap.at(word);

		//word and meaning output
		cout << "[INFO]\tDisplaying article.\n\nTitle: " << word << "\n\nContent:--->\t" << articles << endl;
	}
}



void callBlog()
{
	unordered_map<string, string> umap;
	insertBlog(umap);
	system("CLS");
	displayBlog();
	system("pause");
	searchBlog(umap);
	cout << "[INFO]\tReturning to start page.\n";
	system("pause");
	system("CLS");


	//while (1)
	//{
	//	int input;
	//	cout << "\n\n\n -1 if you want to read the article \n -2 to composeBlog the article \n 3 to deleteBlog the article \n 4 to updateBlog the article \n 5 to exit";
	//	cin >> input;
	//	if (input == 1)
	//		searchBlog(umap);
	//	else if (input == 2)
	//	{
	//		composeBlog();
	//		insertBlog(umap);
	//		displayBlog();
	//	}
	//	else if (input == 3)
	//	{
	//		deleteBlog(umap);
	//		displayBlog();
	//	}
	//	else if (input == 4)
	//	{
	//		updateBlog(umap);
	//		displayBlog();
	//	}
	//	else if (input == 5) {
	//		exit(0);
	//	}
	//}

}


#endif // !BLOG_H