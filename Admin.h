//		Taha Sohail (19L-2241)
#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class User {
	string username;
	int passcode;
	string full_name;
	int access_lvl[4];										//	[admin access(0), read access(1), write access(1), status(1)]= normal user
															//	[admin access(1), read access(1), write access(1), status(1)]= admins
public:
	User();
	string getUsername();									//------
	int getPasscode();										//	Getter functions
	string getFullName();									//
	int* getAccessLvl();									//--
	void setUsername(string str);							//------
	void setPasscode(int pass);								//	Setter functions
	void setFullName(string str);							//
	void setAccessLvl(int arr[4]);							//--
	User& operator=(User& obj);
	bool operator!=(User& obj);
	friend ostream& operator<<(ostream& out, const User& obj);
};

struct Node {												//	Node for hash table
	int key;
	User value;

	Node();
	Node(int key);
	Node(int p_key, User p_value);
};

class HashTable {											//	Hash table with linear probing ( modifications to class code )
	int capacity;
	int table_size;
	Node** table;
	Node* dummy;											//	To store in place of deleted value

public:
	HashTable();
	int hashFunc(int p_key);
	int sizeOfTable();
	bool isEmpty();
	void printTable();
	void insert(int p_key, User p_value);
	User remove(int p_key);
	User search(int p_key);
	User forgotten(string p_username);
};

class Admin : protected User {

public:
	Admin(User p_user);										//	Constructor
	void viewHistory();										//	Only admin can look at search history
	//void changeAccess(User& p_user);						//	Alterate the access of a user
};

#endif // !ADMIN_H