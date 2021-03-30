#ifndef PERSON_ADDRESS_CONTACT_H
#define PERSON_ADDRESS_CONTACT_H

#include "PersonContact.h"
#include <string>
using namespace std;

class PersonAddressContact : public PersonContact
{
private:
	string address;
public:
	PersonAddressContact(const string& fullName, const string& gender, const string& address);
	virtual void display() const;
};
#endif // !PERSON_ADDRESS_CONTACT_H
