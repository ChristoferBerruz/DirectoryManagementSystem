#include "QueryEngine.h"
#include "PersonAddressContact.h"
#include "PersonEmailContact.h"
#include "BusinessPhoneContact.h"
#include "BusinessWebContact.h"
#include "PersonPhoneContact.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

/// <summary>
/// Query I
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
map<string, int> CLIQueryEngine::SearchPersonByNameOrderByState(const vector<Contact*>& contacts)
{
	cout << "Please enter name: ";
	string name;
	cin >> name;

	map<string, int> res = coreQuery.SearchPersonByNameOrderByState(contacts, name);
	return res;
}

/// <summary>
/// Query II
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
map<string, int> CLIQueryEngine::SearchPersonByEmailOrderByGender(const vector<Contact*>& contacts)
{
	cout << "Please enter email domain: ";
	string emailDomain;
	cin >> emailDomain;

	map<string, int> res = coreQuery.SearchPersonByEmailOrderByGender(contacts, emailDomain);
	return res;
}


/// <summary>
/// Query III
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
map<string, int> CLIQueryEngine::SearchQueryBusinessByPhoneNumberOrderByCategory(const vector<Contact*>& contacts)
{
	cout << "Please enter area code: ";

	string areaCode;
	cin >> areaCode;

	map<string, int> res = coreQuery.SearchQueryBusinessByPhoneNumberOrderByCategory(contacts, areaCode);
	return res;
	
}

/// <summary>
/// Query IV
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
map<string, int> CLIQueryEngine::SearchQueryBusinessByEmailOrWebsiteOrderByCategory(const vector<Contact*>& contacts)
{
	cout << "Please enter emailEnding: ";
	string emailEnding;
	cin >> emailEnding;

	cout << "Please enter websiteDomain: ";
	string websiteDomain;
	cin >> websiteDomain;

	map<string, int> res = coreQuery.SearchQueryBusinessByEmailOrWebsiteOrderByCategory(contacts, emailEnding, websiteDomain);
	return res;
}

/// <summary>
/// Query V
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
map<string, int> CLIQueryEngine::SearchQueryPeopleLivingInCTWithOutOfStatePhone(const vector<Contact*>& contacts)
{
	cout << "Please enter area code: ";

	string areaCode;
	cin >> areaCode;

	map<string, int> res = coreQuery.SearchQueryPeopleLivingInCTWithOutOfStatePhone(contacts, areaCode);

	return res;
}

/// <summary>
/// Generates a nice table showing the results of a query
/// </summary>
/// <param name="queryResult"></param>
/// <param name="label1"></param>
/// <param name="label2"></param>
/// <returns></returns>
string CLIQueryEngine::GenerateTable(const map<string, int>& queryResult, const string& label1, const string& label2)
{
	ostringstream buffer;

	int cellLen = 20;
	buffer << setw(cellLen) << left << label1 << setw(cellLen) << left << label2 << endl;

	map<string, int>::const_iterator currentRecord;

	for (currentRecord = queryResult.begin(); currentRecord != queryResult.end(); currentRecord++)
	{
		buffer << setw(cellLen) << left << currentRecord->first << setw(cellLen) << currentRecord->second << endl;
	}

	return buffer.str();
}

/// <summary>
/// Deals with retrieving a valid search query option from CLI
/// </summary>
/// <returns></returns>
int CLIQueryEngine::GetSearchOptionFromCLI()
{
	// Buffer the prompt in memory given its size
	ostringstream tempOut;
	tempOut << "Available Search queries are:\n";
	tempOut << "(1) Find the number of people with <name> ordered by state.\n";
	tempOut << "(2) Find the number of people in the directory whose email domain is <domain> ordered by the gender.\n";
	tempOut << "(3) Find the number of organizations in the directory whose " <<
		"phone number start with the area code <areaCode> ordered by the organization category.\n";

	tempOut << "(4) Find the number of organizations in the directory with a " <<
		"<emailEnding> email or a <websiteDomain> website ordered by the organization category.\n";

	tempOut << "(5) Find the number of people in Connecticut whose"
		<< " phone numbers DO NOT BEGIN with <areaCode>.\n";

	// Dump prompt;
	cout << tempOut.str();
	cout << "Please enter a valid option: ";
	string option;

	// Handle option to be between valid range
	string lowerLim("1");
	string upperLim("5");
	while (cin >> option && lowerLim > option || option > upperLim)
		cout << "Please enter a valid option: ";

	return stoi(option);
}

/// <summary>
/// Handles selection and execution of a valid SearchQuery registered in the engine
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
string CLIQueryEngine::SearchQuery(const vector<Contact*>& contacts)
{
	
	int optionNum = GetSearchOptionFromCLI();

	map<string, int> queryRes;
	string label1;
	string label2 = "Number";

	switch (optionNum) 
	{
	case 1:
		queryRes = SearchPersonByNameOrderByState(contacts);
		label1 = "State";
		break;
	case 2:
		queryRes = SearchPersonByEmailOrderByGender(contacts);
		label1 = "Gender";
		break;
	case 3:
		queryRes = SearchQueryBusinessByPhoneNumberOrderByCategory(contacts);
		label1 = "Category";
		break;
	case 4:
		queryRes = SearchQueryBusinessByEmailOrWebsiteOrderByCategory(contacts);
		label1 = "Category";
		break;
	case 5:
		queryRes = SearchQueryPeopleLivingInCTWithOutOfStatePhone(contacts);
		label1 = "State";
		break;
	default:
		break;
	}
	
	string res = GenerateTable(queryRes, label1, label2);
	cout << res;
	return res;
}


string CLIQueryEngine::DisplayQuery(const vector<Contact*>& contacts)
{
	return " ";
}

/// <summary>
/// Handles and executes the registered Type of Queries
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
string CLIQueryEngine::Query(const vector<Contact*>& contacts)
{
	cout << "Available Queries are: (1) SearchQuery or (2) DisplayQuery." << endl;
	string option;
	cout << "Please enter an option for Query type: ";
	while(cin >> option && (option != "1" && option != "2"))
		cout << "Please enter an option for Query type: ";

	if (option == "1")
	{
		return SearchQuery(contacts);
	}
	else {
		return DisplayQuery(contacts);
	}
}