
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
	void AddPhoneNumber(const string& phoneNum);
	virtual void Display() const;

	vector<string> GetPhoneNumbers() const { return phoneNumbers; }
	virtual ~BusinessPhoneContact() {}
};

#endif // !BUSINESS_PHONE_CONTACT_H

