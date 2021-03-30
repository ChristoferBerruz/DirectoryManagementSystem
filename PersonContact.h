#ifndef PERSON_CONTACT_H
#define PERSON_CONTACT_H

#include "Contact.h"
#include <string>

using namespace std;
class PersonContact : public Contact
{
private:
	string gender;
public:
	PersonContact(const string& fullName, const string& gender);
	virtual void Display() const;
};

#endif // !PERSON_CONTACT_H
