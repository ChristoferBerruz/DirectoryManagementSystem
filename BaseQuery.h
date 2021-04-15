#ifndef BASE_QUERY_H
#define BASE_QUERY_H
#include "Contact.h"
#include <vector>
#include <string>
using namespace std;
class BaseQuery
{
public:
	string virtual Execute(const vector<Contact*>& contacts) = 0;
	void virtual GetParametersFromCLI() = 0;
	virtual ~BaseQuery() {}
};

#endif

