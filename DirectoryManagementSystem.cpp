#include "DirectoryManagementSystem.h"
#include "Contact.h"
#include "Address.h"
#include "PersonAddressContact.h"
#include "PersonEmailContact.h"
#include "PersonPhoneContact.h"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <exception>

using namespace std;

/// <summary>
/// Destructor needed because memory was allocated in the heap
/// </summary>
DirectoryManagementSystem::~DirectoryManagementSystem() 
{
	for_each(contacts.begin(), contacts.end(), [](Contact* contact)
		{
			delete contact;
		}
	);
}


/// <summary>
/// Creates and adds one or multiple contacts on the vector depending
/// on the information in words.
/// </summary>
/// <param name="words"></param>
void DirectoryManagementSystem::CreatePersonContact(const vector<string>& words)
{
	vector<string>::const_iterator word;
	string name = words[0];
	string gender = words[1];
	for (int i = 2; i < words.size(); i++)
	{
		string current = words[i];

		if (validator.IsEmail(current))
		{
			Contact* contact = FindInQuickbook(name, typeid(PersonEmailContact).name());
			if (!contact)
			{
				contact = new PersonEmailContact(name, gender, current);
				AddToQuickbook(name, typeid(PersonEmailContact).name(), contact);
				contacts.push_back(contact);
			}else
			{
				PersonEmailContact* emailContact = dynamic_cast<PersonEmailContact*>(contact);
				emailContact->AddEmail(current);
			}


		}
		else if (validator.IsPhoneNumber(current))
		{
			Contact* contact = FindInQuickbook(name, typeid(PersonPhoneContact).name());
			if (!contact)
			{
				contact = new PersonPhoneContact(name, gender, current);
				AddToQuickbook(name, typeid(PersonPhoneContact).name(), contact);
				contacts.push_back(contact);
			}else
			{
				PersonPhoneContact* phoneContact = dynamic_cast<PersonPhoneContact*>(contact);
				phoneContact->AddPhoneNumber(current);
			}

		}
		else {
			// This is an address, read remaining
			string street = words[i++];
			string district = words[i++];
			string state = words[i++];
			string zipcode = words[i++];

			Address address(street, district, state, zipcode);
			contacts.push_back(new PersonAddressContact(name, gender, address));
		}
	}
}

Contact* DirectoryManagementSystem::FindInQuickbook(const string& name, const string& contactType)
{
	string key = name + contactType;
	if (quickBook.find(key) != quickBook.end())
	{
		return quickBook[key];
	}
	return NULL;
}

void DirectoryManagementSystem::AddToQuickbook(const string& name, const string& contactType, Contact* contact)
{
	string key = name + contactType;
	if (quickBook.find(key) == quickBook.end())
	{
		quickBook[key] = contact;
	}
}

/// <summary>
/// A utility function to trim left and right whitespaces from a string
/// </summary>
/// <param name="word"></param>
/// <returns></returns>
string DirectoryManagementSystem::TrimString(const string& word)
{
	if (word.empty())
		return word;

	string res(word);
	// Remove left whitespaces
	while (res.find(" ") == 0)
		res.erase(0, 1);

	size_t length = res.length();

	// Remove right whitespaces

	while (res.rfind(" ") == --length)
		res.erase(length, length + 1);

	return res;
}

/// <summary>
/// Parses a line into words that are tokens to be properly read by the creation functions.
/// </summary>
/// <param name="line"></param>
/// <returns></returns>
vector<string> DirectoryManagementSystem::ParseLine(const string& line)
{
	istringstream buffer(line);

	vector<string> words;

	// Get each string separated by a comma
	while (!buffer.eof())
	{
		string word;
		getline(buffer, word, ',');

		// This is a long street address
		if (word[0] == '"')
		{
			string street;
			street += word.substr(1, word.length() - 1);

			// Get remaining street address
			string remainingStreet;
			getline(buffer, remainingStreet, '"');

			// Getting rid of the empty string before remaining ,
			string dummy;
			getline(buffer, dummy, ',');

			street += remainingStreet;
			words.push_back(TrimString(street));
		}
		else
		{
			words.push_back(TrimString(word));
		}
	}

	return words;
}

void DirectoryManagementSystem::IngestData(istream& is)
{
	string line;

	getline(is, line);

	vector<string> words = ParseLine(line);

	// Validate first line
	try 
	{
		if (words.size() < 2)
			throw;
		int res = stoi(words[0]);
	}
	catch (...) {
		throw exception("First line must contain contain type and number of contacts.");
	}

	string contactType = words[1];

	if (contactType != "person" && contactType != "business")
		throw exception("Contact type not supported.");

	// Parse line by line
	while (!is.eof())
	{
		getline(is, line);

		words = ParseLine(line);
		if (contactType == "person") {
			CreatePersonContact(words);
		}
	}
}

void DirectoryManagementSystem::ShowAllContacts()
{
	for_each(contacts.begin(), contacts.end(), [](const Contact* contact)
		{
			contact->Display();
			cout << "--------------------------------------------------" << endl;
		}
	);
}

istream& operator>>(istream& is, DirectoryManagementSystem dms) 
{
	dms.IngestData(is);

	return is;
}