
#ifndef BUSINESS_PHONE_CONTACT_H
#define BUSINESS_PHONE_CONTACT_H

#include "BusinessContact.h"
#include <string>
#include <vector>

using namespace std;
class BusinessPhoneContact : public BusinessContact
{
private:
	vector<string> phoneNumbers;
public:
	BusinessPhoneContact(
		const string& businessName,
		const string& businessType,
		const string& phoneNum
	);
	BusinessPhoneContact(
		const string& businessName,
		const string& businessType
	);
	void addPhoneNumber(const string& phoneNum);
	virtual void display() const;
};

#endif // !BUSINESS_PHONE_CONTACT_H

