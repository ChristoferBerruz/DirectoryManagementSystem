#include "SearchPersonByEmail.h"

string SearchPersonByEmail::Execute(const vector<Contact*>& contacts)
{
	map<string, int> res = Search(contacts);
	return FormatAsTable(res, "Gender", "Number");
}



/// <summary>
/// Searches a directory for people that match a email domain. Gets results aggregated by gender.
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
map<string, int> SearchPersonByEmail::Search(const vector<Contact*>& contacts)
{
	map<string, int> res;
	string emailDomain = (*this).emailDomain;
	for_each(contacts.begin(), contacts.end(), [&res, &emailDomain](Contact* const& contact)
		{
			PersonEmailContact* emailContact = dynamic_cast<PersonEmailContact*>(contact);

			if (emailContact)
			{
				vector<string> emails = emailContact->GetEmails();
				vector<string>::iterator currentEmail;

				// Check if any of the emails has the email domain
				for (currentEmail = emails.begin(); currentEmail != emails.end(); currentEmail++)
				{
					if (currentEmail->find(emailDomain) != string::npos)
					{
						if (res.find(emailContact->GetGender()) == res.end())
							res[emailContact->GetGender()] = 0;

						res[emailContact->GetGender()] += 1;
						// Only add this contact ONCE, so break.
						break;
					}
				}
			}
		}
	);

	return res;
}

void SearchPersonByEmail::GetParametersFromCLI()
{
	cout << "Please enter email domain: ";
	string emailDomain;
	cin >> emailDomain;
	SetEmailDomain(emailDomain);
}