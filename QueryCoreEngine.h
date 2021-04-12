#ifndef QUERY_CORE_ENGINE_H
#define QUERY_CORE_ENGINE_H
#include <map>
#include <string>
#include <vector>
#include "Contact.h"
#include "AreaCodesBook.h"
class CoreQueryEngine 
{
protected:
	AreaCodesBook areaQuickbook;
public:
	map<string, int> SearchPersonByNameOrderByState(const vector<Contact*>& contacts, const string& name);
	map<string, int> SearchPersonByEmailOrderByGender(const vector<Contact*>& contacts, const string& emailDomain);
	map<string, int> SearchQueryBusinessByPhoneNumberOrderByCategory(const vector<Contact*>& contacts, const string& areaCode);
	map<string, int> SearchQueryBusinessByEmailOrWebsiteOrderByCategory(const vector<Contact*>& contacts, const string& emailEnding, const string& websiteDomain);
	map<string, int> SearchQueryPeopleLivingInCTWithOutOfStatePhone(const vector<Contact*>& contacts, const string& areaCode);
};
#endif