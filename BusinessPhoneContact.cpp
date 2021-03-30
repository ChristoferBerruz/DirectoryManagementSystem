#include "BusinessPhoneContact.h"
#include <iostream>
#include <algorithm>

using namespace std;

BusinessPhoneContact::BusinessPhoneContact
(
	const string& businessName,
	const string& businessType
) : BusinessContact(businessName, businessType)
{

}

BusinessPhoneContact::BusinessPhoneContact(
	const string& businessName,
	const string& businessType,
	const string& phoneNum
) : BusinessPhoneContact(businessName, businessType)
{
	addPhoneNumber(phoneNum);
}

void BusinessPhoneContact::addPhoneNumber(const string& phoneNum) 
{
	phoneNumbers.push_back(phoneNum);
}


void BusinessPhoneContact::display() const
{
	BusinessContact::display();

	cout << "Phone Numbers: ";

	for_each(phoneNumbers.begin(), phoneNumbers.end(), [](const string& phoneNum)
		{
			cout << phoneNum << " ";
		}
	);

	cout << endl;
}