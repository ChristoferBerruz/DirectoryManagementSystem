#include "PersonEmailContact.h"
#include <iostream>
#include <algorithm>

using namespace std;
PersonEmailContact::PersonEmailContact(const string& fullName, const string& gender, const string& email) 
	: PersonEmailContact(fullName, gender)
{
	addEmail(email);
}

PersonEmailContact::PersonEmailContact(const string& fullName, const string& gender)
	: PersonContact(fullName, gender)
{

}

void PersonEmailContact::addEmail(const string& email)
{
	emailAddresses.push_back(email);
}

void PersonEmailContact::display() const
{
	PersonContact::display();

	cout << "Emails: ";

	for_each(emailAddresses.begin(), emailAddresses.end(), [](const string& email) 
		{
			cout << email << " ";
		}
	);

	cout << endl;
}