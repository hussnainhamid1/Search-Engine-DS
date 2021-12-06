//		Taha Sohail (19L-2241)
#include"Admin.h"
#include<stack>
////////////////// User Class /////////////////////
//--------- Constructor -----------
User::User() {
	username = '\0';
	passcode = -1;
	full_name = '\0';
	access_lvl[0] = 0;									//	Admin access
	access_lvl[1] = 1;									//	Read access
	access_lvl[2] = 1;									//	Write access
	access_lvl[3] = 1;									//	Status
}
//---------- Getter functions --------------
string User::getUsername() {
	return this->username;
}
int User::getPasscode() {
	return this->passcode;
}
string User::getFullName() {
	return this->full_name;
}
int* User::getAccessLvl() {
	return this->access_lvl;
}
//----------- Setter functions --------------
void User::setUsername(string str) {
	this->username = str;
}
void User::setPasscode(int pass) {
	this->passcode = pass;
}
void User::setFullName(string str) {
	this->full_name = str;
}
void User::setAccessLvl(int arr[4]) {
	for (int i = 0; i < 4; i++)
		this->access_lvl[i] = arr[i];
}
//------------- Operator = overloading -----------
User& User::operator=(User& obj) {
	this->username = obj.username;
	this->passcode = obj.passcode;
	this->full_name = obj.full_name;
	for (int i = 0; i < 4; i++)
		this->access_lvl[i] = obj.access_lvl[i];
	return obj;
}
//------------- Operator != overloading -----------
bool User::operator!=(User& obj) {
	if (this->username != obj.username)
		return true;
	if (this->passcode != obj.passcode)
		return true;
	if (this->full_name != obj.full_name)
		return true;
	return false;
}
//------------- Operator << overloading ------------
ostream& operator<<(ostream& out, const User& obj) {
	cout << "\nUsername: " << obj.username << "\nPasscode: " << obj.passcode << "\nFull name: " << obj.full_name << "\nAccess level: ";
	for (int i = 0; i < 4; i++)
		cout << obj.access_lvl[i];
	cout << "\n\n";
	return out;
}

////////////////// Node Class //////////////////////
//------------- Constructors ------------
Node::Node() {
	key = 0;
	value;
}
Node::Node(int p_key) {
	this->key = p_key;
	value;
}
Node::Node(int p_key, User p_value) {
	this->key = p_key;
	this->value = p_value;
}

////////////////// Hash Table Class /////////////////////
//------------- Constructor -------------
HashTable::HashTable() {
	capacity = 100;
	table_size = 0;
	table = new Node * [capacity];
	dummy = new Node(-1);
	for (int i = 0; i < capacity; i++)
		table[i] = NULL;
}
//-------------- Converts key into hash value -----------
int HashTable::hashFunc(int p_key) {
	return p_key % capacity;
}
//-------------- Checks if table is empty --------------
bool HashTable::isEmpty() {
	if (table_size == 0)
		return true;
	return false;
}
//-------------- Returns size of the table -------------
int HashTable::sizeOfTable() {
	return table_size;
}
//-------------- Prints all users in the table --------------
void HashTable::printTable() {
	system("CLS");
	cout << "[INFO]\tPrinting table contents.\n";
	for (int i = 0; i < capacity; i++) {
		if (table[i] != NULL && table[i]->key != -1)
			cout << table[i]->value << endl;
	}		
}
//-------------- Insert elements in the table --------------
void HashTable::insert(int p_key, User p_value) {
	Node* temp = new Node(p_key, p_value);
	int hash_value = hashFunc(p_key);
	while (table[hash_value] != NULL && (table[hash_value]->key != p_key || table[hash_value]->key != -1)) {
		hash_value++;
		hash_value %= capacity;
	}
	if (table[hash_value] == NULL || table[hash_value]->key == -1) {
		table_size++;
		table[hash_value] = temp;
	}
	table[hash_value] = temp;
	//cout << "[INFO]\tEmpty location found. Value has been inserted.\n";
}
//--------------- Remove elements from the table --------------
User HashTable::remove(int p_key) {
	int hash_value = hashFunc(p_key);
	while (table[hash_value] != NULL) {
		if (table[hash_value]->key == p_key) {
			Node* temp = table[hash_value];
			table[hash_value] = dummy;
			table_size--;
			cout << "[INFO]\tKey was found. Value has been deleted.\n";
			return temp->value;
		}
		hash_value++;
		hash_value %= capacity;
	}
	cout << "[WARNING]\tKey was not found. Value has not been deleted.\n";
	User dummy_obj;
	return dummy_obj;
}
//----------------- Search value from key ---------------
User HashTable::search(int p_key) {
	int hash_value = hashFunc(p_key);
	int count = 0;
	User dummy_obj;
	while (table[hash_value] != NULL) {
		count = 0;
		if (count++ > capacity) {									//	To avoid infinite loop
			cout << "[WARNING]\tInfinite loop triggered. Returning dummy value.\n";
			return dummy_obj;
		}
		if (table[hash_value]->key == p_key) {
			cout << "[INFO]\tKey was found. Returning value.\n";
			return table[hash_value]->value;
		}
		hash_value++;
		hash_value %= capacity;
	}
	cout << "[WARNING]\tKey " << p_key << " was not found. Dummy value has been returned.\n";
	return dummy_obj;
}
//----------------- To find forgotten password ---------------
User HashTable::forgotten(string p_username) {
	for (int i = 0; i < capacity; i++) {
		if (table[i] != NULL && table[i]->key != -1) {
			if (table[i]->value.getUsername() == p_username) {
				cout << "[INFO]\tUsername found.\n";
				return table[i]->value;
			}
		}
	}
	cout << "[INFO]\tUsername does not exist.\n";
	User dummy_obj;
	return dummy_obj;

}

////////////////// Admin Class ////////////////////
//------------------ Constructor -------------------
Admin::Admin(User p_user) {
	this->setUsername(p_user.getUsername());
	this->setPasscode(p_user.getPasscode());
	this->setFullName(p_user.getFullName());
	this->setAccessLvl(p_user.getAccessLvl());
}
////------------------ Change Access level of users --------------------
//// Helper functions for acess
//void adminAccess(User& p_user) {
//	int* arr = p_user.getAccessLvl();
//	char conformation;
//	bool flag = false;
//	if (arr[0] == 0) {
//		cout << "User does not have admin access.\n";
//		do {
//			cout << "Do you want to grant user admin access (Y/N): ";
//			cin >> conformation;
//			if (conformation == 'y' || conformation == 'Y') {
//				for (int i = 0; i < 4; i++)
//					arr[i] = 1;
//				cout << "[INFO]\tUser has been granted admin access.\n";
//				flag = true;
//			}
//			else if (conformation == 'n' || conformation == 'N') {
//				cout << "[INFO]\tUser was not given admin access.\n";
//				flag = true;
//			}
//			else {
//				cout << "[WARNING]\tImproper input. Press Y for granting admin access and N for revoking it.\n";
//				cin.get();
//			}
//			system("CLS");
//		} while (flag == false);
//	}
//	else {
//		cout << "User has admin access.\n";
//		do {
//			cout << "Do you want to revoke admin access (Y/N): ";
//			cin >> conformation;
//			if (conformation == 'y' || conformation == 'Y') {
//				arr[0] = 0;
//				cout << "[INFO]\tUser's admin access has been revoked.\n";
//				flag = true;
//			}
//			else if (conformation == 'n' || conformation == 'N') {
//				cout << "[INFO]\tUser's admin access was not revoked.\n";
//				flag = true;
//			}
//			else {
//				cout << "[WARNING]\tImproper input. Press Y for revoking admin access and N for granting it.\n";
//			}
//			cin.get();
//			system("CLS");
//		} while (flag == false);
//	}
//	p_user.setAccessLvl(arr);
//}
//void readAccess(User& p_user) {
//	int* arr = p_user.getAccessLvl();
//	char conformation;
//	bool flag = false;
//	if (arr[1] == 0) {
//		cout << "User does not have read access.\n";
//		do {
//			cout << "Do you want to grant user read access (Y/N): ";
//			cin >> conformation;
//			if (conformation == 'y' || conformation == 'Y') {
//				arr[1] = 1;
//				cout << "[INFO]\tUser has been granted read access.\n";
//				flag = true;
//			}
//			else if (conformation == 'n' || conformation == 'N') {
//				cout << "[INFO]\tUser was not given read access.\n";
//				flag = true;
//			}
//			else {
//				cout << "[WARNING]\tImproper input. Press Y for granting read access and N for revoking it.\n";
//				cin.get();
//			}
//			system("CLS");
//		} while (flag == false);
//	}
//	else {
//		cout << "User has read access.\n";
//		do {
//			cout << "Do you want to revoke read access (Y/N): ";
//			cin >> conformation;
//			if (conformation == 'y' || conformation == 'Y') {
//				arr[1] = 0;
//				cout << "[INFO]\tUser's read access has been revoked.\n";
//				flag = true;
//			}
//			else if (conformation == 'n' || conformation == 'N') {
//				cout << "[INFO]\tUser's read access was not revoked.\n";
//				flag = true;
//			}
//			else {
//				cout << "[WARNING]\tImproper input. Press Y for revoking admireadn access and N for granting it.\n";
//			}
//			cin.get();
//			system("CLS");
//		} while (flag == false);
//	}
//	p_user.setAccessLvl(arr);
//}
//void writeAccess(User& p_user) {
//	int* arr = p_user.getAccessLvl();
//	char conformation;
//	bool flag = false;
//	if (arr[0] == 0) {
//		cout << "User does not have write access.\n";
//		do {
//			cout << "Do you want to grant user write access (Y/N): ";
//			cin >> conformation;
//			if (conformation == 'y' || conformation == 'Y') {
//				arr[2] = 1;
//				cout << "[INFO]\tUser has been granted write access.\n";
//				flag = true;
//			}
//			else if (conformation == 'n' || conformation == 'N') {
//				cout << "[INFO]\tUser was not given write access.\n";
//				flag = true;
//			}
//			else {
//				cout << "[WARNING]\tImproper input. Press Y for granting write access and N for revoking it.\n";
//				cin.get();
//			}
//			system("CLS");
//		} while (flag == false);
//	}
//	else {
//		cout << "User has write access.\n";
//		do {
//			cout << "Do you want to revoke write access (Y/N): ";
//			cin >> conformation;
//			if (conformation == 'y' || conformation == 'Y') {
//				arr[2] = 0;
//				cout << "[INFO]\tUser's write access has been revoked.\n";
//				flag = true;
//			}
//			else if (conformation == 'n' || conformation == 'N') {
//				cout << "[INFO]\tUser's write access was not revoked.\n";
//				flag = true;
//			}
//			else {
//				cout << "[WARNING]\tImproper input. Press Y for revoking write access and N for granting it.\n";
//			}
//			cin.get();
//			system("CLS");
//		} while (flag == false);
//	}
//	p_user.setAccessLvl(arr);
//}
//void accountStatus(User& p_user) {
//	int* arr = p_user.getAccessLvl();
//	char conformation;
//	bool flag = false;
//	if (arr[0] == 0) {
//		cout << "User does not have access to his/her account.\n";
//		do {
//			cout << "Do you want to grant user access to his/her account (Y/N): ";
//			cin >> conformation;
//			if (conformation == 'y' || conformation == 'Y') {
//				arr[3] = 1;
//				cout << "[INFO]\tUser has been granted access to his/her account.\n";
//				flag = true;
//			}
//			else if (conformation == 'n' || conformation == 'N') {
//				cout << "[INFO]\tUser was not given access to his/her account.\n";
//				flag = true;
//			}
//			else {
//				cout << "[WARNING]\tImproper input. Press Y for granting access to his/her account and N for revoking it.\n";
//				cin.get();
//			}
//			system("CLS");
//		} while (flag == false);
//	}
//	else {
//		cout << "User has access to his/her account.\n";
//		do {
//			cout << "Do you want to revoke access to his/her account (Y/N): ";
//			cin >> conformation;
//			if (conformation == 'y' || conformation == 'Y') {
//				arr[3] = 0;
//				cout << "[INFO]\tUser's access to his/her account has been revoked.\n";
//				flag = true;
//			}
//			else if (conformation == 'n' || conformation == 'N') {
//				cout << "[INFO]\tUser's access to his/her account was not revoked.\n";
//				flag = true;
//			}
//			else {
//				cout << "[WARNING]\tImproper input. Press Y for revoking access to his/her account and N for granting it.\n";
//			}
//			cin.get();
//			system("CLS");
//		} while (flag == false);
//	}
//	p_user.setAccessLvl(arr);
//}
////	Main function for access
//void Admin::changeAccess(User& p_user) {
//	int rex = -1;
//	bool flag = false;
//	do {
//		cout << "Enter the access you want to allow/revoke: \n";
//		cout << "\n1). Admin access\n2). Read access\n3). Write access\n4). Account status\n0). Exit Admin settings.\n";
//		cin >> rex;
//		while (cin.fail()) {
//			cin.clear();									// clear input buffer to restore cin to a usable state
//			cin.ignore(INT_MAX, '\n');						// ignore last input
//			cout << "[NOTE]\tPlease enter one of the given options: ";
//			//cin.ignore();
//			cin >> rex;
//		}if (rex == 1) {
//			system("CLS");
//			adminAccess(p_user);
//		}
//		else if (rex == 2) {
//			system("CLS");
//			readAccess(p_user);
//		}
//		else if (rex == 3) {
//			system("CLS");
//			writeAccess(p_user);
//		}
//		else if (rex == 4) {
//			system("CLS");
//			accountStatus(p_user);
//		}
//		else if (rex == 0) {
//			cout << "[INFO]\tThank you for visiting the admin settings.\nPress \"ENTER\" to confirm\n";
//			cin.ignore();
//			cin.get();
//			flag = true;
//		}
//		else {
//			flag = false;
//			cout << "[WARNING]\tImproper input. Please try again.\n";
//		}
//	} while (flag == false);
//	
//}

//------------------ View entire search history -------------
void Admin::viewHistory() {
	ifstream fin;
	fin.open("History.txt");
	stack<string> s;
	string str;
	while (fin.eof() == 0) {
		getline(fin, str);
		s.push(str);
	}
	fin.close();
	if (!s.empty()) {

		int size_of_stack = s.size();
		cout << "[INFO]\tPrinting search history.\n";
		for (int i = 0; i < size_of_stack; i++) {
			cout << "\t" << i << "). " << s.top() << endl;
			s.pop();
		}
	}
	else
		cout << "Stack is empty\n";
	cout << "[INFO]\tReturning to admin settings.\n";
	system("pause");
}