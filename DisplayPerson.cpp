#include "DisplayPerson.h"

string DisplayPerson::FindContact(const vector<Contact*>& contacts)
{
	string name = (*this).personName;

	vector<Contact*> personContacts;
	copy_if(contacts.begin(), contacts.end(), back_insert_iterator<vector<Contact*>>(personContacts), [&name](Contact* const contact)
		{
			return dynamic_cast<PersonContact*>(contact) && contact->GetName() == name;
		}
	);

	// All possible combinatons
	string addressPerson = typeid(PersonAddressContact).name();
	string phonePerson = typeid(PersonPhoneContact).name();
	string emailPerson = typeid(PersonEmailContact).name();

	// We output here
	ostringstream buffer;
	for (int i = 0; i < personContacts.size(); i++)
	{
		Contact* contact = personContacts[i];
		if (i == 0)
		{
			PersonContact* person = dynamic_cast<PersonContact*>(contact);
			buffer << "Name: " << person->GetName() << endl;
			buffer << "Gender: " << person->GetGender() << endl;
		}

		string className = typeid(*contact).name();

		if (className == emailPerson)
		{
			PersonEmailContact* emailContact = dynamic_cast<PersonEmailContact*>(contact);
			buffer << "Email: " << FormatVector(emailContact->GetEmails()) << endl;
		}

		if (className == phonePerson)
		{
			PersonPhoneContact* phoneContact = dynamic_cast<PersonPhoneContact*>(contact);
			buffer << "Phone numbers: " << FormatVector(phoneContact->GetPhoneNumbers()) << endl;
		}
		if (className == addressPerson)
		{
			PersonAddressContact* addressContact = dynamic_cast<PersonAddressContact*>(contact);
			buffer << "Address: \n";
			Address address = addressContact->GetAddress();
			buffer << "Street: " << address.GetStreet() << endl;
			buffer << "City: " << address.GetCity() << endl;
			buffer << "State: " << address.GetState() << endl;
			buffer << "Zip: " << address.GetZipcode() << endl;
		}
	}

	return buffer.str();
}



void DisplayPerson::GetParametersFromCLI()
{
	string dummy;
	getline(cin, dummy);
	cout << "Enter name of person: ";
	string name;
	getline(cin, name);

	SetPersonName(name);
}