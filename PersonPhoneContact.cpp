#include "PersonPhoneContact.h"
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;
PersonPhoneContact::PersonPhoneContact(const string& fullName, const string& gender) :PersonContact(fullName, gender)
{

}

PersonPhoneContact::PersonPhoneContact(const string& fullName, const string& gender, const string& phoneNum)
	:PersonPhoneContact(fullName, gender)
{
	AddPhoneNumber(phoneNum);
}

void PersonPhoneContact::AddPhoneNumber(const string& phoneNum)
{
	phoneNumbers.push_back(phoneNum);
}

void PersonPhoneContact::Display() const
{
	PersonContact::Display();
	cout << "Phone Numbers: ";
	for_each(phoneNumbers.begin(), phoneNumbers.end(), [](const string& phoneNum) 
		{
			cout << phoneNum << " ";
		}
	);
	cout << endl;
}

string PersonPhoneContact::PresentPhoneNumbers() const
{
	ostringstream buffer;
	for (int i = 0; i < phoneNumbers.size(); i++)
	{
		buffer << phoneNumbers[i];
		if (i != phoneNumbers.size() - 1)
			buffer << ", ";
	}
	return buffer.str();
}