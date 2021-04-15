#ifndef SEARCH_PERSON_BY_NAME_H
#define SEARCH_PERSON_BY_NAME_H
#include "SearchQuery.h"
#include "PersonAddressContact.h"
#include <algorithm>
class SearchPersonByName : public SearchQuery
{
private:
	string name;
public:
	string virtual Execute(const vector<Contact*>& contacts);
	void virtual GetParametersFromCLI();
	map<string, int> virtual Search(const vector<Contact*>& contacts);
	SearchPersonByName(const string& name = "") :name(name) {}
	string GetNameParam() const { return name; }
	void SetNameParam(const string& nameParam) { name = nameParam; }
	virtual ~SearchPersonByName() {}
};
#endif