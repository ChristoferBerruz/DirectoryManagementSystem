#ifndef SEARCH_BUSINESS_BY_EMAIL_OR_WEBSITE_H
#define SEARCH_BUSINESS_BY_EMAIL_OR_WEBSITE_H
#include "SearchQuery.h"
#include "BusinessWebContact.h"
class SearchBusinessByEmailOrWebsite : public SearchQuery
{
private:
	string emailEnding;
	string websiteDomain;
public:
	SearchBusinessByEmailOrWebsite(const string& email = "", const string& website = "") :emailEnding(email), websiteDomain(website) {}
	string virtual Execute(const vector<Contact*>& contacts);
	void virtual GetParametersFromCLI();
	map<string, int> virtual Search(const vector<Contact*>& contacts);
	string GetEmailEnding() const { return emailEnding; }
	void SetEmailEnding(const string& email) { emailEnding = email; }
	string GetWebsiteDomain() const { return websiteDomain; }
	void SetWebsiteDomain(const string& domain) { websiteDomain = domain; }
	virtual ~SearchBusinessByEmailOrWebsite() {}
};
#endif