#ifndef DISPLAY_BUSINESS_H
#define DISPLAY_BUSINESS_H
#include "DisplayQuery.h"
#include "BusinessWebContact.h"
#include "BusinessContact.h"
#include "BusinessPhoneContact.h"
#include "BusinessAddressContact.h"
#include <algorithm>
class DisplayBusiness : public DisplayQuery
{
private:
	string businessName;
public:
	DisplayBusiness(const string& organization = ""):businessName(organization){}
	void virtual GetParametersFromCLI();
	string virtual FindContact(const vector<Contact*>& contacts);
	string GetBusinessName() const { return businessName; }
	void SetBusinessName(const string& org) { businessName = org; }
	virtual ~DisplayBusiness() {}
};
#endif