#ifndef BUSINESS_WEB_CONTACT_H
#define BUSINESS_WEB_CONTACT_H
#include <string>
#include <vector>
#include "BusinessContact.h"
using namespace std;
class BusinessWebContact : public BusinessContact
{
private:
	vector<string> emailAddresses;
	vector<string> websites;
public:
	BusinessWebContact(const string& businessName, const string& businessType);
	BusinessWebContact(
		const string& businessName,
		const string& businessType,
		const string& email,
		const string& website
	);
	BusinessWebContact(
		const string& businessName,
		const string& businessType,
		const string& website
	);
	void AddEmail(const string& email);
	void AddWebsite(const string& website);

	vector<string> GetWebAddresses() const { return websites; }

	vector<string> GetEmailAddresses() const { return emailAddresses; }

	virtual void Display() const;

	virtual ~BusinessWebContact() {}
};
#endif // !BUSINESS_WEB_CONTACT_H
