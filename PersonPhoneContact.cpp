#include "PersonPhoneContact.h"
#include <iostream>
#include <algorithm>
using namespace std;
PersonPhoneContact::PersonPhoneContact(const string& fullName, const string& gender) :PersonContact(fullName, gender)
{

}

PersonPhoneContact::PersonPhoneContact(const string& fullName, const string& gender, const string& phoneNum)
	:PersonPhoneContact(fullName, gender)
{
	addPhoneNumber(phoneNum);
}

void PersonPhoneContact::addPhoneNumber(const string& phoneNum)
{
	phoneNumbers.push_back(phoneNum);
}

void PersonPhoneContact::display() const
{
	PersonContact::display();
	cout << "Phone numbers: ";
	for_each(phoneNumbers.begin(), phoneNumbers.end(), [](const string& phoneNum) 
		{
			cout << phoneNum << " ";
		}
	);
	cout << endl;
}