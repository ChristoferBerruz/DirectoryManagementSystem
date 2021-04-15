#include "SearchBusinessByPhoneNumber.h"

map<string, int> SearchBusinessByPhoneNumber::Search(const vector<Contact*>& contacts)
{
	map<string, int> res;

	string areaCode = (*this).areaCode;
	// For U.S. phone numbers
	string targetAreaCode = "1-" + areaCode;

	for_each(contacts.begin(), contacts.end(), [&areaCode, &res, &targetAreaCode](Contact* const& contact)
		{
			BusinessPhoneContact* phoneContact = dynamic_cast<BusinessPhoneContact*>(contact);
			if (phoneContact)
			{
				vector<string> phoneNums = phoneContact->GetPhoneNumbers();
				vector<string>::iterator phone;
				for (phone = phoneNums.begin(); phone != phoneNums.end(); phone++)
				{
					if (phone->rfind(targetAreaCode, 0) == 0)
					{
						// Found a match

						string category = phoneContact->GetCategory();

						if (res.find(category) == res.end())
							res[category] = 0;

						res[category] += 1;
						break;
					}
				}
			}
		}
	);

	return res;
}

void SearchBusinessByPhoneNumber::GetParametersFromCLI()
{
	cout << "Please enter area code: ";
	string areaCode;
	cin >> areaCode;
}

string SearchBusinessByPhoneNumber::Execute(const vector<Contact*>& contacts)
{
	map<string, int> res = Search(contacts);
	return FormatAsTable(res, "Category", "Number");
}