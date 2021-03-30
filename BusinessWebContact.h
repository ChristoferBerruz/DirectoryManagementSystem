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

	void addEmail(const string& email);
	void addWebsite(const string& website);

	virtual void display() const;
};
#endif // !BUSINESS_WEB_CONTACT_H
