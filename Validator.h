#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <string>

using namespace std;
class Validator
{
public:
	bool IsPhoneNumber(const string& word);
	bool IsWebsite(const string& word);
	bool IsEmail(const string& word);
	bool IsGender(const string& word);
};
#endif // !VALIDATOR_H

