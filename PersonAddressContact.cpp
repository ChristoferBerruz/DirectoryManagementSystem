#include "PersonAddressContact.h"
#include <iostream>

using namespace std;
PersonAddressContact::PersonAddressContact(const string& fullName, const string& gender, const string& address)
	: PersonContact(fullName, gender), address(address)
{

}

void PersonAddressContact::display() const
{
	PersonContact::display();
	cout << "Address: " << address << endl;
}