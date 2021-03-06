#include "DirectoryManagementSystem.h"

using namespace std;

DirectoryManagementSystem* DirectoryManagementSystem::Instance = nullptr;

DirectoryManagementSystem* DirectoryManagementSystem::GetInstance()
{
	if (!Instance)
		Instance = new DirectoryManagementSystem();
	return Instance;
}

void DirectoryManagementSystem::DeleteInstance()
{
	if (Instance)
		delete Instance;
	Instance = nullptr;
}
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
	int i = 0;
	string name = words[i++];
	uniqueNames.insert(name);
	string gender;
	if (validator.IsGender(words[i]))
	{
		gender = words[i++];
	}
	else 
	{
		gender = "None";
	}

	for (;i < words.size(); i++)
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


/// <summary>
/// Add BusinessContacts to the contacts
/// </summary>
/// <param name="words"></param>
void DirectoryManagementSystem::CreateBusinessContact(const vector<string>& words)
{
	int i = 0;
	string name = words[i++];
	uniqueNames.insert(name);
	string category = words[i];
	bool isPhone = validator.IsPhoneNumber(category);
	bool isEmail = validator.IsEmail(category);
	bool isWebsite = validator.IsWebsite(category);
	if (isPhone || isEmail || isWebsite)
	{
		// Misplace as category, we need to read from here onwards
		category = "None";
	}
	else {
		// It is indeed a category, so update index
		i++;
	}
	for (; i < words.size(); i++)
	{
		string current = words[i];
		if (validator.IsEmail(current) || validator.IsWebsite(current))
		{
			Contact* contact = FindInQuickbook(name, typeid(BusinessWebContact).name());
			if (!contact)
			{
				contact = new BusinessWebContact(name, category);
				AddToQuickbook(name, typeid(BusinessWebContact).name(), contact);
				contacts.push_back(contact);
			}

			BusinessWebContact* webContact = dynamic_cast<BusinessWebContact*>(contact);

			if (validator.IsEmail(current))
				webContact->AddEmail(current);
			else
				webContact->AddWebsite(current);

		}
		else if (validator.IsPhoneNumber(current))
		{
			Contact* contact = FindInQuickbook(name, typeid(BusinessPhoneContact).name());
			if (!contact)
			{
				contact = new BusinessPhoneContact(name, category, current);
				AddToQuickbook(name, typeid(BusinessPhoneContact).name(), contact);
				contacts.push_back(contact);
			}
			else
			{
				BusinessPhoneContact* phoneContact = dynamic_cast<BusinessPhoneContact*>(contact);
				phoneContact->AddPhoneNumber(current);
			}
		}
		else
		{
			// Address, read remaining
			string street = words[i++];
			string district = words[i++];
			string state = words[i++];
			string zipcode = words[i++];

			Address address(street, district, state, zipcode);
			contacts.push_back(new BusinessAddressContact(name, category, address));
		}
	}
}

/// <summary>
/// Allows to find previous entered contacts. This allows appending information
/// to a previously created contact.
/// </summary>
/// <param name="name">name of the contact</param>
/// <param name="contactType">type of the contact</param>
/// <returns></returns>
Contact* DirectoryManagementSystem::FindInQuickbook(const string& name, const string& contactType)
{
	string key = name + contactType;
	if (quickBook.find(key) != quickBook.end())
	{
		return quickBook[key];
	}
	return NULL;
}


/// <summary>
/// Adds a contact to the quickbook.
/// </summary>
/// <param name="name"></param>
/// <param name="contactType"></param>
/// <param name="contact"></param>
void DirectoryManagementSystem::AddToQuickbook(const string& name, const string& contactType, Contact* contact)
{
	string key = name + contactType;
	if (quickBook.find(key) == quickBook.end())
	{
		quickBook[key] = contact;
	}
}

/// <summary>
/// A utility function to trim left and right whitespaces from a string.
/// Useful because we validate strings and it is whitespace sensitive.
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


/// <summary>
/// Gets data to create contacts per file. Only one contact type per file.
/// </summary>
/// <param name="is"></param>
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

	try 
	{
		while (!is.eof())
		{
			getline(is, line);

			words = ParseLine(line);
			if (contactType == "person") {
				CreatePersonContact(words);
			}
			else if (contactType == "business")
			{
				CreateBusinessContact(words);
			}
		}
	}
	catch (...)
	{
		throw exception("Directory cannot read this file: bad format!");
	}
	// Parse line by line
}


/// <summary>
/// Debug function to check that all contacts were added correctly into the DMS
/// </summary>
void DirectoryManagementSystem::ShowAllContacts()
{
	for_each(contacts.begin(), contacts.end(), [](const Contact* contact)
		{
			contact->Display();
			cout << "--------------------------------------------------" << endl;
		}
	);
}


/// <summary>
/// Main interface that allows the DMS to be querable.
/// </summary>
void DirectoryManagementSystem::Query()
{
	queryResult = engine.Query(contacts);
}


/// <summary>
/// Prints the result of a previously executed query.
/// </summary>
void DirectoryManagementSystem::DisplayResult()
{
	cout << queryResult << endl;
}


ostream& operator<<(ostream& os, DirectoryManagementSystem dms)
{
	os << dms.queryResult << endl;
	return os;
}

/// <summary>
/// Another way to ingest data.
/// </summary>
/// <param name="is"></param>
/// <param name="dms"></param>
/// <returns></returns>
istream& operator>>(istream& is, DirectoryManagementSystem dms) 
{
	try 
	{
		dms.IngestData(is);
	}
	catch (exception e)
	{
		throw e;
	}

	return is;
}
