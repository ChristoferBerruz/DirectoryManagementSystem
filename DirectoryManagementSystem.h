#ifndef DIRECTORY_MANAGEMENT_SYSTEM_H
#define DIRECTORY_MANAGEMENT_SYSTEM_H

#include "Contact.h"
#include "Validator.h"
//#include "QueryEngine.h"
#include <map>
#include <typeinfo>
#include <vector>
#include <iostream>
using namespace std;
class DirectoryManagementSystem
{
private:
	vector<Contact*> contacts;
	int totalContacts;
	string queryResult;
	Validator validator;
	map <string, Contact*> quickBook;
	//CLIQueryEngine engine;
	//void CreateContact(const vector<string>& words, string contactType);
	//void CreateBusinessContact(const vector<string>& words);
	void CreatePersonContact(const vector<string>& words);
	Contact* FindInQuickbook(const string& name, const string& contactType);
	void AddToQuickbook(const string& name, const string& contactType, Contact* contact);
	vector<string> ParseLine(const string& line);
	string TrimString(const string& word);
public:
	//void Query();
	//void DisplayResult();
	~DirectoryManagementSystem();
	void IngestData(istream& is);
	void ShowAllContacts();
	friend istream& operator>>(istream& is, DirectoryManagementSystem dms);
};
#endif // !DIRECTORY_MANAGEMENT_SYSTEM_H
