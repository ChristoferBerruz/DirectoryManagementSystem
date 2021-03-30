
#ifndef PERSON_PHONE_CONTACT_H
#define PERSON_PHONE_CONTACT_H

#include "PersonContact.h"
#include <vector>
#include <string>

using namespace std;
class PersonPhoneContact : public PersonContact
{
private:
	vector<string> phoneNumbers;
public:
	PersonPhoneContact(const string& fullName, const string& gender, const string& phoneNum);
	PersonPhoneContact(const string& fullName, const string& gender);

	void AddPhoneNumber(const string& phoneNum);
	virtual void Display() const;
};
#endif // !PERSON_PHONE_CONTACT_H

