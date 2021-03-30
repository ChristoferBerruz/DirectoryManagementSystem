#ifndef BUSINESS_CONTACT_H
#define BUSINESS_CONTACT_H

#include "Contact.h"
#include <string>

using namespace std;
class BusinessContact : public Contact
{
private:
	string category;
public:
	BusinessContact(const string& name, const string& category);
	virtual void display() const;
};
#endif // !BUSINESS_CONTACT_H
