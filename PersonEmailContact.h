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

	string PresentEmails() const;

	void AddEmail(const string& email);

	virtual void Display() const;

	vector<string> GetEmails() const { return emailAddresses; }

	virtual ~PersonEmailContact() {}
};
#endif // !PERSON_EMAIL_CONTACT_H
