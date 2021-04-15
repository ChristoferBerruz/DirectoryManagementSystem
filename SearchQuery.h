#ifndef SEARCH_QUERY_H
#define SEARCH_QUERY_H
#include "BaseQuery.h"
#include <map>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
class SearchQuery : public BaseQuery
{
public:
	string virtual Execute(const vector<Contact*>& contacts) = 0;
	void virtual GetParametersFromCLI() = 0;
	map<string, int> virtual Search(const vector<Contact*>& contacts) = 0;
	virtual ~SearchQuery() {}
protected:
	string FormatAsTable(const map<string, int>& queryResult, const string& columnOne, const string& columnTwo);
};
#endif
