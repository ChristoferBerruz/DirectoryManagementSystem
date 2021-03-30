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
	AddPhoneNumber(phoneNum);
}

void BusinessPhoneContact::AddPhoneNumber(const string& phoneNum) 
{
	phoneNumbers.push_back(phoneNum);
}


void BusinessPhoneContact::Display() const
{
	BusinessContact::Display();

	cout << "Phone Numbers: ";

	for_each(phoneNumbers.begin(), phoneNumbers.end(), [](const string& phoneNum)
		{
			cout << phoneNum << " ";
		}
	);

	cout << endl;
}