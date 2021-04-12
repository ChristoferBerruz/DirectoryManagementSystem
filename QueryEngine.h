#ifndef QUERY_ENGINE_H
#define QUERY_ENGINE_H

#include "Contact.h"
#include "QueryCoreEngine.h"
#include <map>
#include <vector>
using namespace std;
class CLIQueryEngine
{
private:
	CoreQueryEngine coreQuery;
	string SearchPersonByNameOrderByState(const vector<Contact*>& contacts);
	string SearchPersonByEmailOrderByGender(const vector<Contact*>& contacts);
	string SearchQueryBusinessByPhoneNumberOrderByCategory(const vector<Contact*>& contacts);
	string SearchQueryBusinessByEmailOrWebsiteOrderByCategory(const vector<Contact*>& contacts);
	string SearchQueryPeopleLivingInCTWithOutOfStatePhone(const vector<Contact*>& contacts);
	string GenerateTable(const map<string, int>& queryResult, const string& label1, const string& label2);
	string GetPersonInfo(const vector<Contact*>& contacts);
	string GetBusinessInfo(const vector<Contact*>& contacts);
	string SearchQuery(const vector<Contact*>& contacts);
	int GetSearchOptionFromCLI();
	string DisplayQuery(const vector<Contact*>& contacts);
public:
	string Query(const vector<Contact*>& contacts);
};
#endif
