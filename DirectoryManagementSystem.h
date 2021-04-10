#ifndef DIRECTORY_MANAGEMENT_SYSTEM_H
#define DIRECTORY_MANAGEMENT_SYSTEM_H

#include "Contact.h"
#include "Validator.h"
//#include "QueryEngine.h"
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
	//CLIQueryEngine engine;
	//void CreateContact(const vector<string>& words, string contactType);
	//void CreateBusinessContact(const vector<string>& words);
	void CreatePersonContact(const vector<string>& words);
	vector<string> ParseLine(const string& line);
	string TrimString(const string& word);
public:
	//void Query();
	//void DisplayResult();
	void IngestData(istream& is);
	void ShowAllContacts();
	friend istream& operator>>(istream& is, DirectoryManagementSystem dms);
};
#endif // !DIRECTORY_MANAGEMENT_SYSTEM_H
