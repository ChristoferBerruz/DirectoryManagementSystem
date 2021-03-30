#include "BusinessWebContact.h"
#include <iostream>
#include <algorithm>

using namespace std;

BusinessWebContact::BusinessWebContact(const string& businessName, const string& businessType)
	: BusinessContact(businessName, businessType)
{

}

BusinessWebContact::BusinessWebContact
(
	const string& businessName,
	const string& businessType,
	const string& email,
	const string& website
):BusinessWebContact(businessName, businessType)
{
	addEmail(email);
	addWebsite(website);
}

void BusinessWebContact::addEmail(const string& email)
{
	emailAddresses.push_back(email);
}

void BusinessWebContact::addWebsite(const string& website)
{
	websites.push_back(website);
}

void BusinessWebContact::display() const
{
	BusinessContact::display();
	cout << "Web addresses: ";
	
	for_each(websites.begin(), websites.end(), [](const string& website)
		{
			cout << website << " ";
		}
	);
	
	cout << endl;

	cout << "Email addresses: ";
	for_each(emailAddresses.begin(), emailAddresses.end(), [](const string& email)
		{
			cout << email << " ";
		}
	);

	cout << endl;
}