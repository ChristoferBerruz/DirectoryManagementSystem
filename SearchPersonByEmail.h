#ifndef SEARCH_PERSON_BY_EMAIL_H
#define SEARCH_PERSON_BY_EMAIL_H
#include "SearchQuery.h"
#include "PersonEmailContact.h"
#include <algorithm>
class SearchPersonByEmail : public SearchQuery
{
private:
	string emailDomain;
public:
	SearchPersonByEmail(const string& email = ""):emailDomain(email){}
	string virtual Execute(const vector<Contact*>& contacts);
	void virtual GetParametersFromCLI();
	map<string, int> virtual Search(const vector<Contact*>& contacts);
	string GetEmailDomain() const { return emailDomain; }
	void SetEmailDomain(const string& emailDom) { emailDomain = emailDom; }
	virtual ~SearchPersonByEmail() {}
};
#endif

