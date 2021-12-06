//		Taha Sohail (19L-2241)
#include<iostream>
#include<string>
#include<fstream>
#include"Admin.h"
#include"Helper.h"
#include"Blog.h"
#include"Dictionary.h"


using namespace std;



int main() {
	cout << "\n==================================================== SEARCH ENGINE ====================================================\n\n\n";
	int rex = -1;
	bool flag = false;
	do {
		cout << "\t\t\t\t\t\t      START PAGE \n\n";
		cout << "Search options:\n\t1). Dictionary\n\t2). Articles\n\t3). Login system\n\t0). Exit\n";
		cout << "\n\nSelect your option: ";
		cin >> rex;
		while (cin.fail())
		{
			cin.clear();									// clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n');						// ignore last input
			cout << "\n[NOTE]\tSelect one of the given options: ";
			cin >> rex;
		}
		if (rex == 1) {
			callDictionary();
		}
		else if (rex == 2) {
			callBlog();
		}
		else if (rex == 3) {
			loginSystem();
		}
		else if (rex == 0) {
			cout << "[INFO]\tThank you for visiting our search engine.\n[WARNING]\tYou are now exiting search engine.\n";
			system("pause");
			flag = true;
		}
		else {
			flag = false;
			cout << "[WARNING]\tImproper input. Please try again.\n";
		}
	} while (flag == false);
	

	return 0;
}