#ifndef BUSINESS_CONTACT_H
#define BUSINESS_CONTACT_H

#include "Contact.h"
#include <string>

using namespace std;
class BusinessContact : public Contact
{
private:
	string businessType;
public:
	BusinessContact(const string& businessName = "FakeBusiness", const string& businessType = "Law Firm");
	virtual void display() const;
};
#endif // !BUSINESS_CONTACT_H
