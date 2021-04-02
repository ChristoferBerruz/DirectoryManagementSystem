#ifndef PERSON_ADDRESS_CONTACT_H
#define PERSON_ADDRESS_CONTACT_H

#include "PersonContact.h"
#include <string>
#include "Address.h"
using namespace std;

class PersonAddressContact : public PersonContact
{
private:
	Address address;
public:
	PersonAddressContact(const string& fullName, const string& gender, const Address& address);
	virtual void Display() const;
};
#endif // !PERSON_ADDRESS_CONTACT_H
