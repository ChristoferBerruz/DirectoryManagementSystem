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

map<string, int> CLIQueryEngine::SearchQueryBusinessByEmailOrWebsiteOrderByCategory(const vector<Contact*>& contacts)
{
	cout << "Please enter emailEnding: ";
	string emailEnding;
	cin >> emailEnding;

	cout << "Please enter websiteDomain: ";
	string websiteDomain;
	cin >> websiteDomain;

	map<string, int> res;

	for_each(contacts.begin(), contacts.end(), [&emailEnding, &websiteDomain, &res](Contact* const& contact) 
		{
			BusinessWebContact* webContact = dynamic_cast<BusinessWebContact*>(contact);
			if (webContact)
			{
				vector<string> websites = webContact->GetWebAddresses();
				vector<string>::iterator website;

				// Bool to not double count the contact
				bool previouslyAdded = false;

				// Check the websites
				for (website = websites.begin(); website != websites.end(); website++)
				{
					if (website->find(websiteDomain) != string::npos)
					{
						// Website contains domain, so take it
						string category = webContact->GetCategory();

						if (res.find(category) == res.end())
							res[category] = 0;

						res[category] += 1;
						previouslyAdded = true;
						break;
					}
				}

				// Check the emails only if contact not previously counted
				if (!previouslyAdded)
				{
					vector<string> emails = webContact->GetEmailAddresses();
					vector<string>::iterator email;

					for (email = emails.begin(); email != emails.end(); email++)
					{
						if (email->find(emailEnding) != string::npos)
						{
							string category = webContact->GetCategory();

							if (res.find(category) == res.end())
								res[category] = 0;

							res[category] += 1;
							break;
						}
					}
				}
			}
		}
	);

	return res;
}

map<string, int> CLIQueryEngine::SearchQueryPeopleLivingInCTWithOutOfStatePhone(const vector<Contact*>& contacts)
{
	cout << "Please enter area code: ";

	string areaCode;
	cin >> areaCode;

	vector<Contact*>::const_iterator contact;

	vector<PersonAddressContact*> peopleLivingInCt;
	for_each(contacts.begin(), contacts.end(), [&peopleLivingInCt](Contact* const& contact)
		{
			PersonAddressContact* addressContact = dynamic_cast<PersonAddressContact*>(contact);
			if (addressContact && addressContact->GetAddress().GetState() == "Connecticut")
				peopleLivingInCt.push_back(addressContact);
		}
	);

	map<string, int> res;

	for_each(peopleLivingInCt.begin(), peopleLivingInCt.end(), [&res, &contacts, &areaCode, this](PersonAddressContact* const& addressContact)
		{
			string name = addressContact->GetName();
			string state = addressContact->GetAddress().GetState();
			for_each(contacts.begin(), contacts.end(), [&res, &areaCode, &name, &state, this](Contact* const& contact)
				{
					PersonPhoneContact* phoneContact = dynamic_cast<PersonPhoneContact*>(contact);
					if (phoneContact && phoneContact->GetName() == name)
					{
						// For U.S. numbers
						string target = "1-" + areaCode;

						vector<string> phoneNumbers = phoneContact->GetPhoneNumbers();

						bool notInState = true;
						for (auto phone = phoneNumbers.begin(); phone != phoneNumbers.end(); phone++)
						{
							// We find the area code, so this is not good
							if (phone->rfind(target, 0) == 0)
							{
								notInState = false;
							}
						}

						if (!notInState)
						{
							return;
						}

						// We pick the first phone number not in CT
						for (auto phone = phoneNumbers.begin(); phone != phoneNumbers.end(); phone++)
						{
							// Pick first number not in CT
							if (phone->rfind(target, 0) != 0)
							{
								string phoneAreaCode = (*phone).substr(2, 3);
								string state = (*this).areaQuickbook.GetState(phoneAreaCode);

								if (res.find(state) == res.end())
								{
									res[state] = 0;
								}

								res[state] += 1;
								break;
							}
						}

					}
				}
			);
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