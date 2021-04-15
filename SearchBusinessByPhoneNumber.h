#ifndef SEARCH_BUSINESS_BY_PHONE_NUMBER_H
#define SEARCH_BUSINESS_BY_PHONE_NUMBER_H
#include "SearchQuery.h"
#include "BusinessPhoneContact.h"
class SearchBusinessByPhoneNumber : public SearchQuery
{
private:
	string areaCode;
public:
	string virtual Execute(const vector<Contact*>& contacts);
	void virtual GetParametersFromCLI();
	map<string, int> virtual Search(const vector<Contact*>& contacts);
	string GetAreaCode() const { return areaCode; }
	void SetAreaCode(const string& areaC) { areaCode = areaC; }
	virtual ~SearchBusinessByPhoneNumber() {}
};
#endif