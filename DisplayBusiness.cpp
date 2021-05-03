#include "DisplayBusiness.h"

/// <summary>
/// Finds a business contact given an organization name
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
string DisplayBusiness::FindContact(const vector<Contact*>& contacts)
{
	string organization = (*this).businessName;

	vector<Contact*> businessContacts;
	copy_if(contacts.begin(), contacts.end(), back_insert_iterator<vector<Contact*>>(businessContacts), [&organization](Contact* const contact)
		{
			return dynamic_cast<BusinessContact*>(contact) && contact->GetName() == organization;
		}
	);

	if(businessContacts.size() == 0)
		return "NO RESULTS";

	// We are going to dump the information using this
	ostringstream buffer;

	// All possible combinations
	string webBusiness = typeid(BusinessWebContact).name();
	string phoneBusiness = typeid(BusinessPhoneContact).name();
	string addressBusiness = typeid(BusinessAddressContact).name();

	// Go over all the contacts for the business, check its type, and output to buffer
	for (int i = 0; i < businessContacts.size(); i++)
	{
		Contact* contact = businessContacts[i];
		if (i == 0)
		{
			BusinessContact* business = dynamic_cast<BusinessContact*>(contact);
			buffer << FormatSimpleLine("Organization:", business->GetName());
			buffer << FormatSimpleLine("Category:", business->GetCategory());
		}

		string className = typeid(*contact).name();
		if (className == webBusiness)
		{
			BusinessWebContact* webContact = dynamic_cast<BusinessWebContact*>(contact);

			vector<string> websites = webContact->GetWebAddresses();
			buffer << FormatSimpleLine("Web addresses:", FormatVector(websites));

			vector<string> emails = webContact->GetEmailAddresses();
			buffer << FormatSimpleLine("Email addresses", FormatVector(emails));
		}

		if (className == phoneBusiness)
		{
			BusinessPhoneContact* phoneContact = dynamic_cast<BusinessPhoneContact*>(contact);
			buffer << FormatSimpleLine("Phone numbers:", FormatVector(phoneContact->GetPhoneNumbers()));
		}

		if (className == addressBusiness)
		{
			BusinessAddressContact* addressContact = dynamic_cast<BusinessAddressContact*>(contact);
			buffer << FormatSimpleLine("Address:", "");
			Address address = addressContact->GetAddress();
			buffer << FormatPaddedLine("Street: ", address.GetStreet());
			buffer << FormatPaddedLine("City: ", address.GetCity());
			buffer << FormatPaddedLine("State: ", address.GetState());
			buffer << FormatPaddedLine("Zip: ", address.GetZipcode());
		}
	}
	return buffer.str();
}


void DisplayBusiness::GetParametersFromCLI()
{
	cout << "Enter name of organization: ";

	string organization;
	getline(cin,organization);
	SetBusinessName(organization);
}