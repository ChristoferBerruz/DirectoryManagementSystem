#include "PersonEmailContact.h"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;
PersonEmailContact::PersonEmailContact(const string& fullName, const string& gender, const string& email) 
	: PersonEmailContact(fullName, gender)
{
	AddEmail(email);
}

PersonEmailContact::PersonEmailContact(const string& fullName, const string& gender)
	: PersonContact(fullName, gender)
{

}

void PersonEmailContact::AddEmail(const string& email)
{
	emailAddresses.push_back(email);
}

void PersonEmailContact::Display() const
{
	PersonContact::Display();

	cout << "Email Addresses: ";

	for_each(emailAddresses.begin(), emailAddresses.end(), [](const string& email) 
		{
			cout << email << " ";
		}
	);

	cout << endl;
}

string PersonEmailContact::PresentEmails() const
{
	ostringstream buffer;
	for (int i = 0; i < emailAddresses.size(); i++)
	{
		buffer << emailAddresses[i];
		if (i != emailAddresses.size() - 1)
			buffer << ", ";
	}
	return buffer.str();
}