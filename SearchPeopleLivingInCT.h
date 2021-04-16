#ifndef SEARCH_PEOPLE_LIVING_IN_CT_H
#define SEARCH_PEOPLE_LIVING_IN_CT_H
#include "SearchQuery.h"
#include "AreaCodesBook.h"
#include "PersonPhoneContact.h"
#include "PersonAddressContact.h"
class SearchPeopleLivingInCT : public SearchQuery
{
private:
	string areaCode;
	AreaCodesBook areaQuickbook;
public:
	SearchPeopleLivingInCT(const string& areaCode = "") :areaCode(areaCode) {}
	SearchPeopleLivingInCT(const AreaCodesBook& codeBook, const string& areaCode = "") :areaCode(areaCode), areaQuickbook(codeBook) {}
	string virtual Execute(const vector<Contact*>& contacts);
	void virtual GetParametersFromCLI();
	map<string, int> virtual Search(const vector<Contact*>& contacts);
	virtual ~SearchPeopleLivingInCT() {}
	string GetAreaCode() const { return areaCode; }
	void SetAreaCode(const string& aCode) { areaCode = aCode; }
};
#endif