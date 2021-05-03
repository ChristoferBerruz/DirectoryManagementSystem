#ifndef DIRECTORY_MANAGEMENT_SYSTEM_H
#define DIRECTORY_MANAGEMENT_SYSTEM_H

#include "Contact.h"
#include "Validator.h"
#include "QueryEngine.h"
#include "Contact.h"
#include "Address.h"
#include "PersonAddressContact.h"
#include "PersonEmailContact.h"
#include "PersonPhoneContact.h"
#include "BusinessWebContact.h"
#include "BusinessAddressContact.h"
#include "BusinessPhoneContact.h"
#include <sstream>
#include <algorithm>
#include <exception>
#include <map>
#include <typeinfo>
#include <vector>
#include <iostream>
#include <set>
using namespace std;
class DirectoryManagementSystem
{
private:
	static DirectoryManagementSystem* Instance;
	~DirectoryManagementSystem();
	DirectoryManagementSystem() {}
	DirectoryManagementSystem& operator=(const DirectoryManagementSystem& dms){}
	DirectoryManagementSystem(const DirectoryManagementSystem& dms) {}
	vector<Contact*> contacts;
	set<string> uniqueNames;
	string queryResult;
	Validator validator;
	CLIQueryEngine engine;
	map <string, Contact*> quickBook;
	void CreateBusinessContact(const vector<string>& words);
	void CreatePersonContact(const vector<string>& words);
	Contact* FindInQuickbook(const string& name, const string& contactType);
	void AddToQuickbook(const string& name, const string& contactType, Contact* contact);
	vector<string> ParseLine(const string& line);
	string TrimString(const string& word);
public:
	static DirectoryManagementSystem* GetInstance();
	static void DeleteInstance();
	void Query();
	void DisplayResult();
	void IngestData(std::istream& is);
	void ShowAllContacts();
	vector<Contact*>& GetContacts() { return contacts; }
	size_t GetTotalUniqueContacts() { return uniqueNames.size(); }
	friend std::istream& operator>>(std::istream& is, DirectoryManagementSystem dms);
	friend ostream& operator<<(ostream& os, DirectoryManagementSystem dms);
};
#endif // !DIRECTORY_MANAGEMENT_SYSTEM_H
