///////	Functions by Taha
// This was created to reduce the code in main.cpp and make it easier to read for evaluator
#pragma once
#ifndef HELPER_H
#define HELPER_H
#include"Admin.h"
#include"Blog.h"
#include"Dictionary.h"
using namespace std;


void login(HashTable*& table);											//	Login to existing account
void newUser(HashTable*& table);										//	Regester new account
void forgot(HashTable*& table);											//	If user forgets password

void mainMenu(HashTable*& table);										//	The main display after login system is called
void loadScr(HashTable*& table);										//	This will load all users from .txt file to console
bool checkSimilarity(int pass1, int pass2);								//	This will check if both strings are the same
void loginSystem();

bool check(int arr1[], int arr2[]);
void adminSettings(HashTable*& table, Admin& admin);					//	For admin settings


////////////////////// Function Implementation /////////////////////////
bool check(int arr1[], int arr2[]) {
	for (int i = 0; i < 4; i++) {
		if (arr1[i] != arr2[i])
			return false;
	}
	return true;
}

//----------- Settings menu for admin --------------
void adminSettings(HashTable*& table, Admin& admin) {
	int rex = -1;
	bool flag = false;
	unordered_map<string, Meaning> wmap;
	unordered_map<string, string> bmap;
	do {
		cout << "============================================ ADMIN SETTINGS =======================================================\n";
		cout << "[INFO]\t\tWelcome Admin. Select one of the following settings to proceed.\n";
		cout << "\n\t1). View complete search history\n\t2). View all users\n\t3). Add new word to dictionary\n\t4). Add new article";
		cout << "\n\t5). Update word\n\t6). Update article\n\t7). Remove word from dictionary\n\t8). Remove article\n\t0). Exit admin settings\n";
		cout << "\nEnter prefered setting: ";
		cin >> rex;
		while (cin.fail()) {
			cin.clear();									// clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n');						// ignore last input
			cout << "\n[NOTE]\tSelect one of the given options: ";
			cin >> rex;
		}
		if (rex == 1) {										//	Search History
			system("CLS");
			admin.viewHistory();
			ofstream out("History.txt", ios::app);
			out << "Search history viewed" << endl;
			out.close();
		}
		else if (rex == 2) {								//	Print all users
			system("CLS");
			table->printTable();

			ofstream out("History.txt", ios::app);
			out << "User list printed" << endl;				//	For search history
			out.close();

			cout << "[INFO]\tReturning to admin settings.\n";
			system("pause");
		}
		else if (rex == 3) {
			system("CLS");
			insertWord(wmap);
			composeWord(wmap);
		}
		else if (rex == 4) {
			system("CLS");
			composeBlog();
		}
		else if (rex == 5) {
			system("CLS");
			insertWord(wmap);
			updateWord(wmap);
		}
		else if (rex == 6) {
			system("CLS");
			insertBlog(bmap);
			updateBlog(bmap);
		}
		else if (rex == 7) {
			system("CLS");
			insertWord(wmap);
			deleteWord(wmap);
		}
		else if (rex == 8) {
			system("CLS");
			insertBlog(bmap);
			deleteBlog(bmap);
		}
		else if (rex == 0) {
			cout << "[INFO]\tThank you for visiting admin settings page.\n[WARNING]\tYou are now exiting the admin settings page.\n";
			system("pause");
			flag = true;
		}
		else {
			flag = false;
			cout << "[WARNING]\tImproper input. Please try again.\n";
		}
		system("CLS");
	} while (flag == false);

}

//----------- To call all functions to main --------------
void loginSystem() {
	HashTable* table = new HashTable;
	mainMenu(table);
}

//----------- Check similarity in strings -------------
bool checkSimilarity(int pass1, int pass2) {
	if (pass1 == pass2)
		return true;
	return false;
}

//----------- Function to load all users -------------
void loadScr(HashTable*& table) {
	system("CLS");
	cout << "[INFO]\tUpdating users in  Hash Table.\n";
	ifstream fin;
	fin.open("Users.txt");
	string username, full_name;
	int passcode = -1, access_lvl[4];
	User temp;

	while (fin.eof() == 0) {
		fin.ignore();
		getline(fin, username, ';');
		temp.setUsername(username);
		fin >> passcode;
		temp.setPasscode(passcode);
		getline(fin, full_name, ';');
		temp.setFullName(full_name);
		for (int i = 0; i < 4; i++)
			fin >> access_lvl[i];
		temp.setAccessLvl(access_lvl);
		table->insert(passcode, temp);
		
		/*cout << "\nUsername: " << username << "\tPasscode: " << passcode << "\tFull Name: " << full_name << "\tAccess Level: ";
		for (int i = 0; i < 4; i++)
			cout << access_lvl[i];
		cout << endl;*/

	}
	system("pause");
}

//----------- Function to display main menu of login --------------
void mainMenu(HashTable*& table) {
	int rex = -1;
	bool flag = false;
	do {
		loadScr(table);
		system("CLS");
		cout << "\n==================================================== LOGIN PAGE =====================================================\n";
		cout << "\n[INFO]\t\tWelcome to our login page.\nPlease select one of the following options to proceed.";
		cout << "\n\t1). Login to existing account\n\t2). Create new account\n\t3). Forgot password\n\t0). Exit the Login page\n";
		cout << "\nSelect you option: ";
		cin >> rex;
		while (cin.fail())
		{
			cin.clear();									// clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n');						// ignore last input
			cout << "\n[NOTE]\tSelect one of the given options: ";
			cin >> rex;
		}
		if (rex == 1) {
			system("CLS");
			login(table);
		}
		else if (rex == 2) {
			system("CLS");
			newUser(table);
		}
		else if (rex == 3) {
			system("CLS");
			forgot(table);
		}
		else if (rex == 0) {
			cout << "[INFO]\tThank you for visiting our login page.\n[WARNING]\tYou are now exiting the login page.\n";
			system("pause");
			flag = true;
		}
		else {
			flag = false;
			cout << "[WARNING]\tImproper input. Please try again.\n";
		}
		system("CLS");
	} while (flag == false);
}

//----------- Function to login ------------
void login(HashTable*& table) {
	string username;
	int passcode = -1;
	cout << "\nWelcome user.\n\nEnter username: ";
	cin.ignore();
	getline(cin, username);
	cout << "[NOTE]\t************ Passcode must be in numbers **************\nEnter password: ";
	//cin.ignore();
	cin >> passcode;
	while (cin.fail())
	{
		cin.clear();									// clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n');						// ignore last input
		cout << "[NOTE]\t************ Passcode must be in numbers **************\nEnter password: ";
		//cin.ignore();
		cin >> passcode;
	}
	User user = table->search(passcode);
	User dummy_obj;
	if (user != dummy_obj) {
		//////////////////////	Add code for new articles here //////////////////
		int admin[] = { 1,1,1,1 }, normal[] = { 0,1,1,1 };
		bool flag = check(user.getAccessLvl(), admin);
		if (flag == true) {								//	Admin access
			system("CLS");
			ofstream out("History.txt", ios::app);
			out << "Admin login " << username << endl;
			out.close();
			Admin admin(user);
			adminSettings(table, admin);
		}
		else {
			ofstream out("History.txt", ios::app);
			out << "User login " << username << endl;
			out.close();
			system("CLS");
			int* arr = user.getAccessLvl();
			if (arr[2] == 1) {
				do {
					cout << "\nSelect one of the following actions: \n";
					cout << "\n\t1). Add word to dictionary\n\t2). Add article\n\t3). Get account info\n\t0).Go back to login page.\n";
					int rex = -1;
					cout << "\nEnter action: ";
					cin >> rex;
					while (cin.fail()) {
						cin.clear();									// clear input buffer to restore cin to a usable state
						cin.ignore(INT_MAX, '\n');						// ignore last input
						cout << "\n[NOTE]\tSelect one of the given options: ";
						cin >> rex;
					}
					if (rex == 1) {										//	Add word
						system("CLS");
						unordered_map<string, Meaning> wmap;
						insertWord(wmap);
						composeWord(wmap);
					}
					else if (rex == 2) {								//	Add article
						system("CLS");
						composeBlog();

					}
					else if (rex == 3) {
						system("CLS");
						cout << "\t\tUSER CREDENTIALS\n" << user << endl;

						ofstream out("History.txt", ios::app);
						out << "User checked credentials" << endl;
						out.close();

						cout << "[INFO]\tReturning to actions screen.\n";
						system("pause");
					}
					else if (rex == 0) {
						ofstream out("History.txt", ios::app);
						out << "User log out " << username << endl;
						out.close();

						cout << "[INFO]\tThank you for loging in. Returning to actions menu.\n";
						system("pause");
						flag = true;
					}
					else {
						flag = false;
						cout << "[INFO]\tImproper input.\n";
					}
					system("CLS");
				} while (flag == false);
			}
		}
	}
}

//----------- Function to register ------------
void newUser(HashTable*& table) {
	system("CLS");
	cout << "\n\tWelcome new user\n\n";
	ofstream fout;
	fout.open("Users.txt", ios::app);
	if (!fout)
		cout << "[WARNING]\tFile not created.\n";
	else {
		system("CLS");
		string full_name, first_name, last_name;
		cout << "Enter First name: ";
		cin.ignore();
		getline(cin, first_name);
		first_name += ' ';
		cout << "Enter Last name: ";
		//cin.ignore();
		getline(cin, last_name);
		full_name = first_name + last_name;

		system("CLS");
		string username;
		bool flag = false;
		User dummy_obj;
		do {
			cout << "Enter Username: ";
			//cin.ignore();
			getline(cin, username);
			User temp = table->forgotten(username);
			if (temp != dummy_obj)
				cout << "Username has already been taken. \n";
			else
				flag = true;

		} while (flag == false);

		system("CLS");
		int pass1 = -1, pass2 = -1;
		do {
			cout << "[NOTE]\t************ Passcode must be in numbers **************\nEnter password: ";
			//cin.ignore();
			cin >> pass1;
			while (cin.fail())
			{
				cin.clear();									// clear input buffer to restore cin to a usable state
				cin.ignore(INT_MAX, '\n');						// ignore last input
				cout << "[NOTE]\t************ Passcode must be in numbers **************\nEnter password: ";
				//cin.ignore();
				cin >> pass1;
			}
			cout << "\nConfirm password: ";
			//cin.ignore();
			cin >> pass2;
			while (cin.fail())
			{
				cin.clear();									// clear input buffer to restore cin to a usable state
				cin.ignore(INT_MAX, '\n');						// ignore last input
				cout << "\nConfirm password: ";
				//cin.ignore();
				cin >> pass2;
			}
			if (checkSimilarity(pass1, pass2) == false)
				cout << "[WARNING]\tPasswords do not match. Kindly re-enter password.\n";
		} while (checkSimilarity(pass1, pass2) == false);

		// Input the user credentials into the file
		fout << username << ";" << pass1 << " " << full_name << ";0 1 1 1" << endl;
		cout << "[INFO]\tUser added to database.\n";
	}
	fout.close();
}

//----------- To recover password -------------
void forgot(HashTable*& table) {
	string username;
	cout << "Enter username: ";
	cin.ignore();
	getline(cin, username);

	User temp = table->forgotten(username);
	if (temp.getPasscode() != -1)
		cout << "Your passcode is: " << temp.getPasscode() << endl;
	else
		cout << "Username not found.\n";

	cout << "[INFO]\tReturning to login page.\n";
	system("pause");
}

#endif // !HELPER_H