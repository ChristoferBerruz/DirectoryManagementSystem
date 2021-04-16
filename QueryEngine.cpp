#include "QueryEngine.h"
#include "SearchBusinessByEmailOrWebsite.h"
#include "SearchBusinessByPhoneNumber.h"
#include "SearchPeopleLivingInCT.h"
#include "SearchPersonByEmail.h"
#include "SearchPersonByName.h"

#include "DisplayBusiness.h"
#include "DisplayPerson.h"

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
	while (getline(cin,option) && lowerLim > option || option > upperLim)
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

	string res;

	BaseQuery* query = new SearchPersonByEmail();
	switch (optionNum) 
	{
	case 1:
		query = new SearchPersonByName();
		break;
	case 2:
		query = new SearchPersonByEmail();
		break;
	case 3:
		query = new SearchBusinessByPhoneNumber();
		break;
	case 4:
		query = new SearchBusinessByEmailOrWebsite();
		break;
	case 5:
		query = new SearchPeopleLivingInCT();
		break;
	default:
		break;
	}
	
	query->GetParametersFromCLI();
	res = query->Execute(contacts);

	delete query;
	return res;
}


string CLIQueryEngine::DisplayQuery(const vector<Contact*>& contacts)
{
	cout << "Available Display Queries are:\n";
	cout << "(1) Display all the details of an organization - <organization>\n";
	cout << "(2) Display all the details of a person - <name>\n";

	cout << "Please enter a valid option for Display Query: ";
	string option;
	while (getline(cin,option) && (option != "1" && option != "2"))
		cout << "Please enter a valid option for Display Query: ";

	string res;

	BaseQuery* query;
	if (option == "1")
	{
		query = new DisplayBusiness();
	}
	else
	{
		query = new DisplayPerson();
	}

	query->GetParametersFromCLI();
	res = query->Execute(contacts);
	delete query;
	return res;
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
	while(getline(cin,option) && (option != "1" && option != "2"))
		cout << "Please enter an option for Query type: ";

	if (option == "1")
	{
		return SearchQuery(contacts);
	}
	else {
		return DisplayQuery(contacts);
	}
}