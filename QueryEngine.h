#ifndef QUERY_ENGINE_H
#define QUERY_ENGINE_H

#include "Contact.h"
#include "AreaCodesBook.h"
#include <map>
#include <vector>
using namespace std;
class CLIQueryEngine
{
private:
	AreaCodesBook areaQuickbook;
	map<string, int> SearchPersonByNameOrderByState(const vector<Contact*>& contacts);
	map<string, int> SearchPersonByEmailOrderByGender(const vector<Contact*>& contacts);
	map<string, int> SearchQueryBusinessByPhoneNumberOrderByCategory(const vector<Contact*>& contacts);
	map<string, int> SearchQueryBusinessByEmailOrWebsiteOrderByCategory(const vector<Contact*>& contacts);
	map<string, int> SearchQueryPeopleLivingInCTWithOutOfStatePhone(const vector<Contact*>& contacts);
	string GenerateTable(const map<string, int>& queryResult, const string& label1, const string& label2);
	string GetPersonInfo(const vector<Contact*>& contacts);
	string GetBusinessInfo(const vector<Contact*>& contacts);
	string SearchQuery(const vector<Contact*>& contacts);
	string DisplayQuery(const vector<Contact*>& contacts);
public:
	string Query(const vector<Contact*>& contacts);
};
#endif
