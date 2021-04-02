#include "PersonAddressContact.h"
#include <iostream>

using namespace std;
PersonAddressContact::PersonAddressContact(const string& fullName, const string& gender, const Address& address)
	: PersonContact(fullName, gender), address(address)
{

}

void PersonAddressContact::Display() const
{
	PersonContact::Display();
	cout << "Address: " << address << endl;
}