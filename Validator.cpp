#include "Validator.h"
#include <regex>

bool Validator::IsPhoneNumber(const string& word)
{
	regex phonePattern("1-[0-9]{3}-[0-9]{3}-[0-9]{4}");

	return regex_match(word, phonePattern);
}

bool Validator::IsWebsite(const string& word)
{

	return word.rfind("www", 0) ==  0;
}

bool Validator::IsEmail(const string& word)
{
	return word.find('@') != string::npos;
}

bool Validator::IsGender(const string& word)
{
	return word == "Female" || word == "Male";
}