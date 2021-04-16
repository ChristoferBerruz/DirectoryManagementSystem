#include "SearchBusinessByEmailOrWebsite.h"

/// <summary>
/// Searches a business contact that matches either a email ending or website domain.
/// Returns results aggregated by Category
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
map<string, int> SearchBusinessByEmailOrWebsite::Search(const vector<Contact*>& contacts)
{
	map<string, int> res;
	string emailEnding = (*this).emailEnding;
	string websiteDomain = (*this).websiteDomain;
	for_each(contacts.begin(), contacts.end(), [&emailEnding, &websiteDomain, &res](Contact* const& contact)
		{
			BusinessWebContact* webContact = dynamic_cast<BusinessWebContact*>(contact);
			if (webContact)
			{
				vector<string> websites = webContact->GetWebAddresses();
				vector<string>::iterator website;

				// Bool to not double count the contact
				bool previouslyAdded = false;

				// Check the websites
				for (website = websites.begin(); website != websites.end(); website++)
				{
					if (website->find(websiteDomain) != string::npos)
					{
						// Website contains domain, so take it
						string category = webContact->GetCategory();

						if (res.find(category) == res.end())
							res[category] = 0;

						res[category] += 1;
						previouslyAdded = true;
						break;
					}
				}

				// Check the emails only if contact not previously counted
				if (!previouslyAdded)
				{
					vector<string> emails = webContact->GetEmailAddresses();
					vector<string>::iterator email;

					for (email = emails.begin(); email != emails.end(); email++)
					{
						if (email->find(emailEnding) != string::npos)
						{
							string category = webContact->GetCategory();

							if (res.find(category) == res.end())
								res[category] = 0;

							res[category] += 1;
							break;
						}
					}
				}
			}
		}
	);

	return res;
}


void SearchBusinessByEmailOrWebsite::GetParametersFromCLI()
{
	cout << "Please enter emailEnding: ";
	string emailEnding;
	getline(cin,emailEnding);

	cout << "Please enter websiteDomain: ";
	string websiteDomain;
	getline(cin,websiteDomain);

	SetEmailEnding(emailEnding);
	SetWebsiteDomain(websiteDomain);
}

string SearchBusinessByEmailOrWebsite::Execute(const vector<Contact*>& contacts)
{
	map<string, int> queryRes = Search(contacts);
	if (queryRes.empty())
		return "NO RESULTS";
	return FormatAsTable(queryRes, "Category", "Number");
}