#ifndef QUERY_ENGINE_H
#define QUERY_ENGINE_H

#include "Contact.h"
#include <map>
#include <vector>
using namespace std;
class CLIQueryEngine
{
private:
	string SearchQuery(const vector<Contact*>& contacts);
	int GetSearchOptionFromCLI();
	string DisplayQuery(const vector<Contact*>& contacts);
public:
	string Query(const vector<Contact*>& contacts);
};
#endif
