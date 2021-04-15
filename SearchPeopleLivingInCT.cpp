#include "SearchPeopleLivingInCT.h"


/// <summary>
/// Find the number of people in Connecticut whose phone numbers have out-of-state
/// area codes aggregated by the state.
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
map<string, int> SearchPeopleLivingInCT::Search(const vector<Contact*>& contacts)
{
	vector<Contact*>::const_iterator contact;
	string areaCode = (*this).areaCode;

	vector<PersonAddressContact*> peopleLivingInCt;
	for_each(contacts.begin(), contacts.end(), [&peopleLivingInCt](Contact* const& contact)
		{
			PersonAddressContact* addressContact = dynamic_cast<PersonAddressContact*>(contact);
			if (addressContact && addressContact->GetAddress().GetState() == "Connecticut")
				peopleLivingInCt.push_back(addressContact);
		}
	);

	map<string, int> res;

	for_each(peopleLivingInCt.begin(), peopleLivingInCt.end(), [&res, &contacts, &areaCode, this](PersonAddressContact* const& addressContact)
		{
			string name = addressContact->GetName();
			string state = addressContact->GetAddress().GetState();
			for_each(contacts.begin(), contacts.end(), [&res, &areaCode, &name, &state, this](Contact* const& contact)
				{
					PersonPhoneContact* phoneContact = dynamic_cast<PersonPhoneContact*>(contact);
					if (phoneContact && phoneContact->GetName() == name)
					{
						// For U.S. numbers
						string target = "1-" + areaCode;

						vector<string> phoneNumbers = phoneContact->GetPhoneNumbers();

						bool notInState = true;
						for (auto phone = phoneNumbers.begin(); phone != phoneNumbers.end(); phone++)
						{
							// We find the area code, so this is not good
							if (phone->rfind(target, 0) == 0)
							{
								notInState = false;
							}
						}

						if (!notInState)
						{
							return;
						}

						// We pick the first phone number not in CT
						for (auto phone = phoneNumbers.begin(); phone != phoneNumbers.end(); phone++)
						{
							// Pick first number not in CT
							if (phone->rfind(target, 0) != 0)
							{
								string phoneAreaCode = (*phone).substr(2, 3);
								string state = (*this).areaQuickbook.GetState(phoneAreaCode);

								if (res.find(state) == res.end())
								{
									res[state] = 0;
								}

								res[state] += 1;
								break;
							}
						}

					}
				}
			);
		}
	);

	return res;
}

void SearchPeopleLivingInCT::GetParametersFromCLI()
{
	cout << "Please enter area code: ";
	string areaCode;
	cin >> areaCode;
	SetAreaCode(areaCode);
}


string SearchPeopleLivingInCT::Execute(const vector<Contact*>& contacts)
{
	map<string, int> queryRes = Search(contacts);
	return FormatAsTable(queryRes, "State", "Number");
}