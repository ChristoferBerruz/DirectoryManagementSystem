#ifndef DISPLAY_PERSON_H
#define DISPLAY_PERSON_H
#include "DisplayQuery.h"
#include "PersonAddressContact.h"
#include "PersonEmailContact.h"
#include "PersonContact.h"
#include "PersonPhoneContact.h"
#include <algorithm>
class DisplayPerson : public DisplayQuery
{
private:
	string personName;
public:
	DisplayPerson(const string& name = "") :personName(name) {}
	void virtual GetParametersFromCLI();
	string virtual FindContact(const vector<Contact*>& contacts);
	string GetPersonName() const { return personName; }
	void SetPersonName(const string& name) { personName = name; }
	virtual ~DisplayPerson() {}
};
#endif