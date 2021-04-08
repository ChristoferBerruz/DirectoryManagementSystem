#include "Validator.h"
#include <regex>

bool Validator::IsPhoneNumber(const string& word)
{
	regex phonePattern("1-[0-9]{3}-[0-9]{3}-[0-9]{4}");

	return regex_match(word, phonePattern);
}

bool Validator::IsWebsite(const string& word)
{
	regex websitePattern("w{3}\.[a-zA-Z]+\.[a-zA-Z]+");

	return regex_match(word, websitePattern);
}

bool Validator::IsEmail(const string& word)
{
	return word.find('@') != string::npos;
}