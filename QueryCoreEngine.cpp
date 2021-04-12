#include "QueryCoreEngine.h"
#include "PersonAddressContact.h"
#include "PersonEmailContact.h"
#include "PersonPhoneContact.h"
#include "BusinessPhoneContact.h"
#include "BusinessWebContact.h"
#include <algorithm>


map<string, int> CoreQueryEngine::SearchPersonByNameOrderByState(const vector<Contact*>& contacts, const string& name)
{
	map<string, int> res;
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

map<string, int> CoreQueryEngine::SearchPersonByEmailOrderByGender(const vector<Contact*>& contacts, const string& emailDomain)
{
	map<string, int> res;

	for_each(contacts.begin(), contacts.end(), [&res, &emailDomain](Contact* const& contact)
		{
			PersonEmailContact* emailContact = dynamic_cast<PersonEmailContact*>(contact);

			if (emailContact)
			{
				vector<string> emails = emailContact->GetEmails();
				vector<string>::iterator currentEmail;

				for (currentEmail = emails.begin(); currentEmail != emails.end(); currentEmail++)
				{
					if (currentEmail->find(emailDomain) != string::npos)
					{
						if (res.find(emailContact->GetGender()) == res.end())
							res[emailContact->GetGender()] = 0;

						res[emailContact->GetGender()] += 1;
						break;
					}
				}
			}
		}
	);

	return res;
}

map<string, int> CoreQueryEngine::SearchQueryBusinessByPhoneNumberOrderByCategory(const vector<Contact*>& contacts, const string& areaCode)
{
	map<string, int> res;

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


map<string, int> CoreQueryEngine::SearchQueryBusinessByEmailOrWebsiteOrderByCategory(const vector<Contact*>& contacts,
	const string& emailEnding, const string& websiteDomain)
{

	map<string, int> res;

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

map<string, int> CoreQueryEngine::SearchQueryPeopleLivingInCTWithOutOfStatePhone(const vector<Contact*>& contacts, const string& areaCode)
{
	vector<Contact*>::const_iterator contact;

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