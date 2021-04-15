#ifndef DISPLAY_QUERY_H
#define DISPLAY_QUERY_H
#include "BaseQuery.h"
#include <sstream>
class DisplayQuery : public BaseQuery
{
public:
	string virtual Execute(const vector<Contact*>& contacts) { return FindContact(contacts); };
	void virtual GetParametersFromCLI() = 0;
	string virtual FindContact(const vector<Contact*>& contacts) = 0;
	virtual ~DisplayQuery() {}
protected:
	string FormatVector(const vector<string>& elements);
};

#endif

