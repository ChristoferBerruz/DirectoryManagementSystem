#include "QueryEngine.h"
#include "PersonAddressContact.h"
#include "PersonEmailContact.h"
#include "BusinessPhoneContact.h"
#include "BusinessWebContact.h"
#include "BusinessAddressContact.h"
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
string CLIQueryEngine::SearchPersonByNameOrderByState(const vector<Contact*>& contacts)
{
	cout << "Please enter name: ";
	string name;
	cin >> name;

	map<string, int> res = coreQuery.SearchPersonByNameOrderByState(contacts, name);
	
	return GenerateTable(res, "Name", "Number");
}

/// <summary>
/// Query II
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
string CLIQueryEngine::SearchPersonByEmailOrderByGender(const vector<Contact*>& contacts)
{
	cout << "Please enter email domain: ";
	string emailDomain;
	cin >> emailDomain;

	map<string, int> res = coreQuery.SearchPersonByEmailOrderByGender(contacts, emailDomain);
	return GenerateTable(res, "Gender", "Number");
}


/// <summary>
/// Query III
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
string CLIQueryEngine::SearchQueryBusinessByPhoneNumberOrderByCategory(const vector<Contact*>& contacts)
{
	cout << "Please enter area code: ";

	string areaCode;
	cin >> areaCode;

	map<string, int> res = coreQuery.SearchQueryBusinessByPhoneNumberOrderByCategory(contacts, areaCode);
	return GenerateTable(res, "Category", "Number");
}

/// <summary>
/// Query IV
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
string CLIQueryEngine::SearchQueryBusinessByEmailOrWebsiteOrderByCategory(const vector<Contact*>& contacts)
{
	cout << "Please enter emailEnding: ";
	string emailEnding;
	cin >> emailEnding;

	cout << "Please enter websiteDomain: ";
	string websiteDomain;
	cin >> websiteDomain;

	map<string, int> res = coreQuery.SearchQueryBusinessByEmailOrWebsiteOrderByCategory(contacts, emailEnding, websiteDomain);
	return GenerateTable(res, "Category", "Number");
}

/// <summary>
/// Query V
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
string CLIQueryEngine::SearchQueryPeopleLivingInCTWithOutOfStatePhone(const vector<Contact*>& contacts)
{
	cout << "Please enter area code: ";

	string areaCode;
	cin >> areaCode;

	map<string, int> res = coreQuery.SearchQueryPeopleLivingInCTWithOutOfStatePhone(contacts, areaCode);

	return GenerateTable(res, "State", "Number");
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

	string res;

	switch (optionNum) 
	{
	case 1:
		res = SearchPersonByNameOrderByState(contacts);
		break;
	case 2:
		res = SearchPersonByEmailOrderByGender(contacts);
		break;
	case 3:
		res = SearchQueryBusinessByPhoneNumberOrderByCategory(contacts);
		break;
	case 4:
		res = SearchQueryBusinessByEmailOrWebsiteOrderByCategory(contacts);
		break;
	case 5:
		res = SearchQueryPeopleLivingInCTWithOutOfStatePhone(contacts);
		break;
	default:
		break;
	}
	
	cout << res;
	return res;
}


string CLIQueryEngine::DisplayQuery(const vector<Contact*>& contacts)
{
	cout << "Available Display Queries are:\n";
	cout << "(1) Display all the details of an organization - <organization>\n";
	cout << "(2) Display all the details of a person - <name>\n";

	cout << "Please enter a valid option for Display Query: ";
	string option;
	while (cin >> option && (option != "1" && option != "2"))
		cout << "Please enter a valid option for Display Query: ";

	string res;
	if (option == "1")
	{
		res =  GetBusinessInfo(contacts);
	}
	else
	{
		res =  GetPersonInfo(contacts);
	}

	cout << res;
	return res;
}


string CLIQueryEngine::FormatVector(const vector<string>& elements)
{
	ostringstream buffer;
	for (int i = 0; i < elements.size(); i++)
	{
		buffer << elements[i];
		if (i != elements.size() - 1)
			buffer << ", ";
	}

	return buffer.str();
}


string CLIQueryEngine::GetBusinessInfo(const vector<Contact*>& contacts)
{
	cout << "Enter name of organization: ";
	
	string organization;
	cin >> organization;

	vector<Contact*> businessContacts;
	copy_if(contacts.begin(), contacts.end(), back_insert_iterator<vector<Contact*>>(businessContacts), [&organization](Contact* const contact)
		{
			return dynamic_cast<BusinessContact*>(contact) && contact->GetName() == organization;
		}
	);


	// We are going to dump the information using this
	ostringstream buffer;

	// All possible combinations
	string webBusiness = typeid(BusinessWebContact).name();
	string phoneBusiness = typeid(BusinessPhoneContact).name();
	string addressBusiness = typeid(BusinessAddressContact).name();
	for (int i = 0; i < businessContacts.size(); i++)
	{
		Contact* contact = businessContacts[i];
		if (i == 0)
		{
			BusinessContact* business = dynamic_cast<BusinessContact*>(contact);
			buffer << "Organization: " << business->GetName();
			buffer << "Category: " << business->GetCategory();
		}

		string className = typeid(*contact).name();
		if (className == webBusiness)
		{
			BusinessWebContact* webContact = dynamic_cast<BusinessWebContact*>(contact);
			buffer << "Web addresses: ";
			
			vector<string> websites = webContact->GetWebAddresses();
			buffer << FormatVector(websites) << endl;

			buffer << "Email addresses: ";
			vector<string> emails = webContact->GetEmailAddresses();
			buffer << FormatVector(emails) << endl;
		}

		if (className == phoneBusiness)
		{
			BusinessPhoneContact* phoneContact = dynamic_cast<BusinessPhoneContact*>(contact);
			buffer << "Phone numbers: ";
			buffer << FormatVector(phoneContact->GetPhoneNumbers()) << endl;
		}

		if (className == addressBusiness)
		{
			BusinessAddressContact* addressContact = dynamic_cast<BusinessAddressContact*>(contact);
			buffer << "Address: \n";
			Address address = addressContact->GetAddress();
			buffer << "Street: " << address.GetStreet();
			buffer << "City: " << address.GetCity();
			buffer << "State: " << address.GetState();
			buffer << "Zip: " << address.GetZipcode();
		}
	}
	return buffer.str();
}


string CLIQueryEngine::GetPersonInfo(const vector<Contact*>& contacts)
{
	string dummy;
	getline(cin, dummy);
	cout << "Enter name of person: ";
	string name;
	getline(cin, name);
	vector<Contact*> personContacts;
	copy_if(contacts.begin(), contacts.end(), back_insert_iterator<vector<Contact*>>(personContacts), [&name](Contact* const contact) 
		{
			return dynamic_cast<PersonContact*>(contact) && contact->GetName() == name;
		}
	);

	// All possible combinatons
	string addressPerson = typeid(PersonAddressContact).name();
	string phonePerson = typeid(PersonPhoneContact).name();
	string emailPerson = typeid(PersonEmailContact).name();

	// We output here
	ostringstream buffer;
	for (int i = 0; i < personContacts.size(); i++)
	{
		Contact* contact = personContacts[i];
		if (i == 0) 
		{
			PersonContact* person = dynamic_cast<PersonContact*>(contact);
			buffer << "Name: " << person->GetName() << endl;
			buffer << "Gender: " << person->GetGender() << endl;
		}

		string className = typeid(*contact).name();

		if (className == emailPerson)
		{
			PersonEmailContact* emailContact = dynamic_cast<PersonEmailContact*>(contact);
			buffer << "Email: " << FormatVector(emailContact->GetEmails()) << endl;
		}

		if (className == phonePerson)
		{
			PersonPhoneContact* phoneContact = dynamic_cast<PersonPhoneContact*>(contact);
			buffer << "Phone numbers: " << FormatVector(phoneContact->GetPhoneNumbers()) << endl;
		}
		if (className == addressPerson)
		{
			PersonAddressContact* addressContact = dynamic_cast<PersonAddressContact*>(contact);
			buffer << "Address: \n";
			Address address = addressContact->GetAddress();
			buffer << "Street: " << address.GetStreet() << endl;
			buffer << "City: " << address.GetCity() << endl;
			buffer << "State: " << address.GetState() << endl;
			buffer << "Zip: " << address.GetZipcode() << endl;
		}
	}

	return buffer.str();
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