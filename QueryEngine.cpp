#include "QueryEngine.h"
#include "PersonAddressContact.h"
#include "PersonEmailContact.h"
#include "BusinessPhoneContact.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

map<string, int> CLIQueryEngine::SearchPersonByNameOrderByState(const vector<Contact*>& contacts)
{
	cout << "Please enter name: ";
	string name;
	cin >> name;

	map<string, int> res;
	for_each(contacts.begin(), contacts.end(), [&name, &res] (Contact* const & contact)
		{
			PersonAddressContact* addressContact = dynamic_cast<PersonAddressContact*>(contact);

			// Only objects of PersonAddressContact
			if (addressContact && addressContact->GetName().find(name) != string::npos)
			{
				// Add to map
				string state = addressContact->GetAddress().GetState();
				if (res.find(state) == res.end())
				{
					res[state] = 0;
				}

				res[state] += 1;
			}
		}
	);

	return res;
}

map<string, int> CLIQueryEngine::SearchPersonByEmailOrderByGender(const vector<Contact*>& contacts)
{
	cout << "Please enter email domain: ";
	string emailDomain;
	cin >> emailDomain;

	map<string, int> res;

	for_each(contacts.begin(), contacts.end(), [&res, &emailDomain](Contact* const & contact) 
		{
			PersonEmailContact* emailContact = dynamic_cast<PersonEmailContact*>(contact);

			if (emailContact)
			{
				vector<string> emails = emailContact->GetEmails();
				vector<string>::iterator currentEmail;

				for (currentEmail = emails.begin(); currentEmail != emails.end(); currentEmail++)
				{
					if (currentEmail->find(emailDomain) != string::npos)
					{
						if (res.find(emailContact->GetGender()) == res.end())
							res[emailContact->GetGender()] = 0;

						res[emailContact->GetGender()] += 1;
						break;
					}
				}
			}
		}
	);

	return res;
}

map<string, int> CLIQueryEngine::SearchQueryBusinessByPhoneNumberOrderByCategory(const vector<Contact*>& contacts)
{
	cout << "Please enter area code: ";

	string areaCode;
	cin >> areaCode;

	map<string, int> res;

	// For U.S. phone numbers
	string targetAreaCode = "1-" + areaCode;

	for_each(contacts.begin(), contacts.end(), [&areaCode, &res, &targetAreaCode](Contact* const& contact) 
		{
			BusinessPhoneContact* phoneContact = dynamic_cast<BusinessPhoneContact*>(contact);
			if (phoneContact)
			{
				vector<string> phoneNums = phoneContact->GetPhoneNumbers();
				vector<string>::iterator phone;
				for (phone = phoneNums.begin(); phone != phoneNums.end(); phone++)
				{
					if (phone->rfind(targetAreaCode, 0) == 0)
					{
						// Found a match

						string category = phoneContact->GetCategory();

						if (res.find(category) == res.end())
							res[category] = 0;

						res[category] += 1;
						break;
					}
				}
			}
		}
	);

	return res;
	
}

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

string CLIQueryEngine::SearchQuery(const vector<Contact*>& contacts)
{
	cout << "Available Search queries are:\n";
	cout << "(1) Find the number of <name> ordered by state.\n";
	cout << "(2) Find the number of people in the directory whose email domain is <domain> ordered by the gender.\n";
	cout << "(3) Find the number of organizations in the directory whose " <<
		"phone number start with the area code <areaCode> ordered by the organization category.\n";

	cout << "Please enter a valid option: ";
	string option;
	cin >> option;

	map<string, int> queryRes;
	string label1;
	string label2 = "Number";
	if (option == "1")
	{
		queryRes = SearchPersonByNameOrderByState(contacts);
		label1 = "State";
	}
	else if (option == "2")
	{
		queryRes = SearchPersonByEmailOrderByGender(contacts);
		label1 = "Gender";
	}
	else if (option == "3")
	{
		queryRes = SearchQueryBusinessByPhoneNumberOrderByCategory(contacts);
		label1 = "Category";
	}
	
	string res = GenerateTable(queryRes, label1, label2);
	cout << res;
	return res;
}


string CLIQueryEngine::DisplayQuery(const vector<Contact*>& contacts)
{
	return " ";
}

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