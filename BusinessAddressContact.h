
#ifndef BUSINESS_ADDRESS_CONTACT_H
#define BUSINESS_ADDRESS_CONTACT_H

#include "BusinessContact.h"
class BusinessAddressContact:public BusinessContact
{
private:
	string address;

public:
	BusinessAddressContact(
		const string& businessName,
		const string& businessType,
		const string& address
	);

	virtual void display() const;
};
#endif // !BUSINESS_ADDRESS_CONTACT_H
