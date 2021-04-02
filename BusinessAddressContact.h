
#ifndef BUSINESS_ADDRESS_CONTACT_H
#define BUSINESS_ADDRESS_CONTACT_H

#include "BusinessContact.h"
#include "Address.h"
class BusinessAddressContact:public BusinessContact
{
private:
	Address address;

public:
	BusinessAddressContact(
		const string& businessName,
		const string& businessType,
		const Address& address
	);

	virtual void Display() const;
};
#endif // !BUSINESS_ADDRESS_CONTACT_H
