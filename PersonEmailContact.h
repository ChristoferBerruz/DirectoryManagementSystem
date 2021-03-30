#ifndef PERSON_EMAIL_CONTACT_H
#define PERSON_EMAIL_CONTACT_H

#include "PersonContact.h"
#include <vector>
#include <string>

using namespace std;
class PersonEmailContact: public PersonContact
{
private:
	vector<string> emailAddresses;

public:
	PersonEmailContact(const string& fullName, const string& gender, const string& email);
	PersonEmailContact(const string& fullName, const string& gender);

	void addEmail(const string& email);

	virtual void display() const;
};
#endif // !PERSON_EMAIL_CONTACT_H
