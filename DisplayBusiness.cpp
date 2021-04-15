#include "DisplayBusiness.h"

string DisplayBusiness::FindContact(const vector<Contact*>& contacts)
{
	string organization = (*this).businessName;

	vector<Contact*> businessContacts;
	copy_if(contacts.begin(), contacts.end(), back_insert_iterator<vector<Contact*>>(businessContacts), [&organization](Contact* const contact)
		{
			return dynamic_cast<BusinessContact*>(contact) && contact->GetName() == organization;
		}
	);


	// We are going to dump the information using this
	ostringstream buffer;

	// All possible combinations
	string webBusiness = typeid(BusinessWebContact).name();
	string phoneBusiness = typeid(BusinessPhoneContact).name();
	string addressBusiness = typeid(BusinessAddressContact).name();
	for (int i = 0; i < businessContacts.size(); i++)
	{
		Contact* contact = businessContacts[i];
		if (i == 0)
		{
			BusinessContact* business = dynamic_cast<BusinessContact*>(contact);
			buffer << "Organization: " << business->GetName();
			buffer << "Category: " << business->GetCategory();
		}

		string className = typeid(*contact).name();
		if (className == webBusiness)
		{
			BusinessWebContact* webContact = dynamic_cast<BusinessWebContact*>(contact);
			buffer << "Web addresses: ";

			vector<string> websites = webContact->GetWebAddresses();
			buffer << FormatVector(websites) << endl;

			buffer << "Email addresses: ";
			vector<string> emails = webContact->GetEmailAddresses();
			buffer << FormatVector(emails) << endl;
		}

		if (className == phoneBusiness)
		{
			BusinessPhoneContact* phoneContact = dynamic_cast<BusinessPhoneContact*>(contact);
			buffer << "Phone numbers: ";
			buffer << FormatVector(phoneContact->GetPhoneNumbers()) << endl;
		}

		if (className == addressBusiness)
		{
			BusinessAddressContact* addressContact = dynamic_cast<BusinessAddressContact*>(contact);
			buffer << "Address: \n";
			Address address = addressContact->GetAddress();
			buffer << "Street: " << address.GetStreet();
			buffer << "City: " << address.GetCity();
			buffer << "State: " << address.GetState();
			buffer << "Zip: " << address.GetZipcode();
		}
	}
	return buffer.str();
}


void DisplayBusiness::GetParametersFromCLI()
{
	cout << "Enter name of organization: ";

	string organization;
	cin >> organization;
	SetBusinessName(organization);
}