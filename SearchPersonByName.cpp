#include "SearchPersonByName.h"
string SearchPersonByName::Execute(const vector<Contact*>& contacts)
{
	map<string, int> res = Search(contacts);
	return SearchQuery::FormatAsTable(res, "Name", "Number");
}

void SearchPersonByName::GetParametersFromCLI()
{
	cout << "Please enter name: ";
	string nameParam;
	cin >> nameParam;
	SetNameParam(nameParam);
}

map<string, int> SearchPersonByName::Search(const vector<Contact*>& contacts)
{
	map<string, int> res;
	string name = (*this).name;
	for_each(contacts.begin(), contacts.end(), [&name, &res](Contact* const& contact)
		{
			PersonAddressContact* addressContact = dynamic_cast<PersonAddressContact*>(contact);

			// Only objects of PersonAddressContact
			if (addressContact && addressContact->GetName().find(name) != string::npos)
			{
				// Add to map
				string state = addressContact->GetAddress().GetState();
				if (res.find(state) == res.end())
				{
					res[state] = 0;
				}

				res[state] += 1;
			}
		}
	);
	return res;
}