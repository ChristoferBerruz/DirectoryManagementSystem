#include "DisplayPerson.h"


/// <summary>
/// Finds all the information about a person contact give its name.
/// </summary>
/// <param name="contacts"></param>
/// <returns></returns>
string DisplayPerson::FindContact(const vector<Contact*>& contacts)
{
	string name = (*this).personName;

	vector<Contact*> personContacts;
	copy_if(contacts.begin(), contacts.end(), back_insert_iterator<vector<Contact*>>(personContacts), [&name](Contact* const contact)
		{
			return dynamic_cast<PersonContact*>(contact) && contact->GetName() == name;
		}
	);

	if (personContacts.size() == 0)
		return "NO RESULTS";

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
			buffer << FormatSimpleLine("Name:", person->GetName());
			buffer << FormatSimpleLine("Gender:", person->GetGender());
		}

		string className = typeid(*contact).name();

		if (className == emailPerson)
		{
			PersonEmailContact* emailContact = dynamic_cast<PersonEmailContact*>(contact);
			buffer << FormatSimpleLine("Email:", FormatVector(emailContact->GetEmails()));
		}

		if (className == phonePerson)
		{
			PersonPhoneContact* phoneContact = dynamic_cast<PersonPhoneContact*>(contact);
			buffer << FormatSimpleLine("Phone numbers:", FormatVector(phoneContact->GetPhoneNumbers()));
		}
		if (className == addressPerson)
		{
			PersonAddressContact* addressContact = dynamic_cast<PersonAddressContact*>(contact);
			buffer << FormatSimpleLine("Address:", "");
			Address address = addressContact->GetAddress();
			buffer << FormatPaddedLine("Street:", address.GetStreet());
			buffer << FormatPaddedLine("City:", address.GetCity());
			buffer << FormatPaddedLine("State:", address.GetState());
			buffer << FormatPaddedLine("Zip:", address.GetZipcode());
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