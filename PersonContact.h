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
	string GetGender() { return gender; }
	PersonContact(const string& fullName, const string& gender);
	virtual void Display() const;
	virtual ~PersonContact(){}
};

#endif // !PERSON_CONTACT_H
